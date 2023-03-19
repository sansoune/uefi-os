#include "../../includes/isr.h"

void isr0_handler() {
    print("deviding by zero exeption\n");
    for(;;);
}

void install() {
    SetIDTGate(0, (uint64_t)isr0_handler, 0x08, 0x8E);
}

uint8_t *exeption_message[] = {
    "Devision by zero exeption\n",
    "debbug"
};

void fault_handler(regs *r) {
    if(r->int_no < 32) {
        print(exeption_message[r->int_no]);
        for(;;);
    }
}