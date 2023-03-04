#pragma once

#include "stdint.h"
#include "efiMemory.h"

uint64_t GetMemorySize(EFI_MEMORY_DESCIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize);