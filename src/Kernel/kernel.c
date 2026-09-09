#include "kernel.h"
#include "Terminal.h"
void kmain()
{
    IdtInitialize();
    Clean();
    printfEx("[ OK ]", 0xA);
    printf(" Kernel Loaded\n");
    printfEx("Welcome to Jaurix\n", 0xF);
    TerminalMain();
    while (1)
    {
        hlt();
    }
}