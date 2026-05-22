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
    
    int x = 1 / 0;
    log_info("M3 kernel initialized");
    log_info("Serial logging active");

    halt_forever();
}
