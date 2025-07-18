# :alien: Super Kernel — GDT and TSS Setup

Welcome to the next evolution of our kernel! This phase focuses on refining our Global Descriptor Table (GDT) and introducing the Task State Segment (TSS) to enable seamless privilege transitions and prepare for user-mode execution. Let’s dive into the concepts behind these changes and why they matter.

---

## GDT: The Backbone of Protected Mode

The GDT is the foundation of memory segmentation in protected mode. It defines how the CPU interprets memory, enabling privilege separation (ring 0 for the kernel, ring 3 for user space) and controlling access to executable and writable regions.

Our GDT now includes **six entries**:
- Null descriptor (placeholder)
- Kernel code and data segments (ring 0)
- User code and data segments (ring 3)
- **A new TSS descriptor** for managing privilege transitions

This setup ensures a flat memory model with clear boundaries between kernel and user space, paving the way for safe multitasking and system calls.

---

## TSS: The Key to Privilege Transitions

The Task State Segment (TSS) is a special structure that allows the CPU to switch stacks and manage state during privilege transitions. It’s essential for handling interrupts and system calls when moving between user and kernel modes.

Here’s what the TSS brings to the table:
- A dedicated kernel stack for handling user-mode interrupts
- Automatic state saving and restoration during transitions
- Support for user-mode segments, enabling safe execution outside the kernel

By adding the TSS to our GDT, we’ve unlocked the ability to safely manage privilege levels, a critical step toward a fully functional operating system.

---

## The Bigger Picture

This isn’t just about adding entries to a table or writing some C code. It’s about building the scaffolding for a real operating system. With the GDT and TSS in place, we’re laying the groundwork for:
- User-mode applications
- System calls
- Advanced multitasking

The kernel is no longer just a flat binary—it’s becoming a structured, modular system capable of handling complex tasks. And the best part? We’re just getting started.

---

## What’s Next?

With the GDT and TSS ready, the next step is to implement user-mode transitions and system calls. This will allow us to run isolated user applications while maintaining full control in the kernel. Stay tuned—things are about to get even more exciting! 🚀