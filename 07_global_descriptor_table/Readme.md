# :alien: Super Kernel — GDT Setup

This kernel experiment centers around crafting a custom Global Descriptor Table (GDT) to define memory segments for both kernel and user-space execution, and packaging it into a bootable ISO that GRUB can load in protected mode.

## GDT Structure and Purpose

The GDT (Global Descriptor Table) defines how memory segments behave in protected mode. This is crucial for enabling privilege separation (ring 0 vs ring 3) and for defining executable and readable regions of memory. Our GDT defines five entries:

- A null descriptor (required placeholder)
- A kernel code segment (ring 0, executable, readable)
- A kernel data segment (ring 0, readable, writable)
- A user code segment (ring 3, executable, readable)
- A user data segment (ring 3, readable, writable)

Each entry in the table includes a base address, limit (size), access byte, and flags. The access byte controls permissions and type (code/data, user/kernel), while flags determine granularity and mode (e.g. 32-bit mode).

The layout follows standard x86 protected mode conventions, with flat memory (base = 0, limit = 4 GiB) for each segment. The kernel segments are defined with DPL 0, and the user segments with DPL 3 to enable safe transitions when we eventually introduce user-mode code.

## GDT Loading Flow

The GDT is constructed in C and populated entry by entry. Each entry is packed into the exact binary structure expected by the CPU. Once the table is complete, a pointer structure is created that contains the size and memory address of the GDT.

To activate the GDT, we call an external assembly function. This function receives the GDT pointer and loads it using the LGDT instruction. Once the new table is in place, all segment registers (CS, DS, SS, etc.) must be updated to use the new segment descriptors.

Because modifying CS directly isn't allowed, a far jump (`jmp`) is used to reload it and flush the instruction pipeline. The other segment registers are updated via `mov` instructions using the appropriate segment selector values corresponding to the GDT entries.

At this point, the CPU uses the new GDT for segment lookups, enabling protected mode memory segmentation as configured.


## Kernel Packaging

The build process compiles C and assembly sources into 32-bit ELF objects, links them at physical address `0x100000`, and produces a flat binary wrapped in an ISO image using `grub-mkrescue`. GRUB boots the kernel using the Multiboot specification, which recognizes our multiboot header and jumps into our 32-bit entry point without relying on BIOS interrupts.