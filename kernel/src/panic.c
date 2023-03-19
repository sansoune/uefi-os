#include "./includes/panic.h"

void Panic(const char* Message){
    clear(0x00ff0000);
    setColor(0xffffffff);
    print("kernel panic: \n\n");
    print(Message);
}