# Bootloaders and OS Stuff

This repository contains a collection of experiments related to bootloaders and operating systems, written in assembly. Each file is a minimal working example designed to test or demonstrate a specific idea in early-stage system programming.

## Requirements

To build and run the experiments, you'll need:

- [NASM](https://www.nasm.us/) – Netwide Assembler
- [QEMU](https://www.qemu.org/) – Emulator for testing bootable binaries

Each folder includes its own `Makefile` to compile and run the corresponding experiment.

## Experiments

| Name | Description | Link |
|------|-------------|------|
| Hello Boot | Minimal bootable program that halts the CPU. | [01_hello_boot.asm](https://github.com/LautaroJayat/bootloaders-and-os-stuff/blob/main/01_hello_boot.asm) |
| Hello World | Prints a message using BIOS interrupts, waits for key presses, and repeats. | [02_hello_world.asm](https://github.com/LautaroJayat/bootloaders-and-os-stuff/blob/main/02_hello_world.asm) |
