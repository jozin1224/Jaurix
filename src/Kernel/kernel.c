#include "kernel.h"
#include "Terminal.h"
void kmain()
{
    IdtInitialize();
    Clean();
    TerminalMain();
    while (1)
    {
        hlt();
    }
}