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
    uint64_t ds;
    uint64_t rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax;
    uint64_t interrupt, error; 
    uint64_t rip, cs, rflags, rsp_user, ss; 
} __attribute__((packed)) Registers;

typedef void (*ISRHandler)(Registers* regs);

void install();