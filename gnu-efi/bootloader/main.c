#include <efi.h>
#include <efilib.h>
#include <elf.h>

typedef unsigned long long size_t;

typedef struct {
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelPerScanline;
} FrameBuffer;

#define PSF1_MAGIC0 0x36
#define PSF1_MAGIC1 0x04

typedef struct {
	unsigned char magic[2];
	unsigned char mode;
	unsigned char charSize;
} PSF1_HEADER;

typedef struct {
	PSF1_HEADER* psf1_header;
	void* glyphBuffer;
} PSF1_FONT;

typedef struct {
	FrameBuffer* framebuffer;
	PSF1_FONT* font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	UINTN mMapSize;
	UINTN mMapDescriptorSize;
} BootInfo;

FrameBuffer frame;
FrameBuffer* InitializeGOP() {
	EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
	EFI_STATUS status;

	status = uefi_call_wrapper(BS->LocateProtocol, 3, &gopGuid, NULL, (void**)&gop);
	if(EFI_ERROR(status)){
		Print(L"Unable to locate GOP\n\r");
		return NULL;
	}else {
		Print(L"GOP located\n\r");
	}

	frame.BaseAddress = (void*)gop->Mode->FrameBufferBase;
	frame.BufferSize = gop->Mode->FrameBufferSize;
	frame.Width = gop->Mode->Info->HorizontalResolution;
	frame.Height = gop->Mode->Info->VerticalResolution;
	frame.PixelPerScanline = gop->Mode->Info->PixelsPerScanLine;

	return &frame;
}

EFI_FILE* LoadFile(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
	EFI_FILE* LoadFile;

	EFI_LOADED_IMAGE_PROTOCOL* LodedImage;
	SystemTable->BootServices->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LodedImage);
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
	SystemTable->BootServices->HandleProtocol(LodedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&FileSystem);

	if(Directory == NULL) {
		FileSystem->OpenVolume(FileSystem, &Directory);
	}

	EFI_STATUS s = Directory->Open(Directory, &LoadFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if(s != EFI_SUCCESS) {
		return NULL;
	}

	return LoadFile;
}

int memcp(const void* aptr, const void* bptr, size_t n) {
	const unsigned char* a = aptr, *b = bptr;
	for(size_t i = 0; i < n; i++) {
		if(a[i] < b[i]) return -1;
		else if (a[i] > b[i]) return 1;
	}
	return 0;
}

PSF1_FONT* LoadPSF1Font(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
	EFI_FILE* font = LoadFile(Directory, Path, ImageHandle, SystemTable);
	if (font == NULL) {
		return NULL;
	}

	PSF1_HEADER* fontHeader;
	SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(PSF1_HEADER), (void**)&fontHeader);
	UINTN size = sizeof(PSF1_HEADER);
	font->Read(font, &size, fontHeader);

	if(fontHeader->magic[0] != PSF1_MAGIC0 || fontHeader->magic[1] != PSF1_MAGIC1) {
		return NULL;
	}

	UINTN glyphBufferSize = fontHeader->charSize * 256;
	if(fontHeader->mode == 1) {
		glyphBufferSize = fontHeader->charSize * 512;
	}

	void* glyphBuffer;
	{
		font->SetPosition(font, sizeof(PSF1_HEADER));
		SystemTable->BootServices->AllocatePool(EfiLoaderData, glyphBufferSize, (void**)&glyphBuffer);
		font->Read(font, &glyphBufferSize, glyphBuffer);
	}

	PSF1_FONT* finishedFont;
	SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(PSF1_FONT), (void**)&finishedFont);
	finishedFont->psf1_header = fontHeader;
	finishedFont->glyphBuffer = glyphBuffer;
	return finishedFont;
}


EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	
	InitializeLib(ImageHandle, SystemTable);
	Print(L"test test 123\n\r");

	EFI_FILE* kernel = LoadFile(NULL, L"kernel.elf", ImageHandle, SystemTable);

	if(kernel == NULL) {
		Print(L"Could not load kernel \n\r");
	}else {
		Print(L"kernel Loaded successfuly\n\r");
	}

	Elf64_Ehdr header;
	{
		UINTN FileInfoSize;
		EFI_FILE_INFO* FileInfo;
		kernel->GetInfo(kernel, &gEfiFileInfoGuid, &FileInfoSize, NULL);
		SystemTable->BootServices->AllocatePool(EfiLoaderData, FileInfoSize, (void**)&FileInfo);
		kernel->GetInfo(kernel, &gEfiFileInfoGuid, &FileInfoSize, (void**)&FileInfo);

		UINTN size = sizeof(header);
		kernel->Read(kernel, &size, &header);
	}

	if(memcp(&header.e_ident[EI_MAG0], ELFMAG,SELFMAG) != 0 || header.e_ident[EI_CLASS] != ELFCLASS64 || header.e_ident[EI_DATA] != ELFDATA2LSB || header.e_type != ET_EXEC || header.e_machine != EM_X86_64 || header.e_version != EV_CURRENT){
		Print(L"kernel foramt is bad\n\r");
	}else {
		Print(L"kernel header successfully verified \n\r");
	}

	Elf64_Phdr* phdrs;
	{
		kernel->SetPosition(kernel, header.e_phoff);
		UINTN size = header.e_phnum * header.e_phentsize;
		SystemTable->BootServices->AllocatePool(EfiLoaderData, size, (void**)&phdrs);
		kernel->Read(kernel, &size, phdrs);
	}

	for (Elf64_Phdr* phdr = phdrs; (char*)phdr < (char*)phdrs + header.e_phnum * header.e_phentsize; phdr = (Elf64_Phdr*)((char*)phdr + header.e_phentsize)) {
		switch (phdr->p_type)
		{
		case PT_LOAD:
			int pages = (phdr->p_memsz + 0x1000 - 1) /0x1000;
			Elf64_Addr segment = phdr->p_paddr;
			SystemTable->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, pages, &segment);

			kernel->SetPosition(kernel, phdr->p_offset);
			UINTN size = phdr->p_filesz;
			kernel->Read(kernel, &size, (void*)segment);
			break;
		}
	}

	Print(L"Kernel Loaded\n\r");

	
	PSF1_FONT* newFont = LoadPSF1Font(NULL, L"zap-light16.psf", ImageHandle, SystemTable);
	if(newFont == NULL) {
		Print(L"font is not found\n\r");
	}else {
		Print(L"font found. char size = %d\n\r", newFont->psf1_header->charSize);
	}

	FrameBuffer* buffer = InitializeGOP();
	Print(L"base: 0x%x\n\r size: 0x%x\n\r width: %d\n\r height: %d\n\rpixelPerScanline: %d\n\r", buffer->BaseAddress, buffer->BufferSize, buffer->Width, buffer->Height, buffer->PixelPerScanline);

	EFI_MEMORY_DESCRIPTOR* Map = NULL;
	UINTN MapSize, MapKey;
	UINTN DescriptorSize;
	UINT32 DescriptorVersion;
	{
		SystemTable->BootServices->GetMemoryMap(&MapSize, Map, &MapKey, &DescriptorSize, &DescriptorVersion);
		SystemTable->BootServices->AllocatePool(EfiLoaderData, MapSize, (void**)&Map);
		SystemTable->BootServices->GetMemoryMap(&MapSize, Map, &MapKey, &DescriptorSize, &DescriptorVersion);
	}

	void (*kernelStart)(BootInfo*) = ((__attribute__((sysv_abi)) void (*)(BootInfo*)) header.e_entry);

	BootInfo bootInfo;
	bootInfo.framebuffer = buffer;
	bootInfo.font = newFont;
	bootInfo.mMap = Map;
	bootInfo.mMapSize = MapSize;
	bootInfo.mMapDescriptorSize = DescriptorSize;

	SystemTable->BootServices->ExitBootServices(ImageHandle, MapKey);

	kernelStart(&bootInfo);

	return EFI_SUCCESS; // Exit the UEFI application
}
