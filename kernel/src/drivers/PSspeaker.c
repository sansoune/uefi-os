#include "../includes/PSspeaker.h"

static void PlaySound(unsigned int nFrequence) {
    unsigned char x;
    unsigned char y;
    x = 1193180 / nFrequence;
    outb(0x43, 0xb6);
    outb(0x42, (unsigned char)(x));
    outb(0x42, (unsigned char)(x >> 8));
    y = inb(0x61);
    if (y != (y | 3)) {
 	    outb(0x61, y | 3);
    }
}

static void Quiet() {
    unsigned char x = inb(0x61) & 0xFC;
    outb(0x61, x);
}

void beep(unsigned int freq, unsigned int time) {
    if (!freq) freq = 950;
    if (!time) time = 18;
    if (time == 0) {
        print("beep warning: 'time' played is zero.");
        return;
    }
    PlaySound(freq);
    sleep(time);
    Quiet();
}

note_freq_t melody[] = { E4, B3, C4, D4, C4, B3, A3, A3, C4, E4, D4, C4, B3, C4, D4, E4, C4, A3, A3, 0, 0, 0 };
unsigned int note_durations[] = { 12, 12, 12, 12, 12, 12, 24, 12, 12, 12, 12, 12, 12, 12, 12, 6, 12, 12, 12, 12, 12, 36 };

void music() {
    beep(E4, 0.2);
    beep(B3, 0.2);
    beep(C4, 0.5);
    beep(D4, 0.5);
    beep(C4, 0.2);
    beep(B3, 0.2);
    beep(A3, 0.5);
    beep(A3, 0.5);
    beep(C4, 0.2);
    beep(E4, 0.2);
    beep(D4, 0.5);
    beep(C4, 0.5);
    beep(B3, 0.5);
    beep(B3, 0.5);
    beep(C4, 0.2);
    beep(D4, 0.2);
    beep(E4, 0.2);
    beep(C4, 0.2);
    beep(A3, 0.2);
    beep(A3, 0.2);
    beep(C4, 0.2);
    beep(E4, 0.2);
    beep(D4, 0.5);
    beep(C4, 0.5);
    beep(B3, 0.5);
    beep(B3, 0.5);
    beep(C4, 0.2);
    beep(D4, 0.2);
    beep(E4, 0.2);
    beep(C4, 0.2);
    beep(A3, 0.2);
    beep(A3, 0.2);
    beep(C4, 0.2);
    beep(B3, 0.2);
    beep(C4, 0.5);
    beep(D4, 0.5);
    beep(E4, 0.5);
    beep(C4, 0.5);
    beep(A3, 0.5);
    beep(A3, 0.5);
    beep(E4, 0.2);
    beep(C4, 0.2);
    beep(D4, 0.5);
    beep(B3, 0.5);
    beep(C4, 0.2);
    beep(A3, 0.2);
    beep(A3, 0.2);
    beep(C4, 0.2);
    beep(E4, 0.2);
    beep(D4, 0.5);
    beep(C4, 0.5);
    beep(B3, 0.5);
    beep(B3, 0.5);
    beep(C4, 0.2);
    beep(D4, 0.2);
    beep(E4, 0.2);
    beep(C4, 0.2);
    beep(A3, 0.2);
    beep(A3, 0.2);
    beep(C4, 0.2);
    beep(B3, 0.2);
    beep(C4, 0.5);
    beep(D4, 0.5);
    beep(E4, 0.5);
    beep(C4, 0.5);
    beep(A3, 0.5);
    beep(A3, 0.5);
}
