#ifndef IDT_C
#define IDT_C

#include "Constants.h"
#include "IO.c"
#include "PrintTexst.c"

struct IDT64 {
    uint_16 offset_low;
    uint_16 segment_selector;
    uint_8 ist;
    uint_8 P_DPL_0_GateType;
    uint_16 offset_mid;
    uint_32 offset_high;
    uint_32 zero;
};

typedef struct IDT64 IDT;

extern IDT _idt[256];
extern uint_64 isr1;
extern void LoadIDT();

void InitializeIDT() {
    _idt[1].zero = 0;
    _idt[1].offset_low = (uint_16)(((uint_64)&isr1 & 0x000000000000ffff));
    _idt[1].offset_mid = (uint_16)(((uint_64)&isr1 & 0x00000000ffff0000) >> 16);
    _idt[1].offset_high = (uint_32)(((uint_64)&isr1 & 0xffffffff00000000) >> 32);
    _idt[1].ist = 0; //not useing the Interrupt Stack Table
    _idt[1].segment_selector = 0x08; // 0x08 is the code segment
    // P = 1 must be 1 | DPL = 00 kernel privilege | 0 | 
    // gate type = 1110 aka interpt gate
    _idt[1].P_DPL_0_GateType = 0x8e;
    
    remapPIC();

    outb(0x21, 0xfd);
	outb(0xa1, 0xff);
    LoadIDT();
}

void (*mainKeyboardHandler)(uint_8 scanCode);

void isr1_handler() {
    uint_8 scancode = inb(0x60);
    if (mainKeyboardHandler != NULL) {
        mainKeyboardHandler(scancode);
    }
    outb(0x20, 0x20);
	outb(0xa0, 0x20);
}

#endif