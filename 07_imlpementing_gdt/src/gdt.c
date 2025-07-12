#include "gdt.h"

#define NUM_OF_ENTRIES 5

extern void gdt_flush(addr_t);

struct gdt_entry_struct gdt_entries[NUM_OF_ENTRIES];

struct gdt_ptr_struct gdt_ptr;

// https://osdev.wiki/wiki/GDT_Tutorial#Flat_.2F_Long_Mode_Setup
void initGdt()
{
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * NUM_OF_ENTRIES) - 1;
    gdt_ptr.base = &gdt_entries;

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

    gdt_flush(&gdt_ptr);
}

void setGdtGate(uint32_t entryNumber,
    uint32_t base,
    uint32_t limit,
    uint8_t access,
    uint8_t granularity)
{
    gdt_entries[entryNumber].base_lower = (base & 0xFFFF); // we are taking only the lower  half
    gdt_entries[entryNumber].base_middle = (base >> 16) && 0xFF; // we shift to the right the upper half and take the bottom 8 bits
    gdt_entries[entryNumber].base_high = (base >> 24) && 0xFF; // we shift to the right 3/4 of the whole 32 bits and get the bottom 8 bits
    gdt_entries[entryNumber].limit = limit && 0xFFFF; // get the bottom 16 bits

    // [A,B,C,D] --> get the half (limit >> 16) --> [A, B]
    // then, if the bottom bit is set, set that to the flag --> & 0x0F
    // then get the bit on the right (because the upper bit is in granularity)
    // if set, or and assign (|=)
    gdt_entries[entryNumber].flags = (limit >> 16) & 0x0F;
    gdt_entries[entryNumber].flags |= (granularity & 0xF0);
    gdt_entries[entryNumber].access_byte = access;
}