#include "interrupt.h"
#include "asm_func.h"

KEYBUF keybuf;

const char keytable[0x54] =
	"\0\0001234567890-^\016\0"
	"qwertyuiop@[\0\0"
	"asdfghjkl;:\0\0]"
	"zxcvbnm,./\0*\0 "
	"\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"789-456+1230.";

void init_pic() {
	outb(PIC0_IMR, 0xff);	// すべての割り込みを受け付けない
	outb(PIC1_IMR, 0xff);	// すべての割り込みを受け付けない

	outb(PIC0_ICW1, 0x11);	// エッジトリガモード
	outb(PIC0_ICW2, 0x20);	// IRQ0-7はINT20-27で受ける	
	outb(PIC0_ICW3, 1 << 2);	// PIC1はIRQ2にて接続
	outb(PIC0_ICW4, 0x01);	// ノンバッファモード

	outb(PIC1_ICW1, 0x11);	// エッジトリガモード
	outb(PIC1_ICW2, 0x28);	// IRQ8-15はINT28-2fで受ける
	outb(PIC1_ICW3, 2);		// PIC1はIRQ2にて接続
	outb(PIC1_ICW4, 0x01);	// ノンバッファモード

	outb(PIC0_IMR, 0xfb);	// PIC1以外はすべて割り込み禁止
	outb(PIC1_IMR, 0xff);	// すべての割り込みを受け付けない
}

void init_interrupt() {
	sti();					// 割り込み許可
	outb(PIC0_IMR, 0xfd);	// PIC1とキーボードの割り込み許可

	keybuf.read		= 0;
	keybuf.write	= 0;
	keybuf.length	= 0;
}

void inthandler21(int *esp) {
	unsigned char data = 0;

	outb(PIC0_OCW2, 0x61);	// 割り込み完了通知
	data = inb(PORT_KEYDAT);
	
	if(keybuf.length < KEYBUF_SIZE) {
		if(keybuf.write >= KEYBUF_SIZE) keybuf.write = 0;
		keybuf.data[keybuf.write++] = data;
		keybuf.length++;
	}
}

bool is_keyupdated() {
	return (keybuf.length > 0);
}

unsigned char get_keycode() {
	if(!is_keyupdated() || keybuf.length <= 0) return 0;
	if(keybuf.read >= KEYBUF_SIZE) keybuf.read = 0;
	keybuf.length--;
	return keybuf.data[keybuf.read++];
}
