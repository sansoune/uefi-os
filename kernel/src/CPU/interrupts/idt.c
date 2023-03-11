#include "../../includes/idt.h"

// Declare the IDT with 256 entries
IDTDescEntry IDT[256];
IDTR idt_ptr;

// Declare an Interrupt Stack Table
uint64_t ist[7][4096];

// Declare the Interrupt Service Routine
extern void isr0();

// Define the Interrupt Service Routine
void ISR0_Handler() {
    print("Division by zero exception\n");
}

void SetIDTGate(uint16_t index, uint64_t handler) {
    IDT[index].offset0 = (uint16_t)(handler & 0xFFFF);
    IDT[index].selector = 0x08; // Kernel code segment selector
    IDT[index].ist = 0;
    IDT[index].type_attr = 0x8E; // Present, kernel mode, interrupt gate
    IDT[index].offset1 = (uint16_t)((handler >> 16) & 0xFFFF);
    IDT[index].offset2 = (uint32_t)(handler >> 32);
    IDT[index].ignore = 0;
}

void IDTInit() {
    idt_ptr.Limit = sizeof(IDT) - 1;
    idt_ptr.Offset = (void*)IDT;

    memset(&IDT, 0, sizeof(IDTDescEntry) * 256);
    SetIDTGate(0, (uint64_t)isr0);

    asm volatile("lidt %0" : : "m"(idt_ptr));
}