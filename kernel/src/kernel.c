#include "includes/kernel.h"


extern uint64_t __kernel_start;
extern uint64_t __kernel_end;


void _start(BootInfo* bootInfo) {
	init_graphics(bootInfo->framebuffer, bootInfo->font);
	print("hello ya yassine \n");

	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescriptorSize;

	ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescriptorSize);

	
	uint64_t kernel_size = (uint64_t)&__kernel_end - (uint64_t)&__kernel_start;
	uint64_t kernelPages = (uint64_t)kernel_size / 4096 + 1;
	LockPages(&__kernel_start, kernelPages);

	print("Free RAM: ");
	print(toString(GetFreeRam() / 1024));
	print(" KB\n");

	print("used RAM: ");
	print(toString(GetUsedRam() / 1024));
	print(" KB\n");

	print("Reserved RAM: ");
	print(toString(GetReservedRam() / 1024));
	print(" KB\n");

	for (int i = 0; i < 20; i++)
	{
		void* address = RequestPage();
		print(hex_to_String((uint64_t)address));
		print("\n");
	}
	
    return ;
}