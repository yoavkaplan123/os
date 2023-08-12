gdt_start:
    gdt_nulldesc:
        dd 0
	    dd 0
    gdt_codedesc:
        dw 0xFFFF       ; limit (size of the segment)
        dw 0x0000       ; base (low)
        db 0x00         ; base (medium)
        db 10011010b    ; first bit present (the segment is being used)
                        ; the second and third bit privilege
                        ; fourth bit type (the segment is the code segment)
                        ; fifth bit excutable bit
                        ; sixth bit conforming bit
                        ; seventh read/write bit
                        ; eighth bit accessed bit
        db 11001111b    ; first bit ganularity (1 = the limit is in 4kb bloks)
                        ; second bit size (0 = 16 bits, 1 = 32 bits)
                        ; third and fourth null
                        ; the rest of the byte limit (upper)
        db 0x00         ; high portion of the base
    gdt_datadesc:
        dw 0xFFFF       ; limit (size of the segment)
        dw 0x0000       ; base (location)
        db 0x00         ; base (location) extention
        db 10010010b    ; first bit present (the segment is being used)
                        ; the second and third bit privilege (00 = kenal privilege)
                        ; fourth bit type (the segment is the code segment)
                        ; fifth bit excutable bit
                        ; sixth bit conforming bit
                        ; seventh read/write bit
                        ; eighth bit accessed bit
        db 11001111b    ; first bit ganularity (1 = the limit is in 4kb bloks)
                        ; second bit size (0 = 16 bits, 1 = 32 bits)
                        ; third and fourth null
                        ; the rest of the byte limit extention
        db 0x00         ; high portion of the base
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1    ; size
    dd gdt_start                  ; start

codeseg equ gdt_codedesc - gdt_start
dataseg equ gdt_datadesc - gdt_start

[bits 32]

EditGDT:
    mov [gdt_codedesc + 6], byte 10101111b
    mov [gdt_datadesc + 6], byte 10101111b
    ret 

[bits 16]