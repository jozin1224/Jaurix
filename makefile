CC = gcc
AS = nasm
LD = ld
QEMU = qemu-system-x86_64

CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector -fno-exceptions -nostdlib -c
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

all: iso

kernel_bin: setup
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
	$(CC) $(CFLAGS) src/user/user.c -o Bin/user.o
	$(LD) $(LDFLAGS) Bin/kernel_entry.o Bin/user.o Bin/kernel.o Bin/Io.o Bin/Serial.o Bin/Video.o Bin/Key.o Bin/idt.o Bin/AsmToC.o Bin/Terminal.o Bin/Note.o -o Bin/kernel.bin

iso: kernel_bin
	mkdir -p iso_root/boot/grub
	cp Bin/kernel.bin iso_root/boot/kernel.bin
	@echo 'set timeout=30' > iso_root/boot/grub/grub.cfg
	@echo 'set default=0' >> iso_root/boot/grub/grub.cfg
	@echo 'menuentry "Boot on Jaurix OS" {' >> iso_root/boot/grub/grub.cfg
	@echo '    multiboot /boot/kernel.bin' >> iso_root/boot/grub/grub.cfg
	@echo '    boot' >> iso_root/boot/grub/grub.cfg
	@echo '}' >> iso_root/boot/grub/grub.cfg
	grub-mkrescue -o Jaurix.iso iso_root
	rm -rf iso_root

runiso: iso
	$(QEMU) -cdrom Jaurix.iso -smp 2 -m 1G -serial stdio

setup:
	mkdir -p Bin

clean:
	rm -f Jaurix.iso
	rm -rf Bin/
