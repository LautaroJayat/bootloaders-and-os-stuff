# 🧨 02 - Printing + Keypress Bootloader (16-bit Assembly)

This is my second bootloader experiment.

It prints a message using BIOS, waits for keypresses, and prints again — all from a 16-bit real mode boot sector.

---

## 🧠 What It Does

- Sets up segment and stack registers
- Prints: `Hi, I'm printing from the boot process`
- Waits for keypress 3 times, reprinting the message each time
- Then halts forever

Everything runs before any operating system exists.