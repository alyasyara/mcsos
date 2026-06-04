#include "pmm.h"

static uint8_t frame_bitmap[PMM_MAX_FRAMES];
static uint64_t free_frames;

void pmm_init(void) {
    for (uint64_t i = 0; i < PMM_MAX_FRAMES; i++) {
        frame_bitmap[i] = 0;
    }

    free_frames = PMM_MAX_FRAMES;
}

uint64_t pmm_alloc_frame(void) {
    for (uint64_t i = 0; i < PMM_MAX_FRAMES; i++) {
        if (frame_bitmap[i] == 0) {
            frame_bitmap[i] = 1;
            free_frames--;

            return i * PMM_FRAME_SIZE;
        }
    }

    return 0;
}

void pmm_free_frame(uint64_t frame) {
    uint64_t index = frame / PMM_FRAME_SIZE;

    if (index < PMM_MAX_FRAMES && frame_bitmap[index]) {
        frame_bitmap[index] = 0;
        free_frames++;
    }
}

uint64_t pmm_free_count(void) {
    return free_frames;
}
