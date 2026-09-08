#pragma once

struct idt_entry {
    unsigned short offset_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short offset_high;
} __attribute__((packed));
struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));
void IdtSetGate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void IdtInitialize(void);
void ZeroDivision(void);