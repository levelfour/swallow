#ifndef __IDT_H
#define __IDT_H

#include "types.h"

typedef struct {
	unsigned char data[32];
	int pointer;
	bool updated;
} KEYBUF;
KEYBUF keybuf;

typedef struct {
	unsigned short	base_low;
	unsigned short	selector;
	unsigned char	reserved;
	unsigned char	flags;
	unsigned short	base_high;
} __attribute__ ((packed)) GATE_DESCRIPTOR;

typedef struct {
	unsigned short	size;
	GATE_DESCRIPTOR	*base;
} __attribute__ ((packed)) IDTR;

#define IDT_BASE	0x0026f800
#define IDT_NUM		256

#define	IDT_FLAGS_INTGATE16			0x06
#define	IDT_FLAGS_TSKGATE			0x05
#define	IDT_FLAGS_CALL_GATE			0x0C
#define	IDT_FLAGS_INTGATE32			0x0E
#define	IDT_FLAGS_TRPGATE			0x0F
#define	IDT_FLAGS_DPL_LV0			0x00
#define	IDT_FLAGS_DPL_LV1			0x20
#define	IDT_FLAGS_DPL_LV2			0x40
#define	IDT_FLAGS_DPL_LV3			0x60
#define	IDT_FLAGS_PRESENT			0x80

#define	IDT_INT_SELECTOR			CODE_DESCRIPTOR << 3

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

void set_idt(int int_num, void *interrupt_handler);
void set_gatedesc(int int_num, int base, unsigned short selector, unsigned char flags);
void set_interrupt_descriptor_table();
void init_pic();

void inthandler21(int *esp);

#endif // __IDT_H
