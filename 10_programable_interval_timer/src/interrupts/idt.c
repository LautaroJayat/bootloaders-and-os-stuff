#include "idt.h"
#include "../memset.h"
#include "../outportb.h"
#include "../vga.h"

#define NUM_IDT_ENTRIES 256

struct idt_entry_struct idt_entries[NUM_IDT_ENTRIES];
struct idt_ptr_struct idt_ptr;

extern void idt_flush(uint32_t);

void initIdt()
{
    idt_ptr.limit = sizeof(struct idt_entry_struct) * NUM_IDT_ENTRIES - 1;
    idt_ptr.base = (uint32_t)&idt_entries;

    memset(&idt_entries, 0, sizeof(struct idt_entry_struct) * NUM_IDT_ENTRIES);

    // https://wiki.osdev.org/8259_PIC#Initialisation

    // Start initialization sequence (ICW1) for both PICs
    outPortB(0x20, 0x11); // Master PIC command port: 0x11 = start init, expect ICW4
    outPortB(0xA0, 0x11); // Slave PIC command port: 0x11 = start init, expect ICW4

    // Set vector offset (ICW2)
    outPortB(0x21, 0x20); // Master PIC data port: IRQ0–7 mapped to INT 0x20–0x27
    outPortB(0xA1, 0x28); // Slave PIC data port: IRQ8–15 mapped to INT 0x28–0x2F

    // Setup cascading (ICW3)
    outPortB(0x21, 0x04); // Master PIC: bit 2 set → slave PIC at IRQ2
    outPortB(0xA1, 0x02); // Slave PIC: cascade identity = 2 (connected to master's IRQ2)

    // Set environment info (ICW4)
    outPortB(0x21, 0x01); // Master PIC: 8086/88 mode
    outPortB(0xA1, 0x01); // Slave PIC: 8086/88 mode

    // Clear interrupt masks (initial state — all IRQs enabled)
    outPortB(0x21, 0x0); // Master PIC: unmask all IRQs
    outPortB(0xA1, 0x0); // Slave PIC: unmask all IRQs

    // Set final masks
    outPortB(0x21, 0xFE); // Master PIC: 1111_1110 → only IRQ0 (timer) unmasked
    outPortB(0xA1, 0xFF); // Slave PIC: 1111_1111 → all IRQs masked

    // 0x8E 1000 1110 -->
    // 0x08 0000 1000 --> points to a valid segment in the GDT
    setIdtGate(0, (uint32_t)isr0, 0x08, 0x8E);
    setIdtGate(1, (uint32_t)isr1, 0x08, 0x8E);
    setIdtGate(2, (uint32_t)isr2, 0x08, 0x8E);
    setIdtGate(3, (uint32_t)isr3, 0x08, 0x8E);
    setIdtGate(4, (uint32_t)isr4, 0x08, 0x8E);
    setIdtGate(5, (uint32_t)isr5, 0x08, 0x8E);
    setIdtGate(6, (uint32_t)isr6, 0x08, 0x8E);
    setIdtGate(7, (uint32_t)isr7, 0x08, 0x8E);
    setIdtGate(8, (uint32_t)isr8, 0x08, 0x8E);
    setIdtGate(9, (uint32_t)isr9, 0x08, 0x8E);
    setIdtGate(10, (uint32_t)isr10, 0x08, 0x8E);
    setIdtGate(11, (uint32_t)isr11, 0x08, 0x8E);
    setIdtGate(12, (uint32_t)isr12, 0x08, 0x8E);
    setIdtGate(13, (uint32_t)isr13, 0x08, 0x8E);
    setIdtGate(14, (uint32_t)isr14, 0x08, 0x8E);
    setIdtGate(15, (uint32_t)isr15, 0x08, 0x8E);
    setIdtGate(16, (uint32_t)isr16, 0x08, 0x8E);
    setIdtGate(17, (uint32_t)isr17, 0x08, 0x8E);
    setIdtGate(18, (uint32_t)isr18, 0x08, 0x8E);
    setIdtGate(19, (uint32_t)isr19, 0x08, 0x8E);
    setIdtGate(20, (uint32_t)isr20, 0x08, 0x8E);
    setIdtGate(21, (uint32_t)isr21, 0x08, 0x8E);
    setIdtGate(22, (uint32_t)isr22, 0x08, 0x8E);
    setIdtGate(23, (uint32_t)isr23, 0x08, 0x8E);
    setIdtGate(24, (uint32_t)isr24, 0x08, 0x8E);
    setIdtGate(25, (uint32_t)isr25, 0x08, 0x8E);
    setIdtGate(26, (uint32_t)isr26, 0x08, 0x8E);
    setIdtGate(27, (uint32_t)isr27, 0x08, 0x8E);
    setIdtGate(28, (uint32_t)isr28, 0x08, 0x8E);
    setIdtGate(29, (uint32_t)isr29, 0x08, 0x8E);
    setIdtGate(30, (uint32_t)isr30, 0x08, 0x8E);
    setIdtGate(31, (uint32_t)isr31, 0x08, 0x8E);
    setIdtGate(32, (uint32_t)irq0, 0x08, 0x8E);
    setIdtGate(33, (uint32_t)irq1, 0x08, 0x8E);
    setIdtGate(34, (uint32_t)irq2, 0x08, 0x8E);
    setIdtGate(35, (uint32_t)irq3, 0x08, 0x8E);
    setIdtGate(36, (uint32_t)irq4, 0x08, 0x8E);
    setIdtGate(37, (uint32_t)irq5, 0x08, 0x8E);
    setIdtGate(38, (uint32_t)irq6, 0x08, 0x8E);
    setIdtGate(39, (uint32_t)irq7, 0x08, 0x8E);
    setIdtGate(40, (uint32_t)irq8, 0x08, 0x8E);
    setIdtGate(41, (uint32_t)irq9, 0x08, 0x8E);
    setIdtGate(42, (uint32_t)irq10, 0x08, 0x8E);
    setIdtGate(43, (uint32_t)irq11, 0x08, 0x8E);
    setIdtGate(44, (uint32_t)irq12, 0x08, 0x8E);
    setIdtGate(45, (uint32_t)irq13, 0x08, 0x8E);
    setIdtGate(46, (uint32_t)irq14, 0x08, 0x8E);
    setIdtGate(47, (uint32_t)irq15, 0x08, 0x8E);

    setIdtGate(128, (uint32_t)isr128, 0x08, 0x8E); // system calls
    setIdtGate(177, (uint32_t)isr177, 0x08, 0x8E); // system calls

    idt_flush((uint32_t)&idt_ptr);
};

void setIdtGate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{

    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].segment_selector = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags | 0x60;
};

unsigned char* exception_messages[] = {
    "Division by zero",
    "Debug",
    "Non maskable interrupt",
    "Breakpoint",
    "Into detected overflow",
    "Out of bounds",
    "Invalid opcode",
    "No coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt",
    "Coprocessor fault",
    "Alignment fault",
    "Machine checck",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

void isr_handler(struct InterruptRegisters* regs)
{
    if (regs->int_no < 32) {
        print(exception_messages[regs->int_no]);
        print("\n\n");
        print("Exception! System Halted!\n");
        for (;;)
            ;
    }
}
void* irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void irq_install_handler(int irq, void (*handler)(struct InterruptRegisters* r))
{
    irq_routines[irq] = handler;
};

void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
};

void irq_handler(struct InterruptRegisters* regs)
{
    void (*handler)(struct InterruptRegisters* regs);
    handler = irq_routines[regs->int_no - 32]; // because the irq starts at 32, so 0-16 + 32

    if (handler) {
        handler(regs);
    }

    if (regs->int_no >= 40) {
        outPortB(0xA0, 0x20);
    }

    outPortB(0x20, 0x20);
};