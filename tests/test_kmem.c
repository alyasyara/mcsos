#include <stdio.h>
#include <stdint.h>

#include "mcsos/kmem.h"

static unsigned char heap[4096];

int main(void) {
    void *p1;
    void *p2;

    if (kmem_init(heap, sizeof(heap)) != 0) {
        puts("kmem_init failed");
        return 1;
    }

    p1 = kmem_alloc(64);
    p2 = kmem_alloc(128);

    if (p1 == NULL || p2 == NULL) {
        puts("kmem_alloc failed");
        return 1;
    }

    if (kmem_free_checked(p1) != 0) {
        puts("kmem_free_checked failed");
        return 1;
    }

    puts("M8 kmem host tests: PASS");

    return 0;
}
