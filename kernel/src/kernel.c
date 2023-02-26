#include "includes/kernel.h"

void _start(BootInfo* bootInfo) {
	init_graphics(bootInfo->framebuffer, bootInfo->font);
	print("hello ya yassine \n");

	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescriptorSize;

	for (int i = 0; i < mMapEntries; i++)
	{
		EFI_MEMORY_DESCIPTOR* desc = (EFI_MEMORY_DESCIPTOR*)((uint64_t)bootInfo->mMap + (i * bootInfo->mMapDescriptorSize));
		print(EFI_MEMORY_TYPE_STRINGS[desc->type]);
		print(" ");
		print(toString(desc->numPages * 4096 / 1024));
		print(" KB\n");
	}
	
	
    return ;
}