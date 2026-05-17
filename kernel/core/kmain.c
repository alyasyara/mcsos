#include "../limine/limine.h"

void serial_init();
void serial_write(const char* str);


void kmain(void);
void _start(void) __attribute__((alias("kmain")));
__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

static void halt_forever() {
    while (1) {
        __asm__ volatile ("hlt");
    }
}

void kmain(void) {
    serial_init();

    serial_write("[MCSOS M2] Kernel boot success\n");
    serial_write("[MCSOS M2] Early serial console active\n");

    halt_forever();
}
