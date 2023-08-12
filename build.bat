%nasm% sector1/bootLoader.asm -f bin -o bin/bootLoader.bin

%nasm% sector2+/extendedProgram.asm -f elf64 -o bin/extendedProgram.o

%nasm% sector2+/Binaries.asm -f elf64 -o bin/Binaries.o

wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "sector2+/Kernel.c" -o "bin/Kernel.o"

wsl $WSLENV/x86_64-elf-ld -T"link.ld"

cd bin

copy /b bootLoader.bin + Kernel.bin bootLoader.flp

cd ..

pause