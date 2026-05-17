#include "../include/log.h"
#include "../arch/x86_64/serial.h"

void log_info(const char *msg) {
    serial_write_string("[INFO] ");
    serial_write_string(msg);
    serial_write_string("\n");
}

void log_error(const char *msg) {
    serial_write_string("[ERROR] ");
    serial_write_string(msg);
    serial_write_string("\n");
}
