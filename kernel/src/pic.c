#include "includes/pic.h"



void pic_remap() {
    uint8_t mask1, mask2;

    // Save the masks for later use.
    mask1 = inb(PIC1_DATA);
    io_wait();
    mask2 = inb(PIC2_DATA);

    // Send initialization command to the PIC.
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    // Set the interrupt offsets.
    outb(PIC1_DATA, 0x20);
    io_wait();
    outb(PIC2_DATA, 0x28);
    io_wait();

    // Tell the master PIC that there is a slave PIC at IRQ2.
    outb(PIC1_DATA, 0x04);
    io_wait();
    outb(PIC2_DATA, 0x02);
    io_wait();

    // Set the mode to 8086/88 (MCS-80/85) mode.
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    // Restore the masks.
    outb(PIC1_DATA, mask1);
    io_wait();
    outb(PIC2_DATA, mask2);
    io_wait();
}

void PIC_EndMaster() {
    outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_End_Slave() {
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_Unmask(int irq) {
    uint8_t port;

    if (irq < 8) {
        port = PIC1_DATA;
    }
    else {
        irq -= 8;
        port = PIC2_DATA;
    }
    uint8_t mask = inb(port);
    outb(port, mask & ~(1 << irq));
}