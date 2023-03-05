#pragma once
#include "stdint.h"

typedef struct 
{
    bool present : 1;
    bool ReadWirte : 1;
    bool UserSuper : 1;
    bool WrightThrough : 1;
    bool CacheDisabled : 1;
    bool Accessed : 1;
    bool ignore0 : 1;
    bool LargerPges : 1;
    bool ignore1 : 1;
    uint8_t available : 3;
    uint64_t Address : 52;
} __attribute__((packed)) PageDirectoryEntry;

typedef struct {
    PageDirectoryEntry entries [512];
} __attribute__((aligned(0x1000))) PageTable;

typedef struct 
{
    uint64_t PDP_i;
    uint64_t PD_i;
    uint64_t PT_i;
    uint64_t P_i;
} PageIndexer;

typedef struct {
    PageTable* PML4;
} PageTableManager;

PageIndexer PageMapIndexer(uint64_t virtualAddress);

PageTableManager PageTableManageer(PageTable* PML4Address);
void MapMemory(void* virtualMemory, void* physicalMemory, PageTableManager manager);
void switchPML4(PageTable* PML4);
