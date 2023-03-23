#pragma once

#include "stdio.h"
#include "stdint.h"
#include "efiMemory.h"
#include "conversion.h"
#include "memory.h"
#include "bitmap.h"
#include "pageframeAlloc.h"
#include "paging.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "timer.h"
#include "panic.h"
#include "kb.h"
#include "mouse.h"
#include "pic.h"

typedef struct {
	FrameBuffer* framebuffer;
	PSF1_FONT* font;
	EFI_MEMORY_DESCIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescriptorSize;
} BootInfo;