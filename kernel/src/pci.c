#include "includes/pci.h"


void EnumerateFunction(uint64_t deviceAddress, uint64_t function) {
    uint64_t offset = function << 12;

    uint64_t functionAddress = deviceAddress + offset;
    MapMemory((void*)functionAddress, (void*)functionAddress, g_Pagetablemanager);

    PCIDeviceHeader* pciDeviceHeader = (PCIDeviceHeader*)functionAddress;

    if(pciDeviceHeader->DeviceID == 0) return;
    if(pciDeviceHeader->DeviceID == 0xffff) return;

    print(GetVendorName(pciDeviceHeader->VendorID));
    print(" ");
    print(GetDeviceName(pciDeviceHeader->VendorID, pciDeviceHeader->DeviceID));
    print(" ");
    print(DeviceClasses[pciDeviceHeader->Class]);
    print(" ");
    print(GetSubClassName(pciDeviceHeader->Class, pciDeviceHeader->Subclass));
    print(" ");
    print(GetProgramIFName(pciDeviceHeader->Class, pciDeviceHeader->Subclass ,pciDeviceHeader->ProgIF));
    print("\n");
}


void EnumerateDevice(uint64_t busAddress, uint64_t device) {
    uint64_t offset = device << 15;

    uint64_t deviceAddress = busAddress + offset;
    MapMemory((void*)deviceAddress, (void*)deviceAddress, g_Pagetablemanager);

    PCIDeviceHeader* pciDeviceHeader = (PCIDeviceHeader*)deviceAddress;

    if(pciDeviceHeader->DeviceID == 0) return;
    if(pciDeviceHeader->DeviceID == 0xffff) return;

    for(uint64_t function = 0; function < 8; function++) {
        EnumerateFunction(deviceAddress, function);
    }
}

void EnumerateBus(uint64_t baseAddress, uint64_t bus) {
    uint64_t offset = bus << 20;

    uint64_t busAddress = baseAddress + offset;
    MapMemory((void*)busAddress, (void*)busAddress, g_Pagetablemanager);

    PCIDeviceHeader* pciDeviceHeader = (PCIDeviceHeader*)busAddress;

    if(pciDeviceHeader->DeviceID == 0) return;
    if(pciDeviceHeader->DeviceID == 0xffff) return;

    for(uint64_t device = 0; device < 32; device++) {
        EnumerateDevice(busAddress, device);
    }
}

void EnumeratePCI(MCFGHeader* mcfg) {
    int entries = ((mcfg->Header.Length) - sizeof(MCFGHeader)) / sizeof(DeviceConfig);
    for(int t = 0; t < entries; t++) {
        DeviceConfig* newDeviceConfig = (DeviceConfig*)((uint64_t)mcfg + sizeof(MCFGHeader) + (sizeof(DeviceConfig) * t));
        for(uint64_t bus = newDeviceConfig->StartBus; bus < newDeviceConfig->EndBus; bus++) {
            EnumerateBus(newDeviceConfig->BaseAddress, bus);
        }
    }
}