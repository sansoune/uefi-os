#include "includes/io.h"

void outb(uint16_t port, uint8_t val){
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
    return;
}

uint8_t inb(uint16_t port) {
    uint8_t retVal;
    __asm__ volatile ("inb %1, %0" : "=a"(retVal) : "Nd"(port));
    return retVal;
}

void io_wait()
{
    asm volatile ("outb %%al, $0x80" : : "a"(0));
}