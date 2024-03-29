#include "../includes/memory.h"

uint64_t GetMemorySize(EFI_MEMORY_DESCIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize) {
    static uint64_t memorySizeBytes = 0;

    if(memorySizeBytes > 0) {
        return memorySizeBytes;
    }

    for (int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCIPTOR* desc = (EFI_MEMORY_DESCIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        memorySizeBytes += desc->numPages * 4096;
    }

    return memorySizeBytes;
}

void memset(void* start, uint8_t value, uint64_t num) {
    for (uint64_t i = 0; i < num; i++) {
        ((uint8_t*)start)[i] = value;
    }
}

void memcpy(void* dest, void* source, int count) {
      for (int i = 0; i < count; i++){
	   ((uint8_t*)dest)[i] = ((uint8_t*)source)[i];
      }
}
