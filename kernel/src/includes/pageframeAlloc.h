#pragma once
#include "efiMemory.h"
#include "stdint.h"
#include "bitmap.h"
#include "memory.h"

typedef struct {
    bitmap_t* PageBitmap;
} PageFrameAllocator;

void ReadEFIMemoryMap(EFI_MEMORY_DESCIPTOR* mMap, size_t mMapSize, size_t mMapDescSize);
void FreePage(void* address);
void LockPage(void* address);
void FreePages(void* address, uint64_t pageCount);
void LockPages(void* address, uint64_t pageCount);
void* RequestPage();
uint64_t GetFreeRam();
uint64_t GetUsedRam();
uint64_t GetReservedRam();