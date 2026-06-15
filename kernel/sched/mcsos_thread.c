#include "mcsos_thread.h"

static mcsos_thread_t *threads[MCSOS_MAX_THREADS];
static size_t thread_count;
static size_t current_index;

int mcsos_sched_init(void) {
    thread_count = 0;
    current_index = 0;

    return 0;
}

int mcsos_sched_add(mcsos_thread_t *thread) {
    if (thread == NULL) {
        return -1;
    }

    if (thread_count >= MCSOS_MAX_THREADS) {
        return -1;
    }

    thread->state = MCSOS_THREAD_READY;
    threads[thread_count++] = thread;

    return 0;
}

mcsos_thread_t *mcsos_sched_current(void) {
    if (thread_count == 0) {
        return NULL;
    }

    return threads[current_index];
}

void mcsos_sched_yield(void) {
    if (thread_count <= 1) {
        return;
    }

    current_index = (current_index + 1) % thread_count;
}
