#pragma once 
#include "stdio.h"
#include "stdint.h"
#include "pic.h"
#include "isr.h"

typedef void (*IRQHandler)(Registers* regs);

void IRQ_INIT();
void IRQ_RegisterHandler(int irq, IRQHandler handler);