#include "../../includes/paging.h"
#include "../../includes/pageframeAlloc.h"
#include "../../includes/memory.h"
#include "../../includes/stdio.h"


PageIndexer PageMapIndexer(uint64_t virtualAddress) {
    PageIndexer indexer;
    virtualAddress >>= 12;
    indexer.P_i = virtualAddress & 0x1ff;
    virtualAddress >>= 9;
    indexer.PT_i = virtualAddress & 0x1ff;
    virtualAddress >>= 9;
    indexer.PD_i = virtualAddress & 0x1ff;
    virtualAddress >>= 9;
    indexer.PDP_i = virtualAddress & 0x1ff;
    return indexer;
}

PageTableManager PageTableManageer(PageTable* PML4Address) {
    PageTableManager manager;
    manager.PML4 = PML4Address;
    return manager;
}

void MapMemory(void* virtualMemory, void* physicalMemory, PageTableManager manager) {
    PageIndexer indexer = PageMapIndexer((uint64_t)virtualMemory);
    PageTable* PML4 = manager.PML4;
    PageDirectoryEntry pde;

    pde = PML4->entries[indexer.PDP_i];
    PageTable* PDP;
    if (!pde.present) {
        PDP = (PageTable*)RequestPage();
        memset(PDP, 0, 0x1000);
        pde.Address = (uint64_t)PDP >> 12;
        pde.present = true;
        pde.ReadWirte = true;
        PML4->entries[indexer.PDP_i] = pde;
    }else {
        PDP = (PageTable*)((uint64_t)pde.Address << 12);
    }

    pde = PDP->entries[indexer.PD_i];
    PageTable* PD;
    if (!pde.present) {
        PD = (PageTable*)RequestPage();
        memset(PD, 0, 0x1000);
        pde.Address = (uint64_t)PD >> 12;
        pde.present = true;
        pde.ReadWirte = true;
        PDP->entries[indexer.PD_i] = pde;
    }else {
        PD = (PageTable*)((uint64_t)pde.Address << 12);
    }

    pde = PD->entries[indexer.PT_i];
    PageTable* PT;
    if (!pde.present) {
        PT = (PageTable*)RequestPage();
        memset(PT, 0, 0x1000);
        pde.Address = (uint64_t)PT >> 12;
        pde.present = true;
        pde.ReadWirte = true;
        PD->entries[indexer.PT_i] = pde;
    }else {
        PT = (PageTable*)((uint64_t)pde.Address << 12);
    }

    pde = PT->entries[indexer.P_i];
    pde.Address = (uint64_t)physicalMemory >> 12; 
    pde.present = true;
    pde.ReadWirte = true;
    PT->entries[indexer.P_i] = pde;
}

void switchPML4(PageTable* PML4) {
    __asm__ volatile("mov %0, %%cr3" : : "r" (PML4) : "memory");
}