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

| Experiment                                                                                                                               | Description                                                                                                                                                                  |
| ---------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [`01_hello_boot/`](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/01_hello_boot)                                     | A minimal 512-byte boot sector that simply halts the CPU.                                                                                                                    |
| [`02_hello_world/`](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/02_hello_world)                                   | A boot sector that prints a message via BIOS interrupts, waits for three keypresses, then halts.                                                                             |
| [`03_two_stage_fat12_floppy/`](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/03_two_stage_fat12_floppy)             | A two-stage FAT12 loader: Stage 1 reads the FAT12 BPB, converts LBA to CHS, and loads sector 1; Stage 2 is linked at 0x7E00, prints a message, then halts.                   |
| [`04_kernel_search_n_load/`](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/04_kernel_search_n_load)                 | A two-stage FAT12 loader: Stage 1 reads the FAT12 BPB, converts LBA to CHS, then finds the kernel in the disk image; Stage 2 is then executed, prints a message, then halts. |
| [`05_simplest_grub/`](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/05_simplest_grub)                               | The simplest way to make your kernel boot using grub. Here we offload all the setup for protected mode and load directly into grub :)                                        |
| [`06_writing_to_video_memory/`](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/06_writing_to_video_memory)           | Creating a simple routine to print some messages by writing directly to video memory                                                                                         |
| [`07_imlpementing_gdt/`](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/07_imlpementing_gdt)                         | A simple example on loading a global descriptor table (GDT) to set memory spaces for kernel and user processes                                                               |
| [`08_task_state_segment/`](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/08_task_state_segment)                     | Implementing Task State Segment (TSS) to manage task switching and privilege levels in protected mode                                                                        |
| [`09_interruptor_descriptor_table/`](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/09_interruptor_descriptor_table) | Setting up the Interrupt Descriptor Table (IDT) to handle CPU exceptions and hardware interrupts                                                                             |
| [`10_programmable_interval_timer/`](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/10_programmable_interval_timer)   | Implementing the Programmable Interval Timer (PIT) for system timing and task scheduling                                                                                     |

---

## 📎 Purpose

I’m exploring how machines boot from raw binary instructions. This project is my personal deep dive into low-level systems: starting from the tiniest 512-byte boot stub, moving on to two-stage loaders, and eventually building a toy OS from scratch.

---

## Resources

- [Building an OS - Nanobyte - Youtube Playlist](https://youtu.be/9t-SPC7Tczc?si=yrY9SwBcBSlTdqM8)
- [x86 Operating Systems - OliveSteam - Youtube Playlist](https://www.youtube.com/watch?v=6zPBNEDKbpk&ist=PL2EF13wm-hWAglI8rRbdsCPq_wRpYvQQy)
- [x86 Assembly - OliveSteam - Youtube Playlist](https://www.youtube.com/watch?v=yBO-EJoVDo0&list=PL2EF13wm-hWCoj6tUBGUmrkJmH1972dBB)
- [Coredumped - Youtube channel](https://www.youtube.com/@CoreDumpped/featured)
- [Write Your Own 64-bit Operating System Kerne - CodePulse - Youtube Playlist](https://www.youtube.com/watch?v=FkrpUaGThTQ&list=PLZQftyCk7_SeZRitx5MjBKzTtvk0pHMtp)
- [Intro x86 (32 bit) - OpenSecurityTraining2 - Youtube playlist ](https://www.youtube.com/watch?v=H4Z0S9ZbC0g&list=PL038BE01D3BAEFDB0)
- [Intermediate x86 (32 bit) - OpenSecurityTraining2 - Youtube playlist ](https://www.youtube.com/watch?v=8b0wZhDvLCM&list=PL8F8D45D6C1FFD177)
- [Architecture 1001: Intel x86-64 Assembly - OpenSecurityTraining2 - Youtube Playlist](https://www.youtube.com/watch?v=9r169a3bun0&list=PLUFkSN0XLZ-m9B0DhHjkXd8foIMuZO1Gd)
- [Architecture 2001: Intel x86-64 OS Internals - OpenSecurityTraining2 - Youtube Playlist](https://www.youtube.com/watch?v=YxCILdaQtxs&list=PLUFkSN0XLZ-myVyCmMvfz_W5Z5SauI3cN)
- [Osdev Wiki - Main Page](https://osdev.wiki/wiki/Main_Page)
- [Osdev Wiki - BIOS](https://osdev.wiki/wiki/BIOS)
- [Osdev Wiki - Global Descriptor Table](https://osdev.wiki/wiki/Global_Descriptor_Table)
- [Osdev Wiki - Global Descriptor Table Tutorial](https://osdev.wiki/wiki/GDT_Tutorial)
- [Osdev Wiki - Interrupts](https://osdev.wiki/wiki/Interrupts)
- [Osdev Wiki - Interrupt Descriptor Table](https://osdev.wiki/wiki/Interrupt_Descriptor_Table)

## 📬 Feedback or Ideas?

Feel free to fork, clone, or open issues. This is a personal playground—but you’re welcome to join the journey!
