#include "Driver.h"

static inline char get_pressed_key(void) {
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
