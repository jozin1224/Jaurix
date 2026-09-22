#include "AsmToC.h"

void hlt(void){
    __asm__ __volatile__("hlt");
}
void cli(void)
{
    __asm__ __volatile__("cli");
}
void sti(void)
{
    __asm__ __volatile__("sti");
}