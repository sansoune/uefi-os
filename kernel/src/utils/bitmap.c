#include "../includes/bitmap.h"

bool Bitmap_get(bitmap_t* bitmap, uint64_t index) {
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    if ((bitmap->data[byteIndex] & bitIndexer) > 0) {
        return true;
    }
    return false;
}

void bitmam_set(bitmap_t* bitmap,uint64_t index, bool value) {
    uint64_t Byteindex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    bitmap->data[Byteindex] &= ~bitIndexer;
    if(value) {
        bitmap->data[Byteindex] |= bitIndexer;
    }
}