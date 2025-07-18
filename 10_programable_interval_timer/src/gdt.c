#include "gdt.h"
#include "memset.h"

#define NUM_OF_ENTRIES 6

extern void gdt_flush(uint32_t);
extern void tss_flush();

struct gdt_entry_struct gdt_entries[NUM_OF_ENTRIES];

struct gdt_ptr_struct gdt_ptr;

struct tss_entry_struct tss_entry;

// https://osdev.wiki/wiki/GDT_Tutorial#Flat_.2F_Long_Mode_Setup
void initGdt()
{
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * NUM_OF_ENTRIES) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    setGdtGate(0, 0, 0, 0, 0); // null segment

    // kernel code segment 0x9A -> 1001 1010
    setGdtGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // kernel data segment 0x92 -> 1001 0010
    setGdtGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // kernel code segment 0xFA -> 1111 1010
    // (the 11 is 3 in the middle to say ring 3)
    setGdtGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    // kernel code segment 0xF2 -> 1111 0010
    setGdtGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    writeTSS(5, 0x10, 0x0); // 0x10 is the actual offset where is located

    gdt_flush(&gdt_ptr);
    tss_flush();
}

void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0)
{
    uint32_t base = (uint32_t)&tss_entry;
    uint32_t limit = base + sizeof(tss_entry) -1;

    // 0xE9
    // (1)       (11)            (0)           (1)          (0)                 (0)           (1)
    // (enabled) (usermode = 3 ) (tasksegment) (executable) (segment grows down)(not writable)
    setGdtGate(num, base, limit, 0xE9, 0x00);
    memset(&tss_entry, 0, sizeof(tss_entry));
    tss_entry.ss0 = ss0; // 0x10 stack segment
    tss_entry.esp0 = esp0; // stack pointer is 0

    // it adds the user mode, so we can use the tss to switch from usermode to kernelmode
    tss_entry.cs = 0x08 | 0x3;
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;
};

void setGdtGate(uint32_t entryNumber,
    uint32_t base,
    uint32_t limit,
    uint8_t access,
    uint8_t granularity)
{
    gdt_entries[entryNumber].base_lower = (base & 0xFFFF); // we are taking only the lower  half
    gdt_entries[entryNumber].base_middle = (base >> 16) & 0xFF; // we shift to the right the upper half and take the bottom 8 bits
    gdt_entries[entryNumber].base_high = (base >> 24) & 0xFF; // we shift to the right 3/4 of the whole 32 bits and get the bottom 8 bits
    gdt_entries[entryNumber].limit = limit & 0xFFFF; // get the bottom 16 bits

    // [A,B,C,D] --> get the half (limit >> 16) --> [A, B]
    // then, if the bottom bit is set, set that to the flag --> & 0x0F
    // then get the bit on the right (because the upper bit is in granularity)
    // if set, or and assign (|=)
    gdt_entries[entryNumber].flags = (limit >> 16) & 0x0F;
    gdt_entries[entryNumber].flags |= (granularity & 0xF0);
    gdt_entries[entryNumber].access_byte = access;
}