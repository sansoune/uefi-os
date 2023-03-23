#pragma once

#include "stdint.h"
#include "stdio.h"
#include "conversion.h"
#include "idt.h"
#include "panic.h"

extern void isr0();
extern void isr14();

typedef struct 
{
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbp, rbx, rdx, rcx, rax;
    uint64_t error, interrupt, ignore; 
    uint64_t rip, cs, rflags, rsp, ss; 
} __attribute__((packed)) Registers;

typedef void (*ISRHandler)(Registers* regs);

void install();
