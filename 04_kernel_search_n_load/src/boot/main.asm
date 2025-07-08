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
    mov si, boot_msg
    call print

    ; 4 segments
    ; reserved segment: 1 sector
    ; FAT: 2 tables * 9 sectors per FAT = 18 sectors
    ; Root directory:
    ; Data
    ; We need to  get the LBA of the root dir

    ; 1st we count how many sectors up to the root dir
    mov ax, [bdb_sectors_per_fat]               ; sectors per fat * fat count
    mov bl, [bdb_fat_count]
    xor dh, dh
    mul bx
    add ax, [bdb_number_of_reserved_sectors]    ; then add the num of reserved sectors
    push ax

    ; 2nd now we need to get the size of the root dir in sectors
    ; for this, we calculate how many dir entries are there
    ; and then multiply by how many bytes they use
    ; and finally divide those bytes into how many bytes a setor takes
    mov ax, [bdb_dir_entries_count]
    shl ax, 5                                   ; ax * (2^5) = ax * 32 = ax * dir entry size
    xor dx, dx

    div word [bdb_bytes_per_sector]             ;(32*num of entres) / bytes per sector
                                                ;this will give us the number of sectors for the table
    
    test dx, dx                                 ; check for the reminder
    jz rootDirAfter                             ; continue if no reminder                
    inc ax                                      ; this is to round up (a reminder means the whole sum uses up to quocient + 1 sectors)


; Now we read the whole root directory and put it into memory
rootDirAfter:
    mov cl, al                                  ; number of sectors to read (the size of the root directory)
    pop ax                                      ; LBA of the root directory
    mov dl, [ebr_drive_number]                  ; The drive we are reading from
    mov bx, buffer                              ; The place where we are going to put all of our data
    call disk_read

    xor bx, bx                                  ; set bx to 0 (this will be used while iterating in the kernel search)
    mov di, buffer


searchKernel:
    mov si, kernel_file_name                    ; get the file name
    mov cx, 11                                  ; the size of the name
    push di                                     ; store the buffer in the stack because we dont know
                                                ; what the heck will the comparidon do with our registries
    REPE CMPSB                                  ; https://faydoc.tripod.com/cpu/cmpsb.htm
    
    pop di                                      ; populate di with the buffer
    je foundKernel                              ; we found it

    ; if we reach here, we loop
    add di, 32                                  ; we add 32 to the start of our buffer (to jump to the next table entry)
    inc bx                                      ; because we are counting each table entry we checked
    cmp bx, [bdb_dir_entries_count]             ; did we reach the end of the table?
    jl searchKernel

    jmp kernelNotFound

kernelNotFound:
    mov si, kernel_not_found
    call print
    hlt
    jmp halt

foundKernel:                                    ; 1st load the file allocation table into memory
    mov ax, [di+26]                            ; offset 26 of each table entry stores the 1st cluster number where the file starts
    mov [kernel_cluster], ax                    ; storing where the kernel is located into our variable
    mov ax, [bdb_number_of_reserved_sectors]    
    mov bx, buffer      
    mov cl, [bdb_sectors_per_fat]
    mov dl, [ebr_drive_number]

    call disk_read

    ; now we set up where we are going to load the kernel
    mov bx, kernel_load_segment 
    mov es, bx
    mov bx, kernel_load_offset

loadKernelLoop:
    mov ax, [kernel_cluster]
    add ax, 31                                  ; LBA = (cluster_number - 2) * sectors_per_cluster + data_region_start
                                                ; -2 because the data sectors begin at cluster at cluster 2

    mov cl, 1                                   ; read one sector at a time
    mov dl, [ebr_drive_number]                  ; the drive we are reading from
    call disk_read

    add bx, [bdb_bytes_per_sector]              ; advance from kernel load offset to load offset + 1 sector
    mov ax, [kernel_cluster]                    ; now we advance 1.5 sectors, because fat12 is strangely packed
    mov cx, 3                                   ; multiplying by 3 and dividing by 2 is just that
    mul cx
    mov cx, 2
    div cx

    mov si, buffer
    add si, ax
    mov ax, [ds:si]                             ; the offset is the same but si is advanced

    or dx, dx
    jz even

odd:
    SHR ax, 4                                   ; if odd, we need to get the upper 12 bits
    jmp nextclusterAfter

even:
    and ax, 0x0FFF                              ; will give you the next 12 bits

nextclusterAfter:
    cmp ax, 0x0FF8                              ; from the fat spec, if that value is 0x0FF8 we ended
    jae readFinish

    mov [kernel_cluster], ax
    jmp loadKernelLoop

readFinish:
    mov dl, [ebr_drive_number]
    mov ax, kernel_load_segment
    mov ds, ax
    mov es, ax

    JMP kernel_load_segment:kernel_load_offset   ; JUMP to our target
    hlt

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


boot_msg:               DB "Hi, I'm printing from the boot process", LINE_END,0
read_failed_msg:        DB 'Read from disk failed!', LINE_END, 0
kernel_file_name:       DB 'KERNEL  BIN'
kernel_not_found:       DB 'KERNEL.BIN not found!'
kernel_cluster:         DW 0
kernel_load_segment:    EQU 0x2000
kernel_load_offset:     EQU 0


TIMES 510-($-$$) DB 0
DW 0AA55h

buffer: