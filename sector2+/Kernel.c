#include "stdio.c"
#include "Keyboard.c"
#include "IDT.c"

extern const char _hello[];

void _start() {
    setCursorPosition(cursorPositionFromCoords(0, 0));
    printString(_hello);
    printString("\n\r");
    InitializeIDT();
    mainKeyboardHandler = keyboardHandler;
    printDouble(0.8628, 3);
    return;
}