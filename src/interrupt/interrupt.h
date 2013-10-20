#ifndef __INTERRUPT_H
#define __INTERRUPT_H

#include "types.h"

#define KEYBUF_SIZE		32

typedef struct {
	unsigned char data[KEYBUF_SIZE];
	int read, write; // pointer
	int length;
} KEYBUF;

// number of ports
#define PIC0_ICW1		0x0020
#define PIC0_OCW2		0x0020
#define PIC0_IMR		0x0021
#define PIC0_ICW2		0x0021
#define PIC0_ICW3		0x0021
#define PIC0_ICW4		0x0021
#define PIC1_ICW1		0x00a0
#define PIC1_OCW2		0x00a0
#define PIC1_IMR		0x00a1
#define PIC1_ICW2		0x00a1
#define PIC1_ICW3		0x00a1
#define PIC1_ICW4		0x00a1


#define PORT_KEYDAT		0x0060
#define PORT_KEYSTA		0x0064
#define PORT_KEYCMD		0x0064

// データ定数
#define KEYSTA_SEND_NOTREADY	0x02
#define KEYCMD_WRITE_MODE		0x60

void init_pic();
void init_interrupt();
void inthandler21(int *esp);
bool is_keyupdated();
unsigned char get_keycode();

const char keytable[0x54];

#endif // __INTERRUPT_H
