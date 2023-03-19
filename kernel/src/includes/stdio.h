#pragma once

#include "stdint.h"

typedef struct {
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelPerScanline;
} FrameBuffer;

typedef struct {
	unsigned char magic[2];
	unsigned char mode;
	unsigned char charSize;
} PSF1_HEADER;

typedef struct {
	PSF1_HEADER* psf1_header;
	void* glyphBuffer;
} PSF1_FONT;

typedef struct 
{
	unsigned int x;
	unsigned int y;
} Point;



void init_graphics(FrameBuffer* buffer, PSF1_FONT* font);
void print(const char* str);
void clear(uint32_t colorr);
void setColor(uint32_t clr);