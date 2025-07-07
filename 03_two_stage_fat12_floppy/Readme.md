# FAT12 Two-Stage Bootloader & Kernel

**Welcome to my latest bare-metal hack!** 🚀  
This project demonstrates a true two-stage x86 real-mode bootloader that lives on a FAT12 floppy and a small “kernel” that gets loaded and executed at 0x7E00. No OS, no cheats—just raw NASM, BIOS interrupts, and a healthy dose of disk geometry math.

## 🧠 How It Works

1. **Stage 1 Bootloader**  
   - Lives at sector 0 (LBA 0 → 0×0000:0×7C00)  
   - Contains a FAT12 BIOS Parameter Block (BPB) **only** for your loader’s CHS calculations  
   - Implements `lba_to_chs` + `disk_read` via `INT 13h` with retries & error handling  
   - Reads sector 1 (LBA 1) into 0×0000:0×7E00 and `jmp 0x0000:0x7E00`  

2. **Stage 2 Kernel**  
   - Assembled with `ORG 0x7E00` so labels/data map correctly  
   - Simple `print` routine via `INT 10h` teletype to show  
     ```
     Hi, I’m printing from the kernel!
     ```  
   - Executes `hlt` in an infinite loop  

3. **Makefile Magic**  
   - `make bootloader` → NASM → `build/boot.bin`  
   - `make kernel`     → NASM → `build/kernel.bin`  
   - `make floppy_img` → `dd` zeros + `boot.bin` @ sector 0 + `kernel.bin` @ sector 1  
   - `make boot`       → QEMU spins up the floppy and boots  