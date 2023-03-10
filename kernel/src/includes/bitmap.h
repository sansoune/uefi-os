#pragma once
#include "stdint.h"

typedef struct {
    uint8_t* data;
    size_t size;
} bitmap_t;

bool Bitmap_get(bitmap_t* bitmap, uint64_t index);
bool bitmam_set(bitmap_t* bitmap,uint64_t index, bool value);
