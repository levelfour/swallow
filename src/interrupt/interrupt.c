#include "interrupt.h"
#include "asm_func.h"

KEYBUF keybuf;

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

void init_interrupt() {
	sti();					// 割り込み許可
	out(PIC0_IMR, 0xfd);	// PIC1とキーボードの割り込み許可

	keybuf.pointer = 0;
	keybuf.updated = false;
}

void inthandler21(int *esp) {
	out(PIC0_OCW2, 0x61);	// 割り込み完了通知

	unsigned char data = 0;
	data = in(PORT_KEYDAT);
	if(keybuf.pointer == 31) keybuf.pointer = 0;
	keybuf.data[keybuf.pointer] = data;
	keybuf.updated = true;
}

bool is_keyupdated() {
	return keybuf.updated;
}

unsigned char get_keycode() {
	keybuf.updated = false;
	return keybuf.data[keybuf.pointer];
}
