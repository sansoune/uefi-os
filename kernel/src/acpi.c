#include "includes/acpi.h"

void* FindTable(SDTHeader* sdtHeader, char* signature){
    int entries = (sdtHeader->Length - sizeof(SDTHeader)) / 8;
	for (int t = 0; t < entries; t++)
	{
		SDTHeader* newsdtHeader = (SDTHeader*)*(uint64_t*)((uint64_t)sdtHeader + sizeof(SDTHeader) + (t * 8));
        for(int i = 0; i < 4; i++) {
            if(newsdtHeader->Signature[i] != signature[i]) {
                break;
            }
            if(i == 3) return newsdtHeader; 
        }
	}
    return NULL;
}