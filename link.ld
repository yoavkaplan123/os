OUTPUT_FORMAT(binary)

ENTRY(_start)

INPUT (
    bin/extendedProgram.o
    bin/Kernel.o
    bin/Binaries.o
)

OUTPUT (
    bin/Kernel.bin
)

SECTIONS {
    . = 0x8000;
    
    .text : ALIGN(0x1000) {
        *(.text)
    }

    .idt BLOCK(0x1000) : ALIGN(0x1000) {
        _idt = .;
        . = . + 0x1000;
    }

    .data : ALIGN(0x1000) {
        *(.data)
    }

    .rodata : ALIGN(0x1000) {
        *(.rodata)
    }

    .bss : ALIGN(0x1000) {
        *(.bss)
    }
}