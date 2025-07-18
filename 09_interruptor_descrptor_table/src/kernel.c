#include "./gdt.h"
#include "./interrupts/idt.h"
#include "./vga.h"
void kmain(void);

void kmain(void)
{
    initGdt();
    Reset();
    print("Hello from the Kernel!!\r\n");
    print("I'm writing directly into video memory\r\n");
    print(":)\n");
    initIdt();
    print("IDT Loaded!\r\n");
    // ——— Dump the loaded IDT register ———
    struct idt_ptr_struct loaded;
    __asm__ volatile("sidt %0" : "=m"(loaded));
    print("IDT limit = ");
    print_hex(loaded.limit);
    print("\r\n");
    print("IDT base  = ");
    print_hex(loaded.base);
    print("\r\n");
    // ——— Verify ISR0 address from your table ———
    extern struct idt_entry_struct idt_entries[];
    uint32_t isr0_addr = ((uint32_t)idt_entries[0].base_high << 16)
        | (uint32_t)idt_entries[0].base_low;
    print("ISR0 at   = ");
    print_hex(isr0_addr);
    print("\r\n");
    volatile int a = 2;
    volatile int b = 0;
    volatile int c = a / b;   // yields IDIV ebx,ecx with ebx==0 → #DE
    //print(2 / 0);
};