MODULEALIGN equ  1 << 0 ;Grub                   
MEMINFO     equ  1 << 1                   
FLAGS       equ  MODULEALIGN | MEMINFO    
MAGIC       equ  0x1BADB002               
CHECKSUM    equ -(MAGIC + FLAGS)          

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text
global _start
extern kmain                               

_start:
    cli                                   
    call kmain                             
    jmp $                                 
