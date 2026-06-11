#include "vmm.h"

static void vmm_zero_page(uint64_t *page) {
    for (size_t i = 0; i < VMM_ENTRIES_PER_TABLE; i++) {
        page[i] = 0;
    }
}

bool vmm_is_aligned_4k(uint64_t value) {
    return (value & (VMM_PAGE_SIZE - 1ULL)) == 0;
}

bool vmm_is_canonical(uint64_t vaddr) {
    uint64_t sign = (vaddr >> 47) & 1ULL;
    uint64_t upper = vaddr >> 48;

    return sign ? (upper == 0xFFFFULL) : (upper == 0ULL);
}

static unsigned idx_pml4(uint64_t vaddr) {
    return (unsigned)((vaddr >> 39) & 0x1FFULL);
}

static unsigned idx_pdpt(uint64_t vaddr) {
    return (unsigned)((vaddr >> 30) & 0x1FFULL);
}

static unsigned idx_pd(uint64_t vaddr) {
    return (unsigned)((vaddr >> 21) & 0x1FFULL);
}

static unsigned idx_pt(uint64_t vaddr) {
    return (unsigned)((vaddr >> 12) & 0x1FFULL);
}

static uint64_t *table_from_phys(struct vmm_space *space,
                                 uint64_t paddr) {
    if (space == 0 ||
        space->phys_to_virt == 0 ||
        !vmm_is_aligned_4k(paddr)) {
        return 0;
    }

    return (uint64_t *)space->phys_to_virt(space->ctx, paddr);
}

int vmm_space_init(struct vmm_space *space,
                   uint64_t root_paddr,
                   void *ctx,
                   vmm_alloc_frame_fn alloc_frame,
                   vmm_free_frame_fn free_frame,
                   vmm_phys_to_virt_fn phys_to_virt) {
    if (space == 0 ||
        !vmm_is_aligned_4k(root_paddr) ||
        phys_to_virt == 0) {
        return VMM_ERR_INVAL;
    }

    space->root_paddr = root_paddr;
    space->ctx = ctx;
    space->alloc_frame = alloc_frame;
    space->free_frame = free_frame;
    space->phys_to_virt = phys_to_virt;

    return VMM_MAP_OK;
}
int vmm_query_page(struct vmm_space *space,
                   uint64_t vaddr,
                   struct vmm_mapping *out) {
    (void)space;
    (void)vaddr;
    (void)out;

    return VMM_ERR_NOT_FOUND;
}

int vmm_map_page(struct vmm_space *space,
                 uint64_t vaddr,
                 uint64_t paddr,
                 uint64_t flags) {
    (void)space;
    (void)flags;

    if (!vmm_is_canonical(vaddr) ||
        !vmm_is_aligned_4k(vaddr) ||
        !vmm_is_aligned_4k(paddr)) {
        return VMM_ERR_INVAL;
    }

    return VMM_MAP_OK;
}

int vmm_unmap_page(struct vmm_space *space,
                   uint64_t vaddr) {
    (void)space;

    if (!vmm_is_canonical(vaddr) ||
        !vmm_is_aligned_4k(vaddr)) {
        return VMM_ERR_INVAL;
    }

    return VMM_MAP_OK;
}

void vmm_invalidate_page(uint64_t vaddr) {
    (void)vaddr;
}

uint64_t vmm_read_cr3(void) {
    return 0;
}

void vmm_write_cr3(uint64_t value) {
    (void)value;
}

uint64_t vmm_read_cr2(void) {
    return 0;
}
