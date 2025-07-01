BITS 16
ORG 0x7C00

main:
    call halt

halt:
    jmp halt

TIMES 510-($-$$) DB 0

DW 0AA55h