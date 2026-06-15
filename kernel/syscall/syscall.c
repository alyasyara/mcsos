#include "mcsos/syscall.h"

static mcsos_syscall_ops_t g_ops;
static mcsos_user_region_t g_region;

void mcsos_syscall_init(const mcsos_syscall_ops_t *ops) {
    if (ops != NULL) {
        g_ops = *ops;
    }
}

void mcsos_syscall_set_user_region(mcsos_user_region_t region) {
    g_region = region;
}

int mcsos_user_check_range(uintptr_t addr, size_t len) {
    if (len == 0) {
        return MCSOS_OK;
    }

    if (addr < g_region.base) {
        return MCSOS_EFAULT;
    }

    if ((addr + len) > g_region.limit) {
        return MCSOS_EFAULT;
    }

    return MCSOS_OK;
}

int mcsos_copy_from_user(void *dst, const void *src, size_t len) {
    unsigned char *d;
    const unsigned char *s;
    size_t i;

    if (mcsos_user_check_range((uintptr_t)src, len) != MCSOS_OK) {
        return MCSOS_EFAULT;
    }

    d = (unsigned char *)dst;
    s = (const unsigned char *)src;

    for (i = 0; i < len; ++i) {
        d[i] = s[i];
    }

    return MCSOS_OK;
}
int64_t mcsos_syscall_dispatch(uint64_t nr,
                               uint64_t arg0,
                               uint64_t arg1,
                               uint64_t arg2,
                               uint64_t arg3,
                               uint64_t arg4,
                               uint64_t arg5) {
    (void)arg2;
    (void)arg3;
    (void)arg4;
    (void)arg5;

    switch (nr) {
    case MCSOS_SYS_PING:
        return 0x4D43534FULL;

    case MCSOS_SYS_GET_TICKS:
        if (g_ops.get_ticks == NULL) {
            return MCSOS_ENOSYS;
        }

        return (int64_t)g_ops.get_ticks();

    case MCSOS_SYS_WRITE_SERIAL:
        if (g_ops.write_serial == NULL) {
            return MCSOS_ENOSYS;
        }

        return g_ops.write_serial((const char *)arg0,
                                  (size_t)arg1);

    case MCSOS_SYS_YIELD:
        if (g_ops.yield_current == NULL) {
            return MCSOS_ENOSYS;
        }

        g_ops.yield_current();
        return MCSOS_OK;

    case MCSOS_SYS_EXIT_THREAD:
        if (g_ops.exit_current == NULL) {
            return MCSOS_ENOSYS;
        }

        g_ops.exit_current((int)arg0);
        return MCSOS_OK;

    default:
        return MCSOS_ENOSYS;
    }
}

void mcsos_syscall_dispatch_frame(mcsos_syscall_frame_t *frame) {
    if (frame == NULL) {
        return;
    }

    frame->ret = mcsos_syscall_dispatch(frame->nr,
                                        frame->arg0,
                                        frame->arg1,
                                        frame->arg2,
                                        frame->arg3,
                                        frame->arg4,
                                        frame->arg5);
}
