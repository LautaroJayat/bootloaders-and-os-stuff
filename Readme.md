# 🧵 Bootloaders and OS Stuff

This repository contains a collection of experiments related to bootloaders and operating systems, written in x86 assembly.  
Each folder is a minimal, working example focused on understanding the early stages of system boot.

---

## 🛠 Requirements

To build and run the experiments, you’ll need:

- [NASM](https://www.nasm.us/) – Netwide Assembler
- [QEMU](https://www.qemu.org/) – Emulator for testing bootable binaries
- [GNU Make](https://www.gnu.org/software/make/) – Build automation tool (or compatible)

Each experiment has its own `Makefile` to assemble and launch in QEMU.

---

## 📂 Experiments

| Experiment | Description | README |
|-----------|-------------|--------|
| `01_hello_boot/` | Minimal bootable program that halts the CPU. | [View README](./01_hello_boot/README.md) |
| `02_hello_world/` | Prints a message using BIOS interrupts, waits for keypresses, and repeats 3 times. | [View README](./02_print_loop_boot/README.md) |


---

## 📎 Purpose

I'm just exploring how machines boot from raw binary instructions.  
This project is part of my personal deep dive into low-level systems — starting from scratch with assembly and gradually moving toward a toy OS.

---

## 📬 Feedback or Ideas?

Feel free to fork, clone, or open issues.  
This is a personal playground — but you're welcome to join the journey.

