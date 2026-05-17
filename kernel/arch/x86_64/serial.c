#include <stdint.h>
#include "io.h"

#define COM1 0x3F8

static int is_transmit_empty() {
    return inb(COM1 + 5) & 0x20;
}

void serial_write_char(char c) {
    while (is_transmit_empty() == 0);

    outb(COM1, c);
}

void serial_write(const char* str) {
    while (*str) {
        serial_write_char(*str++);
    }
}

void serial_init() {
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x03);
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);
}
