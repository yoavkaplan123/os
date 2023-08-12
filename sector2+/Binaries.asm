%macro IncBin 2
section .rodata
    global %1
    %1:
        incbin %2
        db 0
        %1_sizee: dq %1_sizee - %1
%endmacro

IncBin _Test, "sector2+/test.txt"
