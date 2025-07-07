BITS 16
ORG 0x7C00


%define LINE_END 0x0D, 0x0A
%define READ_RETRIES 3

; FAT12 HEADERS BELLOW!
jmp short main
nop

bdb_oem:                        db 'MSWIN4.1' ;8 bytes
bdb_bytes_per_sector:           dw 512
bdb_sectors_per_cluster:        db 1
bdb_number_of_reserved_sectors: dw 1
bdb_fat_count:                  db 2
bdb_dir_entries_count:          dw 0E0h ; 224
bdb_total_sectors:              dw 2880 ; 2880 * 512 = 1.14mb (the floppy disk size)
bdb_media_descriptor_type:      db 0F0h ; F0 = 3.5" floppy disk
bdb_sectors_per_fat:            dw 9
bdb_sectors_per_track:          dw 18
bdb_heads:                      dw 2
dbd_number_of_hidden_sectors:   dd 0
bdb_large_sector_count:         dd 0

; EXTENDED BOOT RECOTD HEADERS
ebr_drive_number:               db 0
                                db 0                   ; reserved
ebr_signature:                  db 29h
ebr_volume_id:                  db 12h, 34h, 56h, 78h 
ebr_volume_label:               db 'LAUTAROJA  '       ; 11 BYTES
ebr_system_id:                  db 'FAT12   '          ; 8 bytes



; NOW THE ACTUAL CODE!

main:
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    ; read something from floppy disk
    ; BIOS should set DL to drive number
    mov [ebr_drive_number], dl
    
    mov ax, 1                   ; LBA=1, second sector from disk
    mov cl, 1                   ; 1 sector to read
    mov bx, 0x7E00              ; data should be after the bootloader (512 bytes after)
    mov si, boot_msg
    mov di, 0
    call disk_read
    call print
    cli                         ; disable interrupts, this way CPU can't get out of "halt" state
    jmp 0x0000:0x7E00


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


;
; Error handlers
;
floppy_error:
    mov si, read_failed_msg
    call print
    jmp wait_key_and_reboot

wait_key_and_reboot:
    mov ah, 0
    int 16h                     ; wait for keypress
    jmp 0FFFFh:0                ; jump to beginning of BIOS, should reboot


halt:
    hlt
    jmp halt


;
; Disk routines
;

;
; Converts an LBA address to a CHS address
; Parameters:
;   - ax: LBA address
; Returns:
;   - cx [bits 0-5]: sector number
;   - cx [bits 6-15]: cylinder
;   - dh: head
;

lba_to_chs:
    push ax
    push dx

    xor dx, dx                          ; set to 0
    div word [bdb_sectors_per_track]    ; ax = LBA / sectors_per_track ( lba / 18 ) (the integer result) (how many tracks we have passed?) 
                                        ; dx = LBA % sectors_per_track ( lba % 18 ) (the reminder) (which sector within the track are we?)
    inc dx                              ; dx = ((LBA % sectors_per_track) + 1) = sector we must read
                                        ; note that BIOS expects sectors numbered starting from 1, not 0. So we inc it.
    mov cx, dx                          ; store the sector
    xor dx, dx                          ; set to 0              
    div word [bdb_heads]                ; ax = (LBA / sectors_per_track) / heads = cylinder (based on the tracks, which cylinder are we now?)
                                        ; dx = (LBA % sectors_per_track) / heads = head      (and which head are we located?)
    mov dh, dl                          ; dh = head
    mov ch, al                          ; ch = cylinder
    shl ah, 6
    or cl, ah                           ; put upper 2 bits of cylinder in CL
    pop ax
    mov dl, al                          ; restore DL
    pop ax
    ret


;
; Reads sectors from a disk
; Parameters:
;   - ax: LBA address
;   - cl: number of sectors to read (up to 128)
;   - dl: drive number
;   - es:bx: memory address where to store read data
;
disk_read:
    push ax             ; we will be modifying all of these
    push bx
    push cx
    push dx
    push di

    push cx             ; we need to save this for a moment
    call lba_to_chs     ; at this point, we have some things in CHS in cx and dh is the head number
    pop ax              ; the original LBA address that the previous function overwrote
                        ; AL = number of sectors to read

    mov ah, 02h
    mov di, READ_RETRIES; we will be retrying 3 times

.retry:
    pusha               ; we will be saving all registers because we dont
                        ; have any idea of what bios does when reading
    
    stc                 ; set also the carryflag because not all bios sets it
    int 13h
    jnc .done           ; if carry flag is not set, go to done

    ; if we are here is because the read failed
    dec di
    test di, di
    jnz .retry

.fail:
    ;failed too many times (more than READ_RETRIES)
    jmp floppy_error

.done:
    popa

    pop di
    pop dx
    pop cx
    pop bx
    pop ax                             ; restore registers modified
    ret

;
; Resets disk controller
; Parameters:
;   dl: drive number
;
disk_reset:
    pusha
    mov ah, 0
    stc
    int 13h
    jc floppy_error
    popa
    ret


boot_msg:           DB "Hi, I'm printing from the boot process", LINE_END,0
read_failed_msg:    DB 'Read from disk failed!', LINE_END, 0

TIMES 510-($-$$) DB 0

DW 0AA55h