#include <stdio.h>

#include "mcsos_thread.h"

static void dummy(void *arg) {
    (void)arg;
}

int main(void) {
    mcsos_thread_t t1;
    mcsos_thread_t t2;

    if (mcsos_sched_init() != 0) {
        puts("sched_init failed");
        return 1;
    }

    t1.entry = dummy;
    t1.arg = NULL;

    t2.entry = dummy;
    t2.arg = NULL;

    if (mcsos_sched_add(&t1) != 0) {
        puts("sched_add t1 failed");
        return 1;
    }

    if (mcsos_sched_add(&t2) != 0) {
        puts("sched_add t2 failed");
        return 1;
    }

    if (mcsos_sched_current() != &t1) {
        puts("current thread failed");
        return 1;
    }

    mcsos_sched_yield();

    if (mcsos_sched_current() != &t2) {
        puts("yield failed");
        return 1;
    }

    puts("M9 scheduler host tests: PASS");

    return 0;
}
