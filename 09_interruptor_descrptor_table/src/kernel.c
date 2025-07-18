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
    //print(2 / 0);
};