# FAT12 Two-Stage Bootloader (Reading from disk edition)

**Time to get your hands dirty!!** 🚀  
This project is an experiment for building a true two-stage x86 real-mode bootloader that lives on a FAT12 floppy and a small “kernel” that gets read and loaded from disk.
In this example we use the fat headers to search for the files and load them into memory.

## 🧠 How It Works

1. **Stage 1 Bootloader**  
   - Lives at sector 0 (LBA 0 → 0×0000:0×7C00)  
   - Contains a FAT12 BIOS Parameter Block (BPB)  
   - Implements `lba_to_chs` + `disk_read` via `INT 13h` with retries & error handling 
   - Implements little math to locate files in the FAT12 file system
   - Locates the kernel, loads it into memory and jups to its first instruction  

2. **Stage 2 Kernel**  
   - Assembled with `ORG 0x0`, no magic offsets needed  
   - Simple `print` routine via `INT 10h` teletype to show  
     ```
     Hi, I’m printing from the kernel!
     ```  
   - Executes `hlt` in an infinite loop  

3. **Makefile Magic**  
   - `make bootloader` → NASM → `build/boot.bin`  
   - `make kernel`     → NASM → `build/kernel.bin`  
   - `make floppy_img` → `dd` zeros + `boot.bin` @ sector 0  and then mcopy `kernel.bin` to kernel.bin inside the image  
   - `make boot`       → QEMU spins up the floppy and boots  