# 🧵 Bootloaders and OS Stuff

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

| Experiment | Description | README |
|-----------|-------------|--------|
| `01_hello_boot/` | Minimal bootable program that halts the CPU. | [View README](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/01_hello_boot) |
| `02_hello_world/` | Prints a message using BIOS interrupts, waits for keypresses, and repeats 3 times. | [View README](https://github.com/LautaroJayat/bootloaders-and-os-stuff/tree/main/02_hello_world) |


---

## 📎 Purpose

I'm just exploring how machines boot from raw binary instructions.  
This project is part of my personal deep dive into low-level systems — starting from scratch with assembly and gradually moving toward a toy OS.

---

## 📬 Feedback or Ideas?

Feel free to fork, clone, or open issues.  
This is a personal playground — but you're welcome to join the journey.