#pragma once
#include "stdint.h"

typedef struct {
    uint16_t size;
    uint64_t offset;
} __attribute__((packed)) GDTDescriptor;

typedef struct {
    uint16_t Limit0;
    uint16_t Base0;
    uint8_t Base1;
    uint8_t AccessByte;
    uint8_t Limit1_Flags;
    uint8_t Base2;
} __attribute__((packed)) GDTEntry;

typedef struct {
    GDTEntry Null;
    GDTEntry KernelCode;
    GDTEntry KernelData;
    GDTEntry UseNull;
    GDTEntry UserCode;
    GDTEntry UserData;
} __attribute__((packed)) GDT;

extern GDT DefaultGDT;
void GDTInit();