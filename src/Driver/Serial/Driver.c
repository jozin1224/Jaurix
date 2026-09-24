#include "Driver.h"
int InitSerial() {
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x80);
    outb(PORT + 0, 0x03);
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x03);
    outb(PORT + 2, 0xC7);
    outb(PORT + 4, 0x0B); 
    
    outb(PORT + 4, 0x1E);
    outb(PORT + 0, 0xAE);

    if(inb(PORT + 0) != 0xAE) {
        return 1; 
    }

    outb(PORT + 4, 0x0F);
    return 0; 
}

int IsEmpty() {
    return inb(PORT + 5) & 0x20;
}

void WriteSerial(char c) {
    while ((IsEmpty()) == 0); 
    outb(PORT + 0, c);
}

void PrintSerial(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        WriteSerial(str[i]);
    }
}
