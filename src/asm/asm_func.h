#ifndef __ASM_FUNC_H
#define __ASM_FUNC_H

#include "gdt.h"
#include "idt.h"

void sti();
void cli();
void load_gdtr(GDTR gdtr);
void load_idtr(IDTR idtr);
void outb(unsigned short address, unsigned char value);
unsigned char inb(unsigned short address);

#endif // __ASM_FUNC_H
