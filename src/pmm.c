#include "pmm.h"

static uint64_t next_free_frame = 0x100000;

void pmm_init(void) {
    next_free_frame = 0x100000;
}

uint64_t pmm_alloc_frame(void) {
    uint64_t frame = next_free_frame;
    next_free_frame += PMM_FRAME_SIZE;
    return frame;
}

void pmm_free_frame(uint64_t frame) {
    (void)frame;
}
