#pragma once
#include "conversion.h"
#include "stdint.h"


const char* GetVendorName(uint16_t vendorId);

const char* GetDeviceName(uint16_t vendorId, uint16_t deviceId);
const char* GetSubClassName(uint8_t classCode, uint8_t subClassCode);
const char* GetProgramIFName(uint8_t classCode, uint8_t subClassCode, uint8_t progIF);
