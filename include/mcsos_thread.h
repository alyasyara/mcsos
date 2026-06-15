#ifndef MCSOS_THREAD_H
#define MCSOS_THREAD_H

#include <stdint.h>
#include <stddef.h>

#define MCSOS_THREAD_READY    0
#define MCSOS_THREAD_RUNNING  1
#define MCSOS_THREAD_BLOCKED  2
#define MCSOS_THREAD_EXITED   3

#define MCSOS_MAX_THREADS 16

typedef struct mcsos_context {
    uint64_t rsp;
    uint64_t rbp;
    uint64_t rbx;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
} mcsos_context_t;

typedef struct mcsos_thread {
    uint32_t tid;
    uint32_t state;
    void (*entry)(void *);
    void *arg;
    mcsos_context_t context;
} mcsos_thread_t;

int mcsos_sched_init(void);
int mcsos_sched_add(mcsos_thread_t *thread);
mcsos_thread_t *mcsos_sched_current(void);
void mcsos_sched_yield(void);

#endif
