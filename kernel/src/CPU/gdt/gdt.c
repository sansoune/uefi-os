#include "../../includes/gdt.h"

GDTEntry gdt[6];
GDTDescriptor gdtr;

GDT DefaultGDT = {
    {0,0,0, 0x00, 0x00, 0},
    {0,0,0, 0x9a, 0xa0, 0},
    {0,0,0, 0x92, 0xa0, 0},
    {0,0,0, 0x00, 0x00, 0},
    {0,0,0, 0x9a, 0xa0, 0},
    {0,0,0, 0x92, 0xa0, 0},
};

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].Base0 = (base & 0xFFFF);
    gdt[num].Base1 = (base >> 16) & 0xFF;
    gdt[num].Base2 = (base >> 24) & 0xFF;

    gdt[num].Limit0 = (limit & 0xFFFF);
    gdt[num].Limit1_Flags = (limit >> 16) & 0x0F;

    gdt[num].Limit1_Flags |= gran & 0xF0;
    gdt[num].AccessByte = access;
}

void GDTInit() {
    gdtr.size = (sizeof(GDTEntry) * 3) - 1;
    gdtr.offset = (uint32_t)&gdt;

    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_gate(3, 0, 0, 0, 0);
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_gate(5, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    // LoadGDT(&gdtDescriptor);
    __asm__ volatile("lgdt %0" : : "m"(gdtr));
}