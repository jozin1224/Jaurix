
CC = gcc
AS = nasm
LD = ld
QEMU = qemu-system-i386


CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector -fno-exceptions -fno-rtti -nostdlib -c
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld


all: img


img: setup
	$(AS) $(ASFLAGS) src/Kernel/kernel_entry.asm -o Bin/kernel_entry.o
	$(CC) $(CFLAGS) src/Apps/BasicNote/main.c -o Bin/Note.o
	$(CC) $(CFLAGS) src/Kernel/Terminal.c -o Bin/Terminal.o
	$(CC) $(CFLAGS) src/Kernel/AsmToC.c -o Bin/AsmToC.o
	$(CC) $(CFLAGS) src/Kernel/kernel.c -o Bin/kernel.o
	$(CC) $(CFLAGS) src/Driver/Io.c -o Bin/Io.o
	$(CC) $(CFLAGS) src/Driver/Keyboard/Driver.c -o Bin/Key.o
	$(CC) $(CFLAGS) src/Driver/Serial/Driver.c -o Bin/Serial.o
	$(CC) $(CFLAGS) src/Driver/Video/Driver.c -o Bin/Video.o
	$(CC) $(CFLAGS) src/cpu/idt.c -o Bin/idt.o
	$(LD) $(LDFLAGS) Bin/kernel_entry.o Bin/kernel.o Bin/Io.o Bin/Serial.o Bin/Video.o Bin/Key.o Bin/idt.o Bin/AsmToC.o Bin/Terminal.o Bin/Note.o -o Bin/kernel.bin
	$(AS) -fbin src/Bootloader/boot.asm -o Bin/boot.bin
	#cat Bin/boot.bin Bin/kernel.bin  > Jaurix.img
	dd if=/dev/zero of=Jaurix.img bs=1024 count=1440 2>/dev/null
	dd if=Bin/boot.bin of=Jaurix.img conv=notrunc 2>/dev/null
	dd if=Bin/kernel.bin of=Jaurix.img seek=1 conv=notrunc 2>/dev/null


iso: setup img
	mkdir -p iso_root
	cp Jaurix.img iso_root/floppy.img
	xorriso -as mkisofs -R -b floppy.img -o Jaurix.iso iso_root/
	rm -rf iso_root

runiso: iso
	$(QEMU) -cdrom  Jaurix.iso -smp 2 -m 1G -serial stdio


runimg: img
	$(QEMU) -fda Jaurix.img -smp 2 -m 1G  -serial stdio

setup:
	mkdir -p Bin


clean:
	rm -f Jaurix.iso
	rm -f Jaurix.img
	rm -rf Bin/*
