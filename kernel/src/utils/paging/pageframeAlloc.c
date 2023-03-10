#include "../../includes/pageframeAlloc.h"

uint64_t freeMemory;
uint64_t reservedMemory;
uint64_t usedMemory;
uint64_t Pindex = 0;
int Initialized = 0;

static bitmap_t PageBitmap;

void InitBitmap(size_t bitmapSize, void* bufferAddress) {
    PageBitmap.size = bitmapSize;
    PageBitmap.data = (uint8_t*)bufferAddress;
    for (int i = 0; i < bitmapSize; i++) {
        *(uint8_t*)(PageBitmap.data + i) = 0;
    }
}

void FreePage(void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if (Bitmap_get(&PageBitmap, index) == false) return;
    if(bitmam_set(&PageBitmap, index, false)){
        freeMemory += 4096;
        usedMemory -= 4096;
        if(Pindex > index) Pindex = index;
    }
}

void FreePages(void* address, uint64_t pageCount) {
    for(int i = 0; i < pageCount; i++) {
        FreePage((void*)((uint64_t)address + (i * 4096)));
    }
}

void LockPage(void* address) {
    uint64_t index = (uint64_t)address /4096;
    if(Bitmap_get(&PageBitmap, index) == true) return;
    if(bitmam_set(&PageBitmap, index, true)){
        freeMemory -= 4096;
        usedMemory += 4096;
    }
}

void LockPages(void* address, uint64_t pageCount) {
    for(int i = 0; i < pageCount; i++) {
        LockPage((void*)((uint64_t)address + (i * 4096)));
    }
}

void ReservePage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(Bitmap_get(&PageBitmap, index) == true) return;
    if(bitmam_set(&PageBitmap, index, true)){
        freeMemory -= 4096;
        reservedMemory += 4096;
    }
}

void ReservePages(void* address, uint64_t pageCount) {
    for(int i = 0; i < pageCount; i++) {
        ReservePage((void*)((uint64_t)address + (i * 4096)));
    }
}

void UnreservePage(void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if(Bitmap_get(&PageBitmap, index) == false) return;
    if(bitmam_set(&PageBitmap, index, false)){
        freeMemory += 4096;
        reservedMemory -= 4096;
        if(Pindex > index) Pindex = index;
    }
}

void UnreservePages(void* address, uint64_t pageCount) {
    for(int i = 0; i < pageCount; i++) {
        UnreservePage((void*)((uint64_t)address + (i * 4096)));
    }
}

void ReadEFIMemoryMap(EFI_MEMORY_DESCIPTOR* mMap, size_t mMapSize, size_t mMapDescSize) {
    if(Initialized) return;
    Initialized = true;

    uint64_t mMapEntries = mMapSize / mMapDescSize;
    void* largestFreeMemSeg = 0;
    size_t largestFreeMemSegSize = 0;

    for(int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCIPTOR* desc = (EFI_MEMORY_DESCIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        if(desc->type == 7) {
            if(desc->numPages * 4096 > largestFreeMemSegSize) {
                largestFreeMemSeg = desc->physAddr;
                largestFreeMemSegSize = desc->numPages * 4096;
            }
        }
    }

    uint64_t memorySize = GetMemorySize(mMap, mMapEntries, mMapDescSize);
    freeMemory = memorySize;

    uint64_t bitmap_size = memorySize / 406 / 8 + 1;

    InitBitmap(bitmap_size, largestFreeMemSeg);

    LockPages(&PageBitmap, PageBitmap.size / 4096 + 1);

    for (int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCIPTOR* desc = (EFI_MEMORY_DESCIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        if(desc->type != 7) {
            ReservePages(desc->physAddr, desc->numPages);
        }
    }

}

uint64_t GetFreeRam() {
    return freeMemory;
}

uint64_t GetUsedRam() {
    return usedMemory;
}

uint64_t GetReservedRam() {
    return reservedMemory;
}

void* RequestPage() {
    for (; Pindex < PageBitmap.size * 8; Pindex++)
    {
        if(Bitmap_get(&PageBitmap, Pindex) == true) continue;
        LockPage((void*)(Pindex * 4096));
        return (void*)(Pindex * 4096);
    }
    
    return 0;
}