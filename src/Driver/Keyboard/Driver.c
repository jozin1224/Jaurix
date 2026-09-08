#include "Driver.h"

char GetPressedKey(void) {
    if ((inb(KBD_STATUS_PORT) & 1) == 0) {
        return 0;
    }
    
    unsigned char scancode = inb(KBD_DATA_PORT);
    
    if (scancode & 0x80) {
        return 0;
    }
    
    if (scancode < 128) {
        return kbd_map[scancode];
    }
    
    return 0;
}

int IsValid(char Char) {   // Yes, i am gmod modder
    return (Char >= 32 && Char <= 126) || Char == '\b' || Char == '\r' || Char == '\n'; // Valid char for keyboard
}
