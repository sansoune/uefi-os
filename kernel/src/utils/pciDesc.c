#include "../includes/pciDesc.h"

const char* DeviceClasses[] = {
    "Unclassified",
    "Mass Storage Controller",
    "Network Controller",
    "Display Controller",
    "Multimedia Controller",
    "Memory Controller",
    "Bridge Device",
    "Simple Communication Controller",
    "Base System Peripheral",
    "Input Device Controller",
    "Docking Station", 
    "Processor",
    "Serial Bus Controller",
    "Wireless Controller",
    "Intelligent Controller",
    "Satellite Communication Controller",
    "Encryption Controller",
    "Signal Processing Controller",
    "Processing Accelerator",
    "Non Essential Instrumentation"
};

const char* GetVendorName(uint16_t vendorId) {
    switch (vendorId)
    {
    case 0x8086:
        return "Intel Corp";
    case 0x1022:
        return "AMD";
    case 0x10DE:
        return "NVIDIA Corporation";
    }
    return hex_to_String(vendorId);
}

const char* GetDeviceName(uint16_t vendorId, uint16_t deviceId) {
    switch (vendorId)
    {
    case 0x8086:
        switch (deviceId)   
        {
        case 0x29c0:
            return "Express DRAM Controller";
        case 0x2918:
            return "LCP Interface Controller";
        case 0x2922:
            return "6 Port SATA Controller [AHCI mode]";
        case 0x2930:
            return "SMBus Controller";
        }
        
    }
    return hex_to_String(deviceId);
}

const char* MassStorageControllerSubClassName(subClassCode) {
    switch (subClassCode)
    {
    case 0x00:
        return "SCSI Bus Controller";
    case 0x01:
        return "IDE Controller";
    case 0x02:
        return "Floppy Disk Controller";
    case 0x03:
        return "IPI Bus Controller";
    case 0x04:
        return "RAID Controller";
    case 0x05:
        return "ATA Controller";
    case 0x06:
        return "Serial ATA";
    case 0x07:
        return "Serial Attached SCSI";
    case 0x08:
        return "Non-Volatile Memory Controller";
    case 0x80:
        return "Other";
    }
    return hex_to_String(subClassCode);
}

const char* GetSubClassName(uint8_t classCode, uint8_t subClassCode) {
    switch (classCode)
    {
    case 0x01:
        return MassStorageControllerSubClassName(subClassCode);
    }
    return toString(subClassCode);
}

const char* GetProgramIFName(uint8_t classCode, uint8_t subClassCode, uint8_t progIF) {
    switch (classCode)
    {
    case 0x01:
        switch (subClassCode)
        {
        case 0x06:
            switch (progIF)
            {
            case 0x00:
                return "Vendor Specific Interface";
            case 0x01:
                return "AHCI 1.0";
            case 0x02:
                return "Serial Storage Bus";
            }
        }
    }
    return hex_to_String(progIF);
}