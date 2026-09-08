#include "kernel.h"
void kmain()
{
    IdtInitialize();
    Clean();
    printf("Press a key to Division error");
    while(1)
    {
        char Key = GetPressedKey();
        if (IsValid(Key))
        {
            if (Key == 'a'){
                break;
            }
        }
    }
    int i = 0 / 0;
    while (1)
    {
        hlt();
    }
}