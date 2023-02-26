#pragma once

#include "stdio.h"
#include "stdint.h"
#include "efiMemory.h"
#include "conversion.h"

typedef struct {
	FrameBuffer* framebuffer;
	PSF1_FONT* font;
	void* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescriptorSize;
} BootInfo;