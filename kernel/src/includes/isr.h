#pragma once

#include "stdint.h"
#include "stdio.h"
#include "idt.h"
#include "panic.h"

extern void isr0();

typedef struct {
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;
} regs;

void install();