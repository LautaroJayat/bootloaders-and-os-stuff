# 🎥 Writing to Video Memory! (Super Kernel)

After successfully booting our bare-metal kernel using GRUB in 32-bit protected mode, we're now taking the next big step—**directly writing to video memory** to display text on the screen. This is an exciting moment because we are no longer relying on BIOS interrupts (which aren't available in protected mode)—we're now talking to the hardware ourselves! 💪

This feature gives us basic output capability, enabling us to build more complex debugging and system messaging functions from here on.

---

## 🧠 How It Works (Updated)

### 1. **Multiboot Bootloader (`boot.asm`)**
- This assembly file defines a Multiboot header, allowing GRUB to load our kernel.
- It sets up a basic stack and then jumps to our C `kmain()` function.
- No BIOS calls—GRUB puts us directly into 32-bit **protected mode**.

### 2. **Kernel (`kernel.c`)**
- Starts by calling `Reset()` to clear the screen.
- Uses `print()` to display a message directly to video memory.
- We'll keep enhancing this with custom printing, colors, scrolling, and formatting.

### 3. **Video Output (`vga.c` + `vga.h`)**
- Implements basic `print()` logic by writing characters to memory address `0xB8000`.
- Includes support for new lines (`\n`), carriage returns (`\r`), and tabs (`\t`).
- Manages screen scrolling and cursor position.

### 4. **Linker Script (`linker.ld`)**
- Places the kernel at memory address `0x100000` (1MB).
- Organizes `.text`, `.data`, and `.bss` sections correctly for GRUB and the CPU.

### 5. **GRUB + ISO Image**
- We use `grub.cfg` to load the kernel with the `multiboot` directive.
- An ISO is generated using `grub-mkrescue` for booting in QEMU.
