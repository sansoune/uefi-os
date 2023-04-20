#pragma once
#include "stdint.h"
#include "acpi.h"
#include "paging.h"
#include "stdio.h"
#include "conversion.h"
#include "pciDesc.h"

typedef struct {
    uint16_t VendorID;
    uint16_t DeviceID;
    uint16_t Command;
    uint16_t Status;
    uint8_t RevisionID;
    uint8_t ProgIF;
    uint8_t Subclass;
    uint8_t Class;
    uint8_t CacheLineSize;
    uint8_t LatencyTimer;
    uint8_t HeaderType;
    uint8_t BIST;
} PCIDeviceHeader;

typedef struct {
    PCIDeviceHeader Header;
    uint32_t BAR0;
    uint32_t BAR1;
    uint32_t BAR2;
    uint32_t BAR3;
    uint32_t BAR4;
    uint32_t BAR5;
    uint32_t CardbusCISPtr;
    uint16_t SubsystemVendorId;
    uint16_t SubsytemId;
    uint32_t ExpansionROMBaseAddress;
    uint8_t CapabilitiesPtr;
    uint8_t Rsv0;
    uint16_t Rsv1;
    uint32_t Rsv2;
    uint8_t InterruptLine;
    uint8_t InterruptPin;
    uint8_t MinGrant;
    uint8_t MaxLatency;
} PCIHeader;

void EnumeratePCI(MCFGHeader* mcfg);

extern const char* DeviceClasses[];

