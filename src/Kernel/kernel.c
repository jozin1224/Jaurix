#include "kernel.h"
#include "Terminal.h"

void Restart() {
    PrintSerial("[KERNEL] REBOOT\n");
    uint8_t status;
    for (int i = 0; i < 1000; i++) {
        status = inb(0x64);
        if ((status & 0x02) == 0) {
            break;
        }
    }
    outb(0xFE, 0x64);
    outb(0x06, 0xCF9); 
    __asm__ volatile ("lidt %0; int3" : : "m"((uint16_t){0})); 
}

void kmain()
{
    InitSerial();
    IdtInitialize();
    PrintSerial("[TERMINAL] IDT LOAD\n");
    Clean();
    SetProtectedZone(0);
    printfEx("[ OK ]", 0xA);
    printf(" Kernel Loaded\n");
    printfEx("Welcome to Jaurix\n", 0xF);
    SetProtectedZone(1);
    TerminalMain();
    PrintSerial("[TERMINAL] CRASHED\n");
    while (1)
    {
        hlt();
    }
}