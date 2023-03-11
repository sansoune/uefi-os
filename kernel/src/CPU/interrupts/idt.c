#include "../../includes/idt.h"

IDTDescEntry idt_entries[256];
IDTR idt_ptr;

void isr_handler(void) {
    print("an isr justtriggered");
    while (true);
}

void idt_set_gate(uint8_t num, uint64_t base, uint16_t selector, uint8_t ist, uint8_t flags) {
    idt_entries[num].offset0 = base & 0xFFFF;
    idt_entries[num].selector = selector;
    idt_entries[num].ist = ist;
    idt_entries[num].type_attr = flags;
    idt_entries[num].offset1 = (base >> 16) & 0xFFFF;
    idt_entries[num].offset2 = (base >> 32) & 0xFFFFFFFF;
    idt_entries[num].ignore = 0;
}

void PrepareInterrupts() {
    memset(&idt_entries, 0, sizeof(idt_entries));
    idt_ptr.Limit = sizeof(idt_entries) - 1;
    idt_ptr.Offset = (uint64_t)&idt_entries;
    idt_set_gate(0x0E, (uint64_t)isr_handler, 0x08, 0, IDT_TA_InterruptGate);

    __asm__ volatile("lidt %0" : : "m"(idt_ptr));

}