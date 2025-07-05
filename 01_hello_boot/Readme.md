# 🧨 01 - Minimal Boot Sector (16-bit Assembly)

This is the absolute minimal valid x86 bootloader, written in NASM.

It doesn’t print anything. It doesn’t do anything.  
**But it boots.** And that’s the whole point.

---

## 🧠 What It Does

This boot sector:

- Tells the BIOS "I am a bootable disk"
- Loads to memory address `0x7C00`
- Jumps to an infinite loop
- Nothing else

It’s the literal starting point of an OS — just enough to **not crash the computer**.