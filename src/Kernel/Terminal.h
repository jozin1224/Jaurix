#pragma once

#include "../Driver/Video/Driver.h"
#include "../Driver/Keyboard/Driver.h"
char GetPressedKey(void);
int IsValid(char Char);

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void TerminalMain(void)
{
    while(1)
    {
        char Key = GetPressedKey();
        if (IsValid(Key))
        {
            WriteChar(Key, 0x07);
        }
    }
}