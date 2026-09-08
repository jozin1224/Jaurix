#include "idt.h"
#include "../Driver/Video/Driver.h"
struct idt_entry idt[256];
struct idt_ptr idtp;

void IdtSetGate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[num].offset_low = (base & 0xFFFF);
    idt[num].offset_high = (base >> 16) & 0xFFFF;
    idt[num].selector = sel;
    idt[num].zero = 0;
    idt[num].type_attr = flags;
}
void ZeroDivision(void)
{
    __asm__ __volatile__("cli");
    printf("\n[ERROR] Zero Division");
    while(1)
    {
    __asm__ __volatile__("hlt");
    }
}

void IdtInitialize(void) {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int)&idt;
    for(int i = 0; i < 256; i++) {
        IdtSetGate(i, 0, 0, 0);
    }
    IdtSetGate(0, (unsigned long)ZeroDivision, 0x08, 0x8E);
    __asm__ __volatile__("lidt (%0)" : : "r" (&idtp));
}
