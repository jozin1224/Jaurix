#include "Driver.h"

// Variável global para rastrear o estado do Shift
static bool is_shift_pressed = false;

char GetPressedKey(void) {
    if ((inb(KBD_STATUS_PORT) & 1) == 0) {
        return 0;
    }
    
    unsigned char scancode = inb(KBD_DATA_PORT);
    
    if (scancode == 0x2A || scancode == 0x36) {
        is_shift_pressed = true;
        return 0;
    }
    if (scancode == 0xAA || scancode == 0xB6) {
        is_shift_pressed = false;
        return 0;
    }
    
    if (scancode & 0x80) {
        return 0;
    }
    
    if (scancode < 128) {
        char key = kbd_map[scancode];
        if (is_shift_pressed && key >= 'a' && key <= 'z') {
            key -= 32;
        }
        
        return key;
    }
    
    return 0;
}

int IsValid(char Char) {   // Yes, i am gmod modder
    return (Char >= 32 && Char <= 126) || Char == '\b' || Char == '\r' || Char == '\n'; // Valid char for keyboard
}
