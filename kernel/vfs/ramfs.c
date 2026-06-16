#include "mcs_vfs.h"

static int mcs_strcmp(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        if (*a != *b) {
            return (int)((unsigned char)*a - (unsigned char)*b);
        }
        ++a;
        ++b;
    }
    return (int)((unsigned char)*a - (unsigned char)*b);
}

static size_t mcs_strlen(const char *s) {
    size_t len = 0u;
    while (s[len] != '\0') {
        ++len;
    }
    return len;
}

static void mcs_strcpy(char *dst, const char *src, size_t max_len) {
    size_t i = 0u;
    if (max_len == 0u) {
        return;
    }
    while (i + 1u < max_len && src[i] != '\0') {
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
}

void mcs_ramfs_init(mcs_ramfs_t *fs) {
    if (fs == 0) {
        return;
    }

    fs->node_count = 1u;
    fs->data_used = 0u;

    for (size_t i = 0u; i < MCS_MAX_NODES; ++i) {
        fs->nodes[i].used = 0u;
    }

    fs->nodes[0].used = 1u;
    fs->nodes[0].id = 0u;
    fs->nodes[0].parent = 0u;
    fs->nodes[0].type = MCS_VNODE_DIR;
    fs->nodes[0].name[0] = '\0';
    fs->nodes[0].size = 0u;
    fs->nodes[0].data_offset = 0u;
    fs->nodes[0].data_capacity = 0u;
}

int mcs_ramfs_lookup(mcs_ramfs_t *fs, const char *path, mcs_vnode_t **out) {
    if (fs == 0 || path == 0 || out == 0) {
        return MCS_EINVAL;
    }

    for (size_t i = 0u; i < fs->node_count; ++i) {
        if (fs->nodes[i].used != 0u &&
            mcs_strcmp(fs->nodes[i].name, path) == 0) {
            *out = &fs->nodes[i];
            return MCS_OK;
        }
    }

    return MCS_ENOENT;
}

int mcs_ramfs_create_file(mcs_ramfs_t *fs,
                          const char *path,
                          mcs_vnode_t **out) {
    mcs_vnode_t *existing = 0;

    if (fs == 0 || path == 0 || out == 0) {
        return MCS_EINVAL;
    }

    if (mcs_strlen(path) >= MCS_MAX_NAME) {
        return MCS_ENAMETOOLONG;
    }

    if (mcs_ramfs_lookup(fs, path, &existing) == MCS_OK) {
        *out = existing;
        return MCS_EEXIST;
    }

    if (fs->node_count >= MCS_MAX_NODES) {
        return MCS_ENOSPC;
    }

    mcs_vnode_t *node = &fs->nodes[fs->node_count];

    node->used = 1u;
    node->id = (uint32_t)fs->node_count;
    node->parent = 0u;
    node->type = MCS_VNODE_FILE;

    mcs_strcpy(node->name, path, MCS_MAX_NAME);

    node->size = 0u;
    node->data_offset = fs->data_used;
    node->data_capacity = 0u;

    *out = node;
    fs->node_count++;

    return MCS_OK;
}

int mcs_ramfs_seed_file(mcs_ramfs_t *fs,
                        const char *path,
                        const uint8_t *data,
                        size_t len) {
    mcs_vnode_t *node = 0;
    int rc;

    if (fs == 0 || path == 0) {
        return MCS_EINVAL;
    }

    rc = mcs_ramfs_create_file(fs, path, &node);

    if (rc == MCS_EEXIST) {
        rc = mcs_ramfs_lookup(fs, path, &node);
    }

    if (rc != MCS_OK) {
        return rc;
    }

    if (fs->data_used + len > MCS_RAMFS_DATA_BYTES) {
        return MCS_ENOSPC;
    }

    node->data_offset = fs->data_used;
    node->data_capacity = len;
    node->size = len;

    for (size_t i = 0u; i < len; ++i) {
        fs->data[fs->data_used + i] = data[i];
    }

    fs->data_used += len;

    return MCS_OK;
}
