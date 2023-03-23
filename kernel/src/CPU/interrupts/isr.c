#include "../../includes/isr.h"

void isr0_handler() {
    Panic("deviding by zero exeption\n");
    for(;;);
}
void isr1_handler() {
    Panic("Debug\n");
    for(;;);
}
void isr2_handler() {
    Panic("Non-maskable interrupt\n");
    for(;;);
}
void isr3_handler() {
    Panic("Breakpoint\n");
    for(;;);
}
void isr4_handler() {
    Panic("Overflow\n");
    for(;;);
}
void isr5_handler() {
    Panic("Bound range exceeded\n");
    for(;;);
}
void isr6_handler() {
    Panic("Invalid opcode\n");
    for(;;);
}
void isr7_handler() {
    Panic("Device not available\n");
    for(;;);
}
void isr8_handler() {
    Panic("Double fault\n");
    for(;;);
}
void isr9_handler() {
    Panic("Coprocessor segment overrun\n");
    for(;;);
}
void isr10_handler() {
    Panic("Invalid TSS\n");
    for(;;);
}
void isr11_handler() {
    Panic("Segment not present\n");
    for(;;);
}
void isr12_handler() {
    Panic("Stack-segment fault\n");
    for(;;);
}
void isr13_handler() {
    Panic("General protection fault\n");
    for(;;);
}
void isr14_handler() {
    Panic("Page fault\n");
    for(;;);
}
void isr15_handler() {
    Panic("Reserved1\n");
    for(;;);
}
void isr16_handler() {
    Panic("x87 floating-point exception\n");
    for(;;);
}
void isr17_handler() {
    Panic("Alignment check\n");
    for(;;);
}
void isr18_handler() {
    Panic("Machine check\n");
    for(;;);
}
void isr19_handler() {
    Panic("SIMD floating-point exception\n");
    for(;;);
}
void isr20_handler() {
    Panic("Virtualization exception\n");
    for(;;);
}
void isr21_handler() {
    Panic("Control Protection Exception\n");
    for(;;);
}
void isr22_handler() {
    Panic("Reserved2\n");
    for(;;);
}
void isr23_handler() {
    Panic("Reserved3\n");
    for(;;);
}
void isr24_handler() {
    Panic("Reserved4\n");
    for(;;);
}
void isr25_handler() {
    Panic("Reserved5\n");
    for(;;);
}
void isr26_handler() {
    Panic("Reserved6\n");
    for(;;);
}
void isr27_handler() {
    Panic("Reserved7\n");
    for(;;);
}
void isr28_handler() {
    Panic("Hypervisor Injection Exception\n");
    for(;;);
}
void isr29_handler() {
    Panic("VMM Communication Exception\n");
    for(;;);
}
void isr30_handler() {
    Panic("Security exception\n");
    for(;;);
}
void isr31_handler() {
    Panic("Reserved8\n");
    for(;;);
}

void isr_handler(Registers* regs) {
    print("Error: ");
    print(toString(regs->error));
    print(", Vector: ");
    print(toString(regs->interrupt));
    print(" ");
    print("test");
}

void install() {
    SetIDTGate(0, (uint64_t)isr0, 0x08, 0x8E);
    SetIDTGate(1, (uint64_t)isr1_handler, 0x08, 0x8E);
    SetIDTGate(2, (uint64_t)isr2_handler, 0x08, 0x8E);
    SetIDTGate(3, (uint64_t)isr3_handler, 0x08, 0x8E);
    SetIDTGate(4, (uint64_t)isr4_handler, 0x08, 0x8E);
    SetIDTGate(5, (uint64_t)isr5_handler, 0x08, 0x8E);
    SetIDTGate(6, (uint64_t)isr6_handler, 0x08, 0x8E);
    SetIDTGate(7, (uint64_t)isr7_handler, 0x08, 0x8E);
    SetIDTGate(8, (uint64_t)isr8_handler, 0x08, 0x8E);
    SetIDTGate(9, (uint64_t)isr9_handler, 0x08, 0x8E);
    SetIDTGate(10, (uint64_t)isr10_handler, 0x08, 0x8E);
    SetIDTGate(11, (uint64_t)isr11_handler, 0x08, 0x8E);
    SetIDTGate(12, (uint64_t)isr12_handler, 0x08, 0x8E);
    SetIDTGate(13, (uint64_t)isr13_handler, 0x08, 0x8E);
    SetIDTGate(14, (uint64_t)isr14, 0x08, 0x8E);
    SetIDTGate(15, (uint64_t)isr15_handler, 0x08, 0x8E);
    SetIDTGate(16, (uint64_t)isr16_handler, 0x08, 0x8E);
    SetIDTGate(17, (uint64_t)isr17_handler, 0x08, 0x8E);
    SetIDTGate(18, (uint64_t)isr18_handler, 0x08, 0x8E);
    SetIDTGate(19, (uint64_t)isr19_handler, 0x08, 0x8E);
    SetIDTGate(20, (uint64_t)isr20_handler, 0x08, 0x8E);
    SetIDTGate(21, (uint64_t)isr21_handler, 0x08, 0x8E);
    SetIDTGate(22, (uint64_t)isr22_handler, 0x08, 0x8E);
    SetIDTGate(23, (uint64_t)isr23_handler, 0x08, 0x8E);
    SetIDTGate(24, (uint64_t)isr24_handler, 0x08, 0x8E);
    SetIDTGate(25, (uint64_t)isr25_handler, 0x08, 0x8E);
    SetIDTGate(26, (uint64_t)isr26_handler, 0x08, 0x8E);
    SetIDTGate(27, (uint64_t)isr27_handler, 0x08, 0x8E);
    SetIDTGate(28, (uint64_t)isr28_handler, 0x08, 0x8E);
    SetIDTGate(29, (uint64_t)isr29_handler, 0x08, 0x8E);
    SetIDTGate(30, (uint64_t)isr30_handler, 0x08, 0x8E);
    SetIDTGate(31, (uint64_t)isr31_handler, 0x08, 0x8E);
}
