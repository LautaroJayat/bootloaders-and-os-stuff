BITS 16
ORG 0x7C00

main:
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    mov si, os_boot_msg
    mov di, 0
    call print
    call wait_and_print
    call halt

wait_and_print:
    push ax             ; store ax
    mov ah, 00h         ; instruction 00h is to wait for key
    int 16h             ; interrupt is now activated
    pop ax              ; we can get the content of ax
    inc di              ; we can increment di
    mov si, os_boot_msg ; because we will print again
    call print          ; print
    cmp di, 3           ; which iteration is this?
    jl wait_and_print   ; if lower than 3rd iteration, print again
    jmp halt            ; if not, go to halt

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

os_boot_msg: DB "Hi, I'm printing from the boot process", 0x0D, 0x0A,0

TIMES 510-($-$$) DB 0

DW 0AA55h