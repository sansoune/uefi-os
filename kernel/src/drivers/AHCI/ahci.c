#include "ahci.h"
#include "../../includes/pageframeAlloc.h"

#define HBA_PORT_DEV_PRESENT 0x3
#define HBA_PORT_IPM_ACTIVE 0x1
#define SATA_SIG_ATAPI 0xEB140101
#define SATA_SIG_ATA 0x00000101
#define SATA_SIG_SEMB 0xC33C0101
#define SATA_SIG_PM 0x96690101

PortType CheckPortType(HBAPort* port) {
    uint32_t SATA_STATUS = port->sataStatus;
    uint8_t interfacePowerManagement = (SATA_STATUS >> 8) & 0b111;
    uint8_t deviceDetection = SATA_STATUS & 0b111;

    if(deviceDetection != HBA_PORT_DEV_PRESENT) return PortType_None;
    if(interfacePowerManagement != HBA_PORT_IPM_ACTIVE) return PortType_None;

    switch (port->signature)
    {
    case SATA_SIG_ATAPI:
        return PortType_SATAPI;
    case SATA_SIG_ATA:
        return PortType_SATA;
    case SATA_SIG_PM:
        return PortType_PM;
    case SATA_SIG_SEMB:
        return SATA_SIG_SEMB;
    default:
        return PortType_None;
    }
}

void AHCIDriver_ProbePorts(AHCIDriver* driver) {
    uint32_t portsImplemented = driver->ABAR->portsImplemented;
    for (int i = 0; i < 32; i++)
    {
        if(portsImplemented & (1 << i)) {
            PortType portType = CheckPortType(&driver->ABAR->ports[i]);

            if(portType == PortType_SATA) {
                print("sata drive \n");
            }
            if(portType == PortType_SATAPI) {
                print("satapi drive \n");
            }
            else {
                print("not interested \n");
            }
        }
    }
    
}

void AHCIDriver_ctor(AHCIDriver* driver, PCIDeviceHeader* pciBaseAddress) {
    driver->pciBaseAddress = pciBaseAddress;
    print("AHCI driver Instance initialized\n");

    driver->ABAR = (HBAMemory*)((PCIHeader*)pciBaseAddress)->BAR5;

    MapMemory(driver->ABAR, driver->ABAR, g_Pagetablemanager);

    AHCIDriver_ProbePorts(driver);

}

void AHCIDriver_dtor(AHCIDriver* driver) {
    
}

