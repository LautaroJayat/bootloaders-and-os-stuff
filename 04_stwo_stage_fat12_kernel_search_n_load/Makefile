ASM=nasm

SRC_DIR=src
BUILD_DIR=build


floppy_img: $(BUILD_DIR)/floppy.img

$(BUILD_DIR)/floppy.img: kernel bootloader
	dd if=/dev/zero of=$(BUILD_DIR)/floppy.img bs=512 count=2880
	mkfs.fat -F 12 -n "LAUTAROJA" $(BUILD_DIR)/floppy.img
	dd if=$(BUILD_DIR)/boot.bin of=$(BUILD_DIR)/floppy.img bs=512 count=1 conv=notrunc
	mcopy -i $(BUILD_DIR)/floppy.img $(BUILD_DIR)/kernel.bin "::kernel.bin"

bootloader: $(BUILD_DIR)/boot.bin

$(BUILD_DIR)/boot.bin: $(SRC_DIR)/boot/main.asm
	$(ASM) $(SRC_DIR)/boot/main.asm -f bin -o $(BUILD_DIR)/boot.bin


kernel: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: $(SRC_DIR)/kernel/main.asm
	$(ASM) $(SRC_DIR)/kernel/main.asm -f bin -o $(BUILD_DIR)/kernel.bin


boot: $(BUILD_DIR)/floppy.img
	qemu-system-i386 -fda $(BUILD_DIR)/floppy.img