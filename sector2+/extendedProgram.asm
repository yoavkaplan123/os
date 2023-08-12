jmp EnterProtectedMode

%include "sector2+/gdt.asm"

EnterProtectedMode:
    call enableA20
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp codeseg:startProtectedMode

enableA20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

[bits 32]
%include "sector2+/CPUID.asm"
%include "sector2+/simplePaging.asm"

startProtectedMode:
    mov ax, dataseg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call DetectCPUID
    call Detect_long_mode
    call setUpIdentityPaging
    call EditGDT

    jmp codeseg:startLongMode

[bits 64]
[extern _start]

%include "sector2+/IDT.asm"
startLongMode:
    mov edi, 0xb8000
    mov rax, 0x0f200f200f200f20
    mov ecx, 500
    rep stosq

    call _start

    jmp $