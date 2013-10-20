#include "idt.h"
#include "asm_func.h"
#include "inthandler.h"

void set_idt(int int_num, void *interrupt_handler) {
	set_gatedesc(
		int_num,
		(int)interrupt_handler,
		IDT_INT_SELECTOR,
		IDT_FLAGS_PRESENT | IDT_FLAGS_INTGATE32 | IDT_FLAGS_DPL_LV0);
}

void set_gatedesc(int int_num, int base, unsigned short selector, unsigned char flags) {
	GATE_DESCRIPTOR *idt = (GATE_DESCRIPTOR *)IDT_BASE;

	idt[int_num].base_low	= (unsigned short)(base & 0x0000FFFF);
	idt[int_num].selector	= selector;
	idt[int_num].reserved	= 0x00;
	idt[int_num].flags		= flags;
	idt[int_num].base_high	= (unsigned short)((base & 0xFFFF0000) >> 16);
}

void set_interrupt_descriptor_table() {
	set_idt(0x21, int21);

	IDTR idtr;
	idtr.size	= IDT_NUM * sizeof(GATE_DESCRIPTOR);
	idtr.base	= (GATE_DESCRIPTOR*)IDT_BASE;
	load_idtr(idtr);
}

