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
	
	g_Pagetablemanager = PageTableManageer(PML4);
	
	for (uint64_t i = 0; i < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescriptorSize); i+=0x1000) {
		MapMemory((void*)i, (void*)i, g_Pagetablemanager);
	}
	

	uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
	uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
	LockPages((void*)fbBase, fbSize / 0x1000 + 1);
	for(uint64_t i = fbBase; i < fbBase + fbSize; i += 4096) {
		MapMemory((void*)i, (void*)i, g_Pagetablemanager);
	}

	switchPML4(PML4);
	memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

	init_heap((void*)0x0000100000000000, 0x10);
	SDTHeader* xsdt = (SDTHeader*)(bootInfo->rsdp->XSDTAddress);
	MCFGHeader* mcfg = (MCFGHeader*)FindTable(xsdt, (char*)"MCFG");
	EnumeratePCI(mcfg);
	
	void * code_loc = malloc(20);

	print(__DATE__);
	print(" ");
	print(__TIME__);
	print("\n");
	print("welcome my os\n");
	// char div_by_zero [] =   {   0xba, 0x00, 0x00, 0x00, 0x00,         // mov 0x0, edx
    //                         0xb8, 0xfa, 0x00, 0x00, 0x00,         // mov 0xfa, eax
    //                         0xb9, 0x00, 0x00, 0x00, 0x00,         // mov 0x0, ecx
    //                         0xf7, 0xf1                            // div ecx ---> DIV BY 0
    //                     };

	// load_flat_binary_at(div_by_zero, 17, code_loc);
	// run_flat_binary(code_loc);
	char* buffer;
	while (true)
	{
		status = true;
		print("OS>");
		curretnPos();
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
