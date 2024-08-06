#ifndef KEYBOARD
#define KEYBOARD
#include "KBScanCodeset.h"

void standartSpecialCharHandler(uint_8 scancode, bool *shiftPrest) {
    switch (scancode) {
    case 0x8e: // backSpace
        setCursorPosition(getCursorPosition() - 1);
        printChar(' ');
        setCursorPosition(getCursorPosition() - 1);
        break;
    case 0x2a: // left shift
    case 0x36: // right shift
        *shiftPrest = TRUE;
        break;
    case 0xaa: // left shift relesed
    case 0xb6: // right shift relesed
        *shiftPrest = FALSE;
        break;
    case 0x9c: // Enter
        printString("\n\r");
        break;
    default:
        break;
    }
}

void standartLetterHandler(uint_8 scancode, bool shiftPrest) {
    if (scancode > 57) {
        return;
    }
    char chr = ScanCodeLookupTable[scancode];
    if (chr != 0) {
        if (shiftPrest && chr > 60 && chr < 123) {
            printChar(chr - ASCIILowerUpperConverter);
        }
        else {
            printChar(chr);
        }
    }
}

void standartkeyboardHandler(uint_8 scancode) {
    static bool shiftPrest = FALSE;
    standartSpecialCharHandler(scancode, &shiftPrest);
    standartLetterHandler(scancode, shiftPrest);
}

void keyboardHandler0xE0(uint_8 scancode) {
    switch (scancode) {
    case 0x50: // up
        setCursorPosition(getCursorPosition() + VGA_WIDTH);
        break;
    case 0x48: // down
        setCursorPosition(getCursorPosition() - VGA_WIDTH);
        break;
    case 0x4b: // left
        setCursorPosition(getCursorPosition() - 1);
        break;
    case 0x4d: // right
        setCursorPosition(getCursorPosition() + 1);
        break;
    default:
        break;
    }
}

void keyboardHandler(uint_8 scancode) {
    static uint_8 lastScancode = 0;
    switch (lastScancode) {
    case 0xe0:
        keyboardHandler0xE0(scancode);
        break;
    default:
        standartkeyboardHandler(scancode);
        break;
    }
    lastScancode = scancode;
}

#endif