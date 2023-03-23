#include "../../includes/isr.h"

ISRHandler g_Handlers[256];

char *exception_messages[] = {
    "Divide by zero error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception ",
    "",
    "",
    "",
    "",
    "",
    "",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    ""
};


void isr_handler(Registers* regs) {
    if(g_Handlers[regs->interrupt] != 0) {
        // print("test");
         g_Handlers[regs->interrupt](regs);
    }else {
        Panic(exception_messages[regs->interrupt]);
        asm("hlt");
    }
    
}

void install() {
    SetIDTGate(0, (uint64_t)isr0, 0x08, 0x8E);
    SetIDTGate(1, (uint64_t)isr1, 0x08, 0x8E);
    SetIDTGate(2, (uint64_t)isr2, 0x08, 0x8E);
    SetIDTGate(3, (uint64_t)isr3, 0x08, 0x8E);
    SetIDTGate(4, (uint64_t)isr4, 0x08, 0x8E);
    SetIDTGate(5, (uint64_t)isr5, 0x08, 0x8E);
    SetIDTGate(6, (uint64_t)isr6, 0x08, 0x8E);
    SetIDTGate(7, (uint64_t)isr7, 0x08, 0x8E);
    SetIDTGate(8, (uint64_t)isr8, 0x08, 0x8E);
    SetIDTGate(9, (uint64_t)isr9, 0x08, 0x8E);
    SetIDTGate(10, (uint64_t)isr10, 0x08, 0x8E);
    SetIDTGate(11, (uint64_t)isr11, 0x08, 0x8E);
    SetIDTGate(12, (uint64_t)isr12, 0x08, 0x8E);
    SetIDTGate(13, (uint64_t)isr13, 0x08, 0x8E);
    SetIDTGate(14, (uint64_t)isr14, 0x08, 0x8E);
    SetIDTGate(15, (uint64_t)isr15, 0x08, 0x8E);
    SetIDTGate(16, (uint64_t)isr16, 0x08, 0x8E);
    SetIDTGate(17, (uint64_t)isr17, 0x08, 0x8E);
    SetIDTGate(18, (uint64_t)isr18, 0x08, 0x8E);
    SetIDTGate(19, (uint64_t)isr19, 0x08, 0x8E);
    SetIDTGate(20, (uint64_t)isr20, 0x08, 0x8E);
    SetIDTGate(21, (uint64_t)isr21, 0x08, 0x8E);
    SetIDTGate(22, (uint64_t)isr22, 0x08, 0x8E);
    SetIDTGate(23, (uint64_t)isr23, 0x08, 0x8E);
    SetIDTGate(24, (uint64_t)isr24, 0x08, 0x8E);
    SetIDTGate(25, (uint64_t)isr25, 0x08, 0x8E);
    SetIDTGate(26, (uint64_t)isr26, 0x08, 0x8E);
    SetIDTGate(27, (uint64_t)isr27, 0x08, 0x8E);
    SetIDTGate(28, (uint64_t)isr28, 0x08, 0x8E);
    SetIDTGate(29, (uint64_t)isr29, 0x08, 0x8E);
    SetIDTGate(30, (uint64_t)isr30, 0x08, 0x8E);
    SetIDTGate(31, (uint64_t)isr31, 0x08, 0x8E);
    SetIDTGate(32, (uint64_t)isr32, 0x08, 0x8E);
    SetIDTGate(33, (uint64_t)isr33, 0x08, 0x8E);
    SetIDTGate(34, (uint64_t)isr34, 0x08, 0x8E);
    SetIDTGate(35, (uint64_t)isr35, 0x08, 0x8E);
    SetIDTGate(36, (uint64_t)isr36, 0x08, 0x8E);
    SetIDTGate(37, (uint64_t)isr37, 0x08, 0x8E);
    SetIDTGate(38, (uint64_t)isr38, 0x08, 0x8E);
    SetIDTGate(39, (uint64_t)isr39, 0x08, 0x8E);
    SetIDTGate(40, (uint64_t)isr40, 0x08, 0x8E);
    SetIDTGate(41, (uint64_t)isr41, 0x08, 0x8E);
    SetIDTGate(42, (uint64_t)isr42, 0x08, 0x8E);
    SetIDTGate(43, (uint64_t)isr43, 0x08, 0x8E);
    SetIDTGate(44, (uint64_t)isr44, 0x08, 0x8E);
    SetIDTGate(45, (uint64_t)isr45, 0x08, 0x8E);
    SetIDTGate(46, (uint64_t)isr46, 0x08, 0x8E);
    SetIDTGate(47, (uint64_t)isr47, 0x08, 0x8E);
    SetIDTGate(48, (uint64_t)isr48, 0x08, 0x8E);
    SetIDTGate(49, (uint64_t)isr49, 0x08, 0x8E);
    SetIDTGate(50, (uint64_t)isr50, 0x08, 0x8E);
}


void isr_registerhandler(int interrupt, ISRHandler handler) {
    g_Handlers[interrupt] = handler;
    // IDT_EnableGate(interrupt);
}