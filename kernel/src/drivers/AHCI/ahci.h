#pragma once
#include "../../includes/stdint.h"
#include "../../includes/pci.h"
#include "../../includes/stdio.h"

typedef enum {
    PortType_None = 0,
    PortType_SATA = 1,
    PortType_SEMB = 2,
    PortType_PM = 3,
    PortType_SATAPI = 4
} PortType;

typedef struct {
    uint32_t commandListBase;
    uint32_t commandListBaseUpper;
    uint32_t fisBaseAddress;
    uint32_t fisBaseAddressUpper;
    uint32_t interruptStatus;
    uint32_t interruptEnable;
    uint32_t cmdSts;
    uint32_t rsv0;
    uint32_t taskFileData;
    uint32_t signature;
    uint32_t sataStatus;
    uint32_t sataControl;
    uint32_t sataError;
    uint32_t sataActive;
    uint32_t commandIssue;
    uint32_t sataNotification;
    uint32_t fisSwitchControl;
    uint32_t rsv1[11];
    uint32_t vendor[4];
} HBAPort;

typedef struct {
    uint32_t hostCapability;
    uint32_t globalHostControl;
    uint32_t interruptStatus;
    uint32_t portsImplemented;
    uint32_t version;
    uint32_t cccControl;
    uint32_t cccPorts;
    uint32_t enclosureManagementLocation;
    uint32_t enclosureManagementControl;
    uint32_t hostCapabilitiesExtended;
    uint32_t biosHandoffCtrlSts;
    uint8_t rsv0[0x74];
    uint8_t vendor[0x60];
    HBAPort ports[1];
} HBAMemory;

typedef struct {
    uint8_t commandFISLength:5;
    uint8_t atapi:1;
    uint8_t write:1;
    uint8_t prefetchable:1;

    uint8_t reset:1;
    uint8_t bist:1;
    uint8_t clearBusy:1;
    uint8_t rsv0:1;
    uint8_t portMultiplier:4;

    uint16_t prdtLength;
    uint32_t prdbCount;
    uint32_t commandTableBaseAddress;
    uint32_t commandTableBaseAddressUpper;
    uint32_t rsv1[4];
} HBACommandHeader;


typedef struct {
HBAPort* hbaPort;
PortType portType;
uint8_t* buffer;
uint8_t portNumber;
} Port;


typedef struct {
    PCIDeviceHeader* pciBaseAddress;
    HBAMemory* ABAR;
    Port* ports[32];
    uint8_t portCount;
} AHCIDriver;

void AHCIDriver_ctor(AHCIDriver* driver, PCIDeviceHeader* pciBaseAddress);
void AHCIDriver_dtor(AHCIDriver* driver);



void Configure(Port* port);
void StartCMD(Port* port);
void StopCMD(Port* port);
