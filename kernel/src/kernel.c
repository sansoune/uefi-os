#include "includes/kernel.h"


extern uint64_t __kernel_start;
extern uint64_t __kernel_end;

void _start(BootInfo* bootInfo) {
	init_graphics(bootInfo->framebuffer, bootInfo->font);

	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescriptorSize;

	ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescriptorSize);

	GDTInit();
	IDTInit();
	install();
	IRQ_INIT();
	init_timer();
	init_kb();
	
	
	uint64_t kernel_size = (uint64_t)&__kernel_end - (uint64_t)&__kernel_start;
	uint64_t kernelPages = (uint64_t)kernel_size / 4096 + 1;
	LockPages(&__kernel_start, kernelPages);

	PageTable* PML4 = (PageTable*)RequestPage();
	memset(PML4, 0, 0x1000);

	uint64_t stack = (uint64_t)RequestPage() + 0x1000;
	asm("mov %0, %%rsp" : : "r"(stack));
	
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

	switchPML4(PML4);
	memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

	init_heap((void*)0x0000100000000000, 0x10, pageTableManagr);


	print("welcome my os\n");
	char* buffer;
	while (true)
	{
		status = true;
		curretnPos();
		print("OS>");
		while(status == true){
    	    buffer = readStr();
    	}
		shell(buffer);
		clean_buffer();
	}
	


	// for (unsigned long long i = 0; i < 10000000000ULL; i++) {}

	// int x = 5, y = 0, z;

    // __asm__ ("movl %1, %%eax;"
    //          "movl %2, %%ebx;"
    //          "idivl %%ebx;"
    //          "movl %%eax, %0;"
    //          : "=r" (z)
    //          : "r" (x), "r" (y)
    //          : "%eax", "%ebx");

	// int* fault = (int*)0x80000000000;
	// *fault = 2;


	while (true);
	
    return ;
}
