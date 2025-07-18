ASM=nasm
GCC=gcc
CFLAGS= -m32 -fno-stack-protector -fno-builtin
GRUB=grub-mkrescue


SRC_DIR=src
BUILD_DIR=build
GRUB_BOT_DIR=super_kernel/boot/grub
GRUB_KERNEL_DIR=super_kernel/boot



$(BUILD_DIR)/kernel.iso: bin kernel bootloader 
	$(GRUB) -o $(BUILD_DIR)/kernel.iso super_kernel/

bin: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: kernel bootloader $(SRC_DIR)/linker.ld 
	ld -m elf_i386 -T $(SRC_DIR)/linker.ld -o $(GRUB_KERNEL_DIR)/kernel $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/vga.o $(BUILD_DIR)/lgdt.o $(BUILD_DIR)/gdt.o   $(BUILD_DIR)/memset.o

kernel: $(BUILD_DIR)/kernel.o vga

$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c vga gdt lgdt
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/kernel.c -o $(BUILD_DIR)/kernel.o

vga: $(BUILD_DIR)/vga.o

$(BUILD_DIR)/vga.o: $(SRC_DIR)/vga.c $(SRC_DIR)/vga.h
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/vga.c -o $(BUILD_DIR)/vga.o

gdt: $(BUILD_DIR)/gdt.o

$(BUILD_DIR)/gdt.o: $(SRC_DIR)/gdt.h $(SRC_DIR)/gdt.h memset
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/gdt.c -o $(BUILD_DIR)/gdt.o

memset: $(BUILD_DIR)/memset.o

$(BUILD_DIR)/memset.o: $(SRC_DIR)/memset.c $(SRC_DIR)/memset.h
	$(GCC) $(CFLAGS) -c $(SRC_DIR)/memset.c -o $(BUILD_DIR)/memset.o

lgdt: $(BUILD_DIR)/lgdt.o

$(BUILD_DIR)/lgdt.o: $(SRC_DIR)/gdt.asm
	$(ASM) -f elf32 $(SRC_DIR)/gdt.asm -o $(BUILD_DIR)/lgdt.o

bootloader: $(BUILD_DIR)/boot.o

$(BUILD_DIR)/boot.o: $(SRC_DIR)/boot.asm
	$(ASM) -f elf32 $(SRC_DIR)/boot.asm -o $(BUILD_DIR)/boot.o


boot:
	qemu-system-i386 $(BUILD_DIR)/kernel.iso
