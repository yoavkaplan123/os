#include "PrintTexst.c"
#include "IDT.c"

extern const char _Test[];

void _start() {
    setCursorPosition(cursorPositionFromCoords(0,0));
    printString(_Test);
    printString("\n\r");
    InitializeIDT();
    return;
}