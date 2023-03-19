#include "../../includes/idt.h"

// Declare the IDT with 256 entries
IDTDescEntry IDT[256];
IDTR idt_ptr;

void SetIDTGate(uint16_t index, uint64_t handler, uint16_t sel, uint8_t flags) {
    IDTDescEntry* entry = &IDT[index];
    entry->offset0 = (uint16_t)(handler & 0xFFFF);
    entry->selector = sel; // Kernel code segment selector
    entry->ist = 0;
    entry->type_attr = flags; // Present, kernel mode, interrupt gate
    entry->offset1 = (uint16_t)((handler >> 16) & 0xFFFF);
    entry->offset2 = (uint32_t)(handler >> 32);
    entry->ignore = 0;
}

void IDTInit() {
    idt_ptr.Limit = sizeof(IDT) - 1;
    idt_ptr.Offset = IDT;

    memset(&IDT, 0, sizeof(IDTDescEntry) * 256);

    asm volatile("lidt %0" : : "m"(idt_ptr));
    
}