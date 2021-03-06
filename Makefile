GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fno-stack-protector -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386

# objects = loader.o gdt.o driver.o port.o interruptstubs.o interrupts.o keyboard.o mouse.o kernel.o bouncy_ball.o
objects = obj/loader.o \
          obj/gdt.o \
          obj/drivers/driver.o \
          obj/hardwarecommunication/port.o \
          obj/hardwarecommunication/interruptstubs.o \
          obj/hardwarecommunication/interrupts.o \
          obj/hardwarecommunication/pci.o \
          obj/drivers/keyboard.o \
          obj/drivers/mouse.o \
          obj/drivers/vga.o \
          obj/gui/widget.o \
          obj/gui/window.o \
          obj/gui/desktop.o \
          obj/kernel.o \
          obj/bouncy_ball.o \
          obj/common/stdio.o \
          obj/common/cpu.o

obj/%.o: source/%.cpp
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

obj/%.o: source/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

mykernel.iso: mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp mykernel.bin iso/boot/mykernel.bin
	echo 'set timeout=1'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "GROS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/mykernel.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue  -o mykernel.iso iso --locale-directory= --themes=
	rm -rf iso

# the viktor tutorial was using vbox but it didn't work on my install
# so imma use qemu instead of vbox
run: mykernel.iso
	(killall qemu-i386 && sleep 1) || true
	qemu-system-x86_64 -drive format=raw,file=mykernel.iso -m 512m -cpu core2duo -serial stdio -serial file:CON


.PHONY: clean
clean:
	rm -rf obj mykernel.bin mykernel.iso
