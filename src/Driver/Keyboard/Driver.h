#pragma once
#define KBD_DATA_PORT 0x60
#define KBD_STATUS_PORT 0x64
#include "../../Kernel/kernel.h"
extern bool ctrl;
static const char kbd_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0,
 '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0, '*',    0,
  ' ',  0
};

char GetPressedKey(void);
int IsValid(char Char);