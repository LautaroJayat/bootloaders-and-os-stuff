# GRUB Multiboot x86 Kernel (Super Kernel)

**Booting bare metal in 32-bit protected mode using grub!** 🔥  
This project is a starting point for building a Multiboot-compliant kernel using GRUB, NASM, and C. It runs in QEMU and boots from an ISO image built with `grub-mkrescue`.
It isn't doing too much, just a blank screen, but its just for practice and understanding how this works.

## 🧠 How It Works

1. **Multiboot Bootloader (boot.asm)**  
   - NASM file with a GRUB-compatible multiboot header  
   - Sets up the stack and calls the C `kmain()` function  
   - No BIOS calls, already in protected mode

2. **Kernel (kernel.c)**  
   - Simple C stub function for now  
   - Expand it with printing, memory management, interrupts, etc.

3. **Linker Script (linker.ld)**  
   - Tells the linker to place the kernel at 1MB (0x100000)  
   - Aligns `.text`, `.data`, and `.bss`

4. **GRUB + ISO Image**  
   - Uses `grub.cfg` to load the kernel with `multiboot`  
   - Generates an ISO using `grub-mkrescue`