
# sudo apt-get install g++ binutils libc6-dev-i386
# sudo apt-get install VirtualBox grub-legacy xorriso

GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = obj/compiled/loader.o \
          obj/compiled/gdt.o \
          obj/compiled/drivers/driver.o \
          obj/compiled/hrdwcom/port.o \
          obj/compiled/hrdwcom/interruptstubs.o \
          obj/compiled/hrdwcom/interrupts.o \
          obj/compiled/drivers/keyboard.o \
          obj/compiled/drivers/mouse.o \
          obj/compiled/kernel.o


run: GENOS.iso
	qemu-system-x86_64 -cdrom obj/GENOS.iso

obj/compiled/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

obj/compiled/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

GENOS.iso: linker.ld $(objects)
		ld $(LDPARAMS) -T $< -o obj/GENOS.bin $(objects)
		cp -r data/* obj/iso/
		cp obj/GENOS.bin obj/iso/boot/
		grub-mkrescue --output=obj/GENOS.iso obj/iso

install: GENOS.bin
	sudo cp $< /boot/GENOS.bin

.PHONY: clear
clear:
		rm -r obj/compiled/* obj/iso/* obj/GENOS.bin obj/GENOS.iso



.PHONY: clean
clean:
	rm -r obj/compiled/*
