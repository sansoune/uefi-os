#include "ahci.h"
#include "../../includes/pageframeAlloc.h"
#include "../../includes/heap.h"

#define HBA_PORT_DEV_PRESENT 0x3
#define HBA_PORT_IPM_ACTIVE 0x1
#define SATA_SIG_ATAPI 0xEB140101
#define SATA_SIG_ATA 0x00000101
#define SATA_SIG_SEMB 0xC33C0101
#define SATA_SIG_PM 0x96690101

#define HBA_PxCMD_CR 0x8000
#define HBA_PxCMD_FRE 0x0010
#define HBA_PxCMD_ST 0x0001
#define HBA_PxCMD_FR 0x4000


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

            if(portType == PortType_SATA || portType == PortType_SATAPI) {
                driver->ports[driver->portCount] = (Port*) malloc(sizeof(Port) * 6);
                driver->ports[driver->portCount]->portType = portType;
                driver->ports[driver->portCount]->hbaPort = &driver->ABAR->ports[i];
                driver->ports[driver->portCount]->portNumber = driver->portCount;
                driver->portCount++;
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

    for (int i = 0; i < driver->portCount; i++)
    {
        Port* port = driver->ports[i];

        Configure(port);
    }
    

}

void AHCIDriver_dtor(AHCIDriver* driver) {
    
}


void Configure(Port* port) {
    StopCMD(port);

    void* newBase = RequestPage();
    port->hbaPort->commandListBase = (uint32_t)(uint64_t)newBase;
    port->hbaPort->commandListBaseUpper = (uint32_t)((uint64_t)newBase >> 32);
    memset((void*)(port->hbaPort->commandListBase), 0, 1024);

    void* fisBase = RequestPage();
    port->hbaPort->fisBaseAddress = (uint32_t)(uint64_t)fisBase;
    port->hbaPort->fisBaseAddressUpper = (uint32_t)((uint64_t)fisBase >> 32);
    memset(fisBase, 0, 256);

    HBACommandHeader* cmdHeader = (HBACommandHeader*)((uint64_t)port->hbaPort->commandListBase + ((uint64_t)port->hbaPort->commandListBaseUpper << 32 ));

    for (int i = 0; i < 32; i++)
    {
        cmdHeader[i].prdtLength = 8;

        void* cmdTableAddress = RequestPage();
        uint64_t address = (uint64_t)cmdTableAddress + (i << 8);
        cmdHeader[i].commandTableBaseAddress = (uint32_t)(uint64_t)address; 
        cmdHeader[i].commandTableBaseAddressUpper = (uint32_t)((uint64_t)address >> 32);
        memset(cmdTableAddress, 0, 256); 
    }
    

    StartCMD(port);
}
void StartCMD(Port* port) {
    while (port->hbaPort->cmdSts & HBA_PxCMD_CR);
    port->hbaPort->cmdSts |= HBA_PxCMD_FRE;
    port->hbaPort->cmdSts |= HBA_PxCMD_ST;
}
void StopCMD(Port* port) {
    port->hbaPort->cmdSts &= ~HBA_PxCMD_ST;
    port->hbaPort->cmdSts &= ~HBA_PxCMD_FRE;
    
    while (true)
    {
        if(port->hbaPort->cmdSts & HBA_PxCMD_FR) continue;
        if(port->hbaPort->cmdSts & HBA_PxCMD_CR) continue;

        break;
    }
    

}
