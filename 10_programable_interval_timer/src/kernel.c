#include "./gdt.h"
#include "./interrupts/idt.h"
#include "./timer/timer.h"
#include "./vga.h"

void kmain(void);

void kmain(void)
{
    Reset();
    print("Hello from the Kernel!!\r\n");
    print("I'm writing directly into video memory\r\n");
    initGdt();
    print("GDT Loaded!!\r\n");
    print(":)\n");
    initIdt();
    print("IDT Already Set!\r\n");
    initTimer();
    for (;;)
        ;
};