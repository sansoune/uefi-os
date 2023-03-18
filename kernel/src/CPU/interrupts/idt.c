#include "../../includes/idt.h"

// Declare the IDT with 256 entries
IDTDescEntry IDT[256];
IDTR idt_ptr;

// Define the Interrupt Service Routine
void ISR0_Handler() {
    print("Division by zero exception\n");
    // asm("hlt");
    while (true);
}
void DoubleFaultHandler() {
    // Perform error handling for double fault
    print("double fault");
    while(true);
}

void DoubleFaultISR() {
    DoubleFaultHandler();
}

void SetIDTGate(uint16_t index, uint64_t handler) {
    IDTDescEntry* entry = &IDT[index];
    entry->offset0 = (uint16_t)(handler & 0xFFFF);
    entry->selector = 0x08; // Kernel code segment selector
    entry->ist = 0;
    entry->type_attr = 0x8E; // Present, kernel mode, interrupt gate
    entry->offset1 = (uint16_t)((handler >> 16) & 0xFFFF);
    entry->offset2 = (uint32_t)(handler >> 32);
    entry->ignore = 0;
}

void IDTInit() {

    // asm("cli");

    

    idt_ptr.Limit = sizeof(IDT) - 1;
    idt_ptr.Offset = IDT;

    memset(&IDT, 0, sizeof(IDTDescEntry) * 256);
    // for (int i = 0; i < 256; i++)
    // {
    //     SetIDTGate(i, (uint64_t)hand);
    // }
    
    SetIDTGate(0, (uint64_t)isr0);
    SetIDTGate(8, (uint64_t)DoubleFaultISR);

    asm volatile("lidt %0" : : "m"(idt_ptr));

    // pic_remap(0x20, 0x28);

    // asm("sti");
}