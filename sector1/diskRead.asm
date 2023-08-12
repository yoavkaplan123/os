PROGRAM_SPACE equ  0x8000

ReadDisk:
    mov ah, 0x02
    mov bx, PROGRAM_SPACE
    mov al, 32             ; number of sectors (sector size 512) to read from the disk
    mov dl, [bootDisk]
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    
    int 0x13

    jc DiskReadFailed
    ret

bootDisk:
    db 0

diskReadErrorMas:
    db 'disk read failed', 0

DiskReadFailed:
    mov bx, diskReadErrorMas
    call printString
    jmp $