#ifndef __ASM_FUNC_H
#define __ASM_FUNC_H

#include "gdt.h"
#include "idt.h"

void load_gdtr(GDTR gdtr);
void load_idtr(IDTR idtr);
//void load_idtr(int size, void *base);
void out(unsigned short address, unsigned char value);
unsigned char in(unsigned short address);

#endif // __ASM_FUNC_H
