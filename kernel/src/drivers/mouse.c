// #include "../includes/mouse.h"

// void mouse_wait() {
//     uint64_t timeout = 100000;
//     while (timeout--)
//     {
//         if((inb(0x64) & 0b10) == 0) {
//             return;
//         }
//     }
    
// }

// void mouse_wait_input() {
//     uint64_t timeout = 100000;
//     while (timeout--)
//     {
//         if(inb(0x64) & 0b1) {
//             return;
//         }
//     }
    
// }

// void mouse_write(uint8_t value) {
//     mouse_wait();
//     outb(0x64, 0xD4);
//     mouse_wait();
//     outb(0x64, value);
// }

// uint8_t mouse_read() {
//     mouse_wait_input();
//     return inb(0x60);
// }

// void init_mouse() {
//     outb(0x64, 0xA8);
//     mouse_wait();
//     outb(0x64, 0x20);
//     mouse_wait_input();
//     uint8_t status = inb(0x60);
//     status |= 0b10;
//     mouse_wait();
//     outb(0x64, 0x60);
//     mouse_wait();
//     outb(0x60, status); 
//     mouse_write(0xF6);
//     mouse_read();
//     mouse_write(0xF4);
//     mouse_read();
// }

// void mouse_handler() {
//     asm("cli");
//     asm("cld");
//     uint8_t mouseData = inb(0x60);
//     print("m");
//     PIC_End_Slave();
//     asm("sti");
// }