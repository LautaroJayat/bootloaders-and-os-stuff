BITS 16
ORG 0x0 

%define LINE_END 0x0D, 0x0A

main:     
    mov si, os__msg
    mov di, 0
    call print
    call halt

print:
    push si
    push ax
    push bx

print_loop:
    lodsb
    or al, al
    jz done_printing
    mov ah, 0x0E
    mov bh, 0
    int 0x10
    jmp print_loop

done_printing:
    pop bx
    pop ax
    pop si
    ret

halt:
    hlt
    jmp halt

os__msg: DB "Hi, I'm printing from the kernel!", LINE_END, 0

TIMES 510-($-$$) db 0
