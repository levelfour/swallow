#ifndef __IDT_H
#define __IDT_H

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

void set_idt(int int_num, void *interrupt_handler);
void set_gatedesc(int int_num, int base, unsigned short selector, unsigned char flags);
void set_interrupt_descriptor_table();

#endif // __IDT_H
