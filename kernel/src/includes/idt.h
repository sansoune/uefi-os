#pragma once
#include "stdint.h"
#include "stdio.h"
#include "pageframeAlloc.h"
#include "memory.h"
#include "pic.h"

#define IDT_TA_InterruptGate 0b10001110
#define IDT_TA_CallGate 0b10001100
#define IDT_TA_TrapGate 0b10001111


typedef struct {
    uint16_t offset0;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset1;
    uint32_t offset2;
    uint32_t ignore;
} __attribute__((packed)) IDTDescEntry;

typedef struct {
    uint16_t Limit;
    IDTDescEntry* Offset;
} __attribute__((packed)) IDTR;


void IDTInit();
void SetIDTGate(uint16_t index, uint64_t handler, uint16_t sel, uint8_t flags);