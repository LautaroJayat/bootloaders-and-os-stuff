#include "timer.h"
#include "../interrupts/idt.h"
#include "../outportb.h"
#include "../stdint.h"
#include "../vga.h"

uint64_t ticks;
const uint32_t freq = 1000;

void onIrq0(struct InterruptRegisters* regs)
{
    ticks += 1;
    print("Ticked!!\n\r");
};

void initTimer()
{
    ticks = 0;
    irq_install_handler(0, &onIrq0);

    uint32_t divisor = 1193180 / freq;

    outPortB(0x43, 0x36);
    outPortB(0x40, (uint8_t)(divisor & 0xFF));
    outPortB(0x40, (uint8_t)((divisor >> 8) & 0xFF));
};
