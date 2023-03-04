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

// void* calloc(size_t num, size_t size) {
//     void* ptr = malloc(num * size);
//     if (ptr) {
//         memset(ptr, 0, num * size);
//     }
//     return ptr;
// }

// void free(void* ptr) {
//     // implement your own memory freeing mechanism
// }