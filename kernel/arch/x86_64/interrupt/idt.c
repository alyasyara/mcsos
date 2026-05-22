#include "idt.h"

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void isr_stub(void);

static void set_idt_gate(int n, uint64_t handler) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector = 0x28;
    idt[n].ist = 0;
    idt[n].type_attributes = 0x8E;
    idt[n].offset_mid = (handler >> 16) & 0xFFFF;
    idt[n].offset_high = (handler >> 32) & 0xFFFFFFFF;
    idt[n].zero = 0;
}

void idt_init(void) {
    set_idt_gate(0, (uint64_t)isr_stub);

    idtp.limit = sizeof(idt) - 1;
    idtp.base = (uint64_t)&idt;

    __asm__ volatile("lidt %0" : : "m"(idtp));
}
