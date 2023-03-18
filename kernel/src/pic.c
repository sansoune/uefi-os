#include "includes/pic.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

void pic_remap(uint8_t offset1, uint8_t offset2) {
    uint8_t mask1, mask2;

    // Save the masks for later use.
    mask1 = inb(0x21);
    mask2 = inb(0xA1);

    // Send initialization command to the PIC.
    outb(0x20, 0x11);
    io_wait();
    outb(0xA0, 0x11);
    io_wait();

    // Set the interrupt offsets.
    outb(0x21, offset1);
    io_wait();
    outb(0xA1, offset2);
    io_wait();

    // Tell the master PIC that there is a slave PIC at IRQ2.
    outb(0x21, 0x04);
    io_wait();
    outb(0xA1, 0x02);
    io_wait();

    // Set the mode to 8086/88 (MCS-80/85) mode.
    outb(0x21, 0x01);
    io_wait();
    outb(0xA1, 0x01);
    io_wait();

    // Restore the masks.
    outb(0x21, mask1);
    io_wait();
    outb(0xA1, mask2);
    io_wait();
}