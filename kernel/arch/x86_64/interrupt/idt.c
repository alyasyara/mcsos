#include "idt.h"

static struct idt_entry idt[256];
static struct idt_ptr idtr;

void idt_init(void) {
    idtr.limit = sizeof(idt) - 1;
    idtr.base = (uint64_t)&idt;
}
