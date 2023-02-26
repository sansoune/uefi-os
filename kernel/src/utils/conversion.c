#include "../includes/conversion.h"


char int_to_string[256];

const char* toString(int num) {
    uint8_t size;
    uint32_t sizeTest = num;
    while (sizeTest / 10 > 0)
    {
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while (num / 10 > 0)
    {
        uint8_t remainder = num % 10;
        num /= 10;
        int_to_string[size - index] = remainder + '0';
        index++;
    }
    uint8_t remainder = num % 10;
    int_to_string[size - index] = remainder + '0';
    int_to_string[size + 1] = 0;
    return int_to_string;


}




char hexTo_StringOutput[128];
const char* hex_to_String(uint32_t value) {
    uint32_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 4 * 2 - 1;
    for(uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexTo_StringOutput[size - (i*2+1)] = tmp + (tmp > 9 ? 'A' : '0');
        tmp = ((*ptr & 0x0F));
        hexTo_StringOutput[size - (i*2)] = tmp + (tmp > 9 ? 'A' : '0');
    }
    hexTo_StringOutput[size + 1] = 0;
    return hexTo_StringOutput;
}