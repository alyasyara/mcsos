#include <stdio.h>

#include "mcsos/syscall.h"

static uint64_t fake_ticks(void) {
    return 1234;
}

static int64_t fake_write(const char *buf, size_t len) {
    (void)buf;
    return (int64_t)len;
}

static void fake_yield(void) {
}

static void fake_exit(int code) {
    (void)code;
}

int main(void) {
    mcsos_syscall_ops_t ops;
    int64_t ret;

    ops.get_ticks = fake_ticks;
    ops.yield_current = fake_yield;
    ops.exit_current = fake_exit;
    ops.write_serial = fake_write;

    mcsos_syscall_init(&ops);

    ret = mcsos_syscall_dispatch(MCSOS_SYS_PING,
                                 0, 0, 0, 0, 0, 0);

    if (ret != 0x4D43534FULL) {
        puts("PING failed");
        return 1;
    }

    ret = mcsos_syscall_dispatch(MCSOS_SYS_GET_TICKS,
                                 0, 0, 0, 0, 0, 0);

    if (ret != 1234) {
        puts("GET_TICKS failed");
        return 1;
    }

    ret = mcsos_syscall_dispatch(MCSOS_SYS_WRITE_SERIAL,
                                 (uint64_t)"abc",
                                 3,
                                 0, 0, 0, 0);

    if (ret != 3) {
        puts("WRITE_SERIAL failed");
        return 1;
    }

    puts("M10 syscall host tests: PASS");

    return 0;
}
