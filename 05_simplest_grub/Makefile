ASM=nasm
GCC=gcc
GRUB=grub-mkrescue

SRC_DIR=src
BUILD_DIR=build
GRUB_BOT_DIR=super_kernel/boot/grub
GRUB_KERNEL_DIR=super_kernel/boot



$(BUILD_DIR)/kernel.iso: bin kernel bootloader 
	$(GRUB) -o $(BUILD_DIR)/kernel.iso super_kernel/

bin: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: kernel bootloader $(SRC_DIR)/linker.ld
	ld -m elf_i386 -T $(SRC_DIR)/linker.ld -o $(GRUB_KERNEL_DIR)/kernel $(BUILD_DIR)/kernel.o $(BUILD_DIR)/boot.o

kernel: $(BUILD_DIR)/kernel.o

$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c
	$(GCC) -m32 -fno-stack-protector -fno-builtin -c $(SRC_DIR)/kernel.c -o $(BUILD_DIR)/kernel.o

bootloader: $(BUILD_DIR)/boot.o

$(BUILD_DIR)/boot.o: $(SRC_DIR)/boot.asm
	$(ASM) -f elf32 $(SRC_DIR)/boot.asm -o $(BUILD_DIR)/boot.o


boot:
	qemu-system-i386 $(BUILD_DIR)/kernel.iso