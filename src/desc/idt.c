#include "idt.h"
#include "stdio.h"
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

	keybuf.pointer = 0;
	keybuf.updated = false;

	IDTR idtr;
	idtr.size	= IDT_NUM * sizeof(GATE_DESCRIPTOR);
	idtr.base	= (GATE_DESCRIPTOR*)IDT_BASE;
	load_idtr(idtr);
}

void init_pic() {
	out(PIC0_IMR, 0xff);	// すべての割り込みを受け付けない
	out(PIC1_IMR, 0xff);	// すべての割り込みを受け付けない

	out(PIC0_ICW1, 0x11);	// エッジトリガモード
	out(PIC0_ICW2, 0x20);	// IRQ0-7はINT20-27で受ける	
	out(PIC0_ICW3, 1 << 2);	// PIC1はIRQ2にて接続
	out(PIC0_ICW4, 0x01);	// ノンバッファモード

	out(PIC1_ICW1, 0x11);	// エッジトリガモード
	out(PIC1_ICW2, 0x28);	// IRQ8-15はINT28-2fで受ける
	out(PIC1_ICW3, 2);		// PIC1はIRQ2にて接続
	out(PIC1_ICW4, 0x01);	// ノンバッファモード

	out(PIC0_IMR, 0xfb);	// PIC1以外はすべて割り込み禁止
	out(PIC1_IMR, 0xff);	// すべての割り込みを受け付けない
}

void inthandler21(int *esp) {
	out(PIC0_OCW2, 0x61);	// 割り込み完了通知

	unsigned char data = 0;
	data = in(PORT_KEYDAT);
	if(keybuf.pointer == 31) keybuf.pointer = 0;
	keybuf.data[keybuf.pointer] = data;
	keybuf.updated = true;
}
