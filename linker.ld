ENTRY(_start)

SECTIONS
{
    . = 1M; /* Garante o carregamento em 1 Megabyte */

    .text : AT(ADDR(.text))
    {
        *(.multiboot)    /* Captura o cabeçalho Multiboot */
        . = ALIGN(4);    /* Força alinhamento estrito de 4 bytes */
        *(.text)
    }

    .rodata : { *(.rodata) }
    .data   : { *(.data) }
    .bss    : { *(.bss) }
}
