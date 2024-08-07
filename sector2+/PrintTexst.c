#ifndef PRINT_TEXST
#define PRINT_TEXST

#include "IO.c"
#include "ColorCode.h"

#define VGA_MEMORY (uint_8 *)0xb8000
#define VGA_WIDTH 80
#define VGA_LENGTH 25
#define MAX_POSE 2000

void clearScreen() {
    uint_64 clearColor = BACKGROUND_BLACK;
    uint_64 value = 0;
    value += clearColor << 8;
    value += clearColor << 24;
    value += clearColor << 40;
    value += clearColor << 56;
    for (uint_64 *i = (uint_64*)VGA_MEMORY;
     i < (uint_64*)(VGA_MEMORY + 4000); i++) {
        *i = value;
    }
}

void setCursorPosition(uint_16 position) {
    position = position >= 2000 ? 1999 : position;
    position = position < 0 ? 0 : position;
    outb(0x3d4, 0x0f);
    outb(0x3d5, (uint_8)(position & 0xff));
    outb(0x3d4, 0x0e);
    outb(0x3d5, (uint_8)((position >> 8) & 0xff));
}

uint_16 getCursorPosition(void) {
    uint_16 pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint_16)inb(0x3D5)) << 8;
    return pos;
}

uint_16 cursorPositionFromCoords(uint_16 x, uint_16 y) {
    x = x >= VGA_WIDTH ? VGA_WIDTH - 1 : x;
    y = y >= VGA_LENGTH ? VGA_LENGTH - 1 : y;
    return y * VGA_WIDTH + x;
}

void printColorString(const char *str, 
    uint_8 colorCode) {
    uint_8 *str_ptr = (uint_8 *)str;
    uint_16 index = getCursorPosition();
    for (; *str_ptr != 0; str_ptr++) {
        switch (*str_ptr) {
            case 10:
                index += VGA_WIDTH;
                break;
            case 13:
                index -= index % VGA_WIDTH;
                break;
            default:
                *(VGA_MEMORY + index * 2) = *str_ptr;
                *(VGA_MEMORY + index * 2 + 1) = colorCode;
                index++;
        } 
    }
    setCursorPosition(index);
}

void printString(const char *str) {
    printColorString(str, BACKGROUND_BLACK | FOREGROUND_GREEN);
}

void printChar(char chr) {
    char temp[2];
    temp[0] = chr;
    temp[1] = 0;
    printString(temp);
}

uint_8 IntLen(uint_64 value) {
    uint_8 i = 0;
    for(; value; value /= 10, i++);
    return i;
}

uint_8 strlen(char *str) {
    uint_8 i = 0;
    for(; *str; i++, str++);
    return i;
}

void HexToString(const void *value, uint_8 size, char *output) {
    uint_8 *ptr, temp, i;
    const uint_8 length = size * 2 - 1;
    for (i = 0; i < size; i++) {
        ptr = ((uint_8*)value + i); 
        temp = (*ptr & 0xf0) >> 4;
        output[length - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
        temp = *ptr & 0x0f;
        output[length - (i * 2)] = temp + (temp > 9 ? 55 : 48);
    }
    output[length + 1] = 0;
}

void IntToString(uint_64 value, char *output) {
    uint_8 i = 0, length = IntLen(value) - 1;
    for(; value; value /= 10, i++) {
        output[length - i] = value % 10 + '0';
    }
    output[i + 1] = 0;
}

void printHex(const void *value, uint_8 size) {
    char str[size], *ptr;
    ptr = str;
    HexToString(value, size, str);
    //clear zeros at the begning
    for (; !((*ptr) - '0'); ptr++);
    printString(ptr);
}

void printInt(uint_64 value) {
    char str[IntLen(value)];
    IntToString(value, str);
    printString(str);
}

#endif