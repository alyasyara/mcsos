#include "mcsos/kmem.h"

typedef struct kmem_block {
    uint64_t magic;
    size_t size;
    int free;
    struct kmem_block *next;
} kmem_block_t;

static unsigned char *g_heap_base;
static size_t g_heap_size;
static size_t g_heap_offset;

static size_t align_up(size_t value) {
    return (value + (KMEM_ALIGN - 1u)) & ~(KMEM_ALIGN - 1u);
}

int kmem_init(void *base, size_t bytes) {
    if (base == NULL || bytes == 0) {
        return -1;
    }

    g_heap_base = (unsigned char *)base;
    g_heap_size = bytes;
    g_heap_offset = 0;

    return 0;
}

void *kmem_alloc(size_t bytes) {
    void *ptr;
    size_t needed;

    if (bytes == 0) {
        return NULL;
    }

    needed = align_up(bytes);

    if (g_heap_offset + needed > g_heap_size) {
        return NULL;
    }

    ptr = g_heap_base + g_heap_offset;
    g_heap_offset += needed;

    return ptr;
}

void *kmem_calloc(size_t count, size_t bytes) {
    return kmem_alloc(count * bytes);
}

int kmem_free_checked(void *ptr) {
    if (ptr == NULL) {
        return -1;
    }

    return 0;
}

void kmem_get_stats(kmem_stats_t *out) {
    (void)out;
}

int kmem_validate(void) {
    return 0;
}
