HOST?=i686-elf
TOOLCHAIN_DIR := i686-elf-4.9.1-Linux-x86_64

PWD = $(shell pwd)
TOOLCHAIN_PREFIX := tools/$(TOOLCHAIN_DIR)/bin/

AS = $(TOOLCHAIN_PREFIX)$(HOST)-as
CPP = $(TOOLCHAIN_PREFIX)$(HOST)-g++

GPPARMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -std=c++14
ASPARAMS = --32

#TODO: Update LD params
LDPARAMS = -melf_i386


objlist = src/arch/x86/boot.o src/kernel/kernel.o src/kernel/gdt.o src/kernel/port.o src/kernel/interruptstubs.o src/kernel/interrupts.o src/kernel/terminal.o

%.o : %.cpp
	$(CPP) $(GPPARMS) -o $@ -c $<

%.o : %.s
	$(AS) $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objlist)
	ld $(LDPARAMS) -T $< -o $@ $(objlist)

clean:
	rm -rf $(objlist)
	rm -rf mykernel.bin
iso: mykernel.bin
	mkdir -p isodir/boot/grub
	cp mykernel.bin isodir/boot/mykernel.bin
	printf "menuentry mykernel {\n	multiboot /boot/mykernel.bin\n}" > isodir/boot/grub/grub.cfg
	grub-mkrescue -o mykernel.iso isodir

qemu: iso
	qemu-system-i386 -cdrom mykernel.iso -curses
