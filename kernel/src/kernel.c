#include "includes/kernel.h"


extern uint64_t __kernel_start;
extern uint64_t __kernel_end;


void _start(BootInfo* bootInfo) {
	init_graphics(bootInfo->framebuffer, bootInfo->font);

	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescriptorSize;

	ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescriptorSize);

	GDTInit();
	PrepareInterrupts();
	
	uint64_t kernel_size = (uint64_t)&__kernel_end - (uint64_t)&__kernel_start;
	uint64_t kernelPages = (uint64_t)kernel_size / 4096 + 1;
	LockPages(&__kernel_start, kernelPages);

	PageTable* PML4 = (PageTable*)RequestPage();
	memset(PML4, 0, 0x1000);
	
	PageTableManager pageTableManagr = PageTableManageer(PML4);
	
	for (uint64_t i = 0; i < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescriptorSize); i+=0x1000) {
		MapMemory((void*)i, (void*)i, pageTableManagr);
	}
	

	uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
	uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
	LockPages((void*)fbBase, fbSize / 0x1000 + 1);
	for(uint64_t i = fbBase; i < fbBase + fbSize; i += 4096) {
		MapMemory((void*)i, (void*)i, pageTableManagr);
	}

	memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);
	switchPML4(PML4);
	

	print("i am in the memory map! \n");
	
	MapMemory((void*)0x600000000, (void*)0x80000, pageTableManagr);
	uint64_t* test = (uint64_t*)0x600000000;
	*test = 26;
	print(toString(*test));

	asm("int $0x0E");

	while (true);
	
    return ;
}