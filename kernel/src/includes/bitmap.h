#pragma once
#include "stdint.h"

typedef struct {
    uint8_t* data;
    size_t size;
} bitmap_t;

int Bitmap_get(bitmap_t* bitmap, uint64_t index);
void bitmam_set(bitmap_t* bitmap,uint64_t index, int value);
