#ifndef IO 
#define IO

#include "Constants.c"

#define PIC_MASTER_COMMAND 0x20
#define PIC_MASTER_DTATA 0x21
#define PIC_SALVE_COMMAND 0xA0
#define PIC_SLAVE_DATA 0xA1

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01


void outb(uint_16 port, uint_8 value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

uint_8 inb(uint_16 port) {
    uint_8 ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void remapPIC() {
    uint_8 maskMasterPIC, maskSlavePIC;

    maskMasterPIC = inb(PIC_MASTER_DTATA);
    maskSlavePIC = inb(PIC_SLAVE_DATA);

    outb(PIC_MASTER_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC_SALVE_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC_MASTER_DTATA, 0);
    outb(PIC_SLAVE_DATA, 8);
    outb(PIC_MASTER_DTATA, 4);
    outb(PIC_SLAVE_DATA, 2);
    outb(PIC_MASTER_DTATA, ICW4_8086);
    outb(PIC_SLAVE_DATA, ICW4_8086);

    outb(PIC_MASTER_DTATA, maskMasterPIC);
    outb(PIC_SLAVE_DATA, maskSlavePIC);
}

#endif