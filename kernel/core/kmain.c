#include "../arch/x86_64/serial.h"
#include "../include/log.h"

static void halt_forever(void) {
    while (1) {
        __asm__ volatile ("hlt");
    }
}

void kmain(void) {
    serial_init();

    log_info("M3 kernel initialized");
    log_info("Serial logging active");

    halt_forever();
}
