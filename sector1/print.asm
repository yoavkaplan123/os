printString:
    push ax
    push bx
    mov ah, 0x0e
    .PrintLoop:
        cmp [bx], byte 0
        je .Exit
        mov al, [bx]
        int 0x10
        inc bx
        jmp .PrintLoop
    .Exit:
        pop bx
        pop ax
    ret