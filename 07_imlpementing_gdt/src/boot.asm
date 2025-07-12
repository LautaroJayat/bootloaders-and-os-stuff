BITS 32

section .text
    ALIGN 4
    DD 0x1BADB002
    DD 0X00000000
    DD -(0x1BADB002 + 0X00000000)

global start
extern kmain

start:
    CLI
    mov esp, stack_space
    CALL kmain
    HLT

haltKernel:
    CLI
    HLT
    jmp haltKernel

section .bss
RESB 8192

stack_space: