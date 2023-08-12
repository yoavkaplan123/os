[org 0x7c00]

mov [bootDisk], dl

mov bp, 0x7c00
mov sp, bp

call ReadDisk

jmp PROGRAM_SPACE

%include "sector1/print.asm"
%include "sector1/diskRead.asm"

times 510-($-$$) db 0

dw 0xaa55
