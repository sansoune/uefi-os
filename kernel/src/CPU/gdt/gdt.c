#include "../../includes/gdt.h"



GDT DefaultGDT = {
    {0,0,0, 0x00, 0x00, 0},
    {0,0,0, 0x9a, 0xa0, 0},
    {0,0,0, 0x92, 0xa0, 0},
    {0,0,0, 0x00, 0x00, 0},
    {0,0,0, 0x9a, 0xa0, 0},
    {0,0,0, 0x92, 0xa0, 0},
};

void GDTInit() {
    GDTDescriptor gdtDescriptor;
    gdtDescriptor.size = sizeof(GDT) - 1;
    gdtDescriptor.offset = (uint64_t)&DefaultGDT;
    LoadGDT(&gdtDescriptor);
}