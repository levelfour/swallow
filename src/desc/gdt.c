#include "asm_func.h"
#include "gdt.h"

void set_segment_descriptor_table() {
	set_segmdesc(NULL_DESCRIPTOR, GDT_NULL_BASE, GDT_NULL_LIMIT, GDT_NULL_FLAGS);
	set_segmdesc(CODE_DESCRIPTOR, GDT_CODE_BASE, GDT_CODE_LIMIT, GDT_CODE_FLAGS);
	set_segmdesc(DATA_DESCRIPTOR, GDT_DATA_BASE, GDT_DATA_LIMIT, GDT_DATA_FLAGS);

	GDTR gdtr;
	gdtr.size	= GDT_NUM * sizeof(SEGMENT_DESCRIPTOR);
	gdtr.base	= (SEGMENT_DESCRIPTOR*)GDT_BASE;
//	load_gdtr(gdtr.size, gdtr.base);
	load_gdtr(gdtr);
}

void set_segmdesc(int segm_num, int base, unsigned int limit, unsigned short flags) {
	SEGMENT_DESCRIPTOR *gdt = (SEGMENT_DESCRIPTOR *)GDT_BASE;

	if(limit > 0xfffff) {
		flags |= 0x8000; // G_bit = 1
		limit /= 0x1000;
	}

	gdt[segm_num].limit_low		= limit & 0xFFFF;
	gdt[segm_num].base_low		= (unsigned short)(base & 0x0000FFFF);
	gdt[segm_num].base_mid		= (unsigned char)((base & 0x00FF0000) >> 16);
	gdt[segm_num].access_right	= flags & 0xFF;
	gdt[segm_num].limit_high	= ((limit >> 16) & 0x0F) | ((flags >> 8) & 0xF0);
	gdt[segm_num].base_high		= (unsigned char)((base & 0xFF000000) >> 24);
}

