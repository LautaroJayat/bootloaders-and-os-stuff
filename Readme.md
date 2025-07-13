# :alien: Bootloaders and OS Stuff

This repository contains a collection of experiments related to bootloaders and operating systems, written in assembly, C, and who knows what else. Each folder has a minimal working example designed to test or demonstrate a specific idea in early-stage system programming.

---

## 🛠 Requirements

To build and run the experiments, you’ll need:

- [NASM](https://www.nasm.us/) – Netwide Assembler  
- [QEMU](https://www.qemu.org/) – Emulator for testing bootable binaries  
- [GNU Make](https://www.gnu.org/software/make/) – Build automation tool (or compatible)  

Each experiment has its own `Makefile` to assemble and launch in QEMU.

---

## 📂 Experiments

| Experiment                   | Description                                                        | README                                                                                                                                       |
|------------------------------|--------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------|
| `01_hello_boot/`             | A minimal 512-byte boot sector that simply halts the CPU.          | [View README](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/01_hello_boot)                                               |
| `02_hello_world/`            | A boot sector that prints a message via BIOS interrupts, waits for three keypresses, then halts. | [View README](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/02_hello_world)                                              |
| `03_two_stage_fat12_floppy/` | A two-stage FAT12 loader: Stage 1 reads the FAT12 BPB, converts LBA to CHS, and loads sector 1; Stage 2 is linked at 0x7E00, prints a message, then halts. | [View README](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/03_two_stage_fat12_floppy)                                    |
| `04_kernel_search_n_load/` | A two-stage FAT12 loader: Stage 1 reads the FAT12 BPB, converts LBA to CHS, then finds the kernel in the disk image; Stage 2 is then executed, prints a message, then halts. | [View README](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/04_kernel_search_n_load)                                    |
| `05_simplest_grub/` | The simplest way to make your kernel boot using grub. Here we offload all the setup for protected mode and load directly into grub :) | [View README](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/05_simplest_grub)                                    |
| `06_writing_to_video_memory/` | Creating a simple routine to print some messages by writing directly to video memory | [View README](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/06_writing_to_video_memory)                                    |
| `07_imlpementing_gdt/` | A simple example on loading a global descriptor table (GDT) to set memory spaces for kernel and user processes | [View README](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/07_imlpementing_gdt)                                    |



---

## 📎 Purpose

I’m exploring how machines boot from raw binary instructions. This project is my personal deep dive into low-level systems: starting from the tiniest 512-byte boot stub, moving on to two-stage loaders, and eventually building a toy OS from scratch.

---

## 📬 Feedback or Ideas?

Feel free to fork, clone, or open issues. This is a personal playground—but you’re welcome to join the journey!
