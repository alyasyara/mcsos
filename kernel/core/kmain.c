#include "../arch/x86_64/serial.h"
#include "../arch/x86_64/interrupt/idt.h"
#include "../include/log.h"

static void halt_forever(void) {
    while (1) {
        __asm__ volatile ("hlt");
    }
}

void kmain(void) {
    serial_init();

    idt_init();

    log_info("M6 kernel initialized");
    log_info("Interrupt handler active");

    __asm__ volatile ("int $0x3");

    halt_forever();
}
