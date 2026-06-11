#include "vmm.h"

bool vmm_is_aligned_4k(uint64_t value) {
    return (value & (VMM_PAGE_SIZE - 1ULL)) == 0;
}

bool vmm_is_canonical(uint64_t vaddr) {
    uint64_t sign = (vaddr >> 47) & 1ULL;
    uint64_t upper = vaddr >> 48;

    if (sign) {
        return upper == 0xFFFFULL;
    }

    return upper == 0ULL;
}
