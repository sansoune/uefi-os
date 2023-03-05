#pragma once

#include "stdint.h"
#include "efiMemory.h"

uint64_t GetMemorySize(EFI_MEMORY_DESCIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize);
void memset(void* start, uint8_t value, uint64_t num);