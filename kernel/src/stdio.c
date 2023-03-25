#include "includes/stdio.h"

void putchar(FrameBuffer* buffer, PSF1_FONT* font, unsigned int color, char chr, unsigned int x, unsigned int y) {
	unsigned int* pixPtr = (unsigned int*)buffer->BaseAddress;
	char* fontPtr = (char*)font->glyphBuffer + (chr * font->psf1_header->charSize);
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

void setColor(uint32_t clr) {
	color = clr;
}

void clear(uint32_t colorr) {
	uint64_t fbase = (uint64_t)frame_buffer->BaseAddress;
	uint64_t bytesPerScanline = frame_buffer->PixelPerScanline * 4;
	uint64_t fbHeight = frame_buffer->Height;
	uint64_t fbsize = frame_buffer->BufferSize;

	for(int verticalLine = 0; verticalLine < fbHeight; verticalLine++) {
		uint64_t pixPtrBase = fbase + (bytesPerScanline * verticalLine);
		for(uint32_t* pixPtr = (uint32_t*)pixPtrBase; pixPtr < (uint32_t*)(pixPtrBase + bytesPerScanline); pixPtr++) {
			*pixPtr = colorr;
		}
	}
	CursorPosition.y = 0;
	CursorPosition.x = 0;
}

void scroll_line() {
    uint32_t* framebuffer = (uint32_t*)frame_buffer->BaseAddress;
    uint32_t* tmp = framebuffer;
	uint64_t line_size = frame_buffer->PixelPerScanline * sizeof(uint32_t);
    
    memcpy(tmp, tmp + 16 * frame_buffer->PixelPerScanline, line_size * (frame_buffer->Height - 16));
    tmp += (frame_buffer->Height - 16) * frame_buffer->PixelPerScanline;
    memset(tmp, 0, line_size * 16);
    CursorPosition.y -= 16;
}


void print(const char* str) {
	const char* chr = (char*)str;
	while (*chr != 0)
	{
        if(*chr == '\n') {
            CursorPosition.x = 0;
            CursorPosition.y += 16;
			if (CursorPosition.y >= frame_buffer->Height - 16) {
                scroll_line();
            }
            chr++;
			continue;    
        }
		putchar(frame_buffer, text_font, color, *chr, CursorPosition.x, CursorPosition.y);
		CursorPosition.x += 8;
		if(CursorPosition.x + 8 > frame_buffer->Width) {
			CursorPosition.x = 0;
			CursorPosition.y += 16;
			if (CursorPosition.y >= frame_buffer->Height - 16) {
                scroll_line();
            }
		}
		chr++;
	}
	
}

void putc(char c) {
	putchar(frame_buffer, text_font, color, c, CursorPosition.x, CursorPosition.y);
	CursorPosition.x += 8;
	if (CursorPosition.x + 8 > frame_buffer->Width)
	{
		CursorPosition.x = 0;
		CursorPosition.y +=16;
	}
	
}

