#include "includes/stdio.h"

void putchar(FrameBuffer* buffer, PSF1_FONT* font, unsigned int color, char chr, unsigned int x, unsigned int y) {
	unsigned int* pixPtr = (unsigned int*)buffer->BaseAddress;
	char* fontPtr = font->glyphBuffer + (chr * font->psf1_header->charSize);
	for (unsigned long yy = y; yy < y + 16 ; yy++)
	{
		for (unsigned long xx = x; xx < x + 8; xx++)
		{
			if((*fontPtr & (0b10000000 >> (xx - x))) > 0) {
				*(unsigned int*)(pixPtr + xx +(yy * buffer->PixelPerScanline)) = color;
			}
		}

		fontPtr++; 	
	}
	 
}

FrameBuffer* frame_buffer;
PSF1_FONT* text_font;

void init_graphics(FrameBuffer* buffer, PSF1_FONT* font) {
    frame_buffer = buffer;
    text_font = font;
}

Point CursorPosition;

unsigned int color = 0xffffffff;

void print(const char* str) {
	const char* chr = str;
	while (*chr != 0)
	{
        if(*chr == '\n') {
            CursorPosition.x = 0;
            CursorPosition.y += 16;
            chr+= 2;    
        }
		putchar(frame_buffer, text_font, color, *chr, CursorPosition.x, CursorPosition.y);
		CursorPosition.x += 8;
		if(CursorPosition.x + 8 > frame_buffer->Width) {
			CursorPosition.x = 0;
			CursorPosition.y += 16;
		}
		chr++;
	}
	
}

