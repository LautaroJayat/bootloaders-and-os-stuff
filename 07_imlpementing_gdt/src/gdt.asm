global gdt_flush

gdt_flush:
    mov eax, [esp+4]
    LGDT [eax]

    mov eax, 0x10 ; this is the offset where the GDT lives
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush
.flush:
    ret