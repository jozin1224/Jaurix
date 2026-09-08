#include "kernel.h"
void ASMCommand(const char* ASM)
{
    __asm__ __volatile__("cli");
}
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
        ASMCommand("hlt");
    }
}