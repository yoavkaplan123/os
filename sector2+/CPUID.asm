DetectCPUID:
    pushfd
    pop eax

    mov ecx, eax

    xor eax, 1 << 21

    push eax
    popfd

    pushfd
    pop eax

    push ecx
    popfd

    xor eax, ecx
    jz _htl
    ret

Detect_long_mode:
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz _htl
    ret

_htl:
    hlt