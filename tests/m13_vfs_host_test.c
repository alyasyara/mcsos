#include "mcs_vfs.h"

#include <assert.h>
#include <stdio.h>

static void test_ramfs_create_and_lookup(void) {
    mcs_ramfs_t fs;
    mcs_vnode_t *node = 0;
    int rc;

    mcs_ramfs_init(&fs);

    rc = mcs_ramfs_create_file(&fs, "/hello.txt", &node);
    assert(rc == MCS_OK);
    assert(node != 0);
    assert(node->type == MCS_VNODE_FILE);

    node = 0;
    rc = mcs_ramfs_lookup(&fs, "/hello.txt", &node);
    assert(rc == MCS_OK);
    assert(node != 0);

    printf("[PASS] create and lookup\n");
}

static void test_duplicate_create(void) {
    mcs_ramfs_t fs;
    mcs_vnode_t *node = 0;
    int rc;

    mcs_ramfs_init(&fs);

    rc = mcs_ramfs_create_file(&fs, "/dup.txt", &node);
    assert(rc == MCS_OK);

    rc = mcs_ramfs_create_file(&fs, "/dup.txt", &node);
    assert(rc == MCS_EEXIST);

    printf("[PASS] duplicate create\n");
}

static void test_lookup_missing(void) {
    mcs_ramfs_t fs;
    mcs_vnode_t *node = 0;
    int rc;

    mcs_ramfs_init(&fs);

    rc = mcs_ramfs_lookup(&fs, "/missing.txt", &node);
    assert(rc == MCS_ENOENT);

    printf("[PASS] lookup missing\n");
}

static void test_seed_file(void) {
    static const uint8_t data[] = {
        'M', 'C', 'S', 'O', 'S'
    };

    mcs_ramfs_t fs;
    mcs_vnode_t *node = 0;
    int rc;

    mcs_ramfs_init(&fs);

    rc = mcs_ramfs_seed_file(&fs,
                             "/seed.txt",
                             data,
                             sizeof(data));
    assert(rc == MCS_OK);

    rc = mcs_ramfs_lookup(&fs, "/seed.txt", &node);
    assert(rc == MCS_OK);
    assert(node != 0);
    assert(node->size == sizeof(data));

    printf("[PASS] seed file\n");
}

int main(void) {
    test_ramfs_create_and_lookup();
    test_duplicate_create();
    test_lookup_missing();
    test_seed_file();

    printf("[PASS] M13 VFS RAMFS host tests passed\n");

    return 0;
}
