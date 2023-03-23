#pragma once

#include "stdint.h"
#include "io.h"
#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

#define PIC_EOI 0x20

// void pic_remap();
// void PIC_Unmask(int irq);
// void PIC_EndMaster();
// void PIC_End_Slave();

void PIC_configure(uint8_t offsetPic1, uint8_t offsetPic2);
void PIC_SendEndOfInterrupt(int irq);
void PIC_Disable();
void PIC_Mask(int irq);
void PIC_Unmask(int irq);
uint16_t PIC_ReadIRQRequestRegister();
uint16_t PIC_ReadInServiceRegister();