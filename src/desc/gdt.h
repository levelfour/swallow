#ifndef __GDT_H
#define __GDT_H

typedef struct {
	unsigned short	limit_low;
	unsigned short	base_low;
	unsigned char	base_mid;
	unsigned char	access_right;
	unsigned char	limit_high;
	unsigned char	base_high;
} __attribute__ ((packed)) SEGMENT_DESCRIPTOR;

typedef struct {
	unsigned short		size;
	SEGMENT_DESCRIPTOR	*base;
} __attribute__ ((packed)) GDTR;


#define GDT_BASE	0x00270000
#define GDT_NUM		3

#define	NULL_DESCRIPTOR			0
#define	CODE_DESCRIPTOR			1
#define	DATA_DESCRIPTOR			2
#define	TEMP_DESCRIPTOR			3
#define	TASK_CODE_DESCRIPTOR	3
#define	TASK_DATA_DESCRIPTOR	4
#define	KTSS_DESCRIPTOR			5

/* Null Descriptor		*/
#define	GDT_NULL_LIMIT		0x0000
#define GDT_NULL_BASE		0x00000000
#define	GDT_NULL_FLAGS		0x0000

/* Code Descriptor		*/
#define	GDT_CODE_LIMIT		0xFFFF
#define GDT_CODE_BASE		0x00000000
#define	GDT_CODE_FLAGS_BL	0x9A
#define	GDT_CODE_FLAGS_BH	0xCF
#define	GDT_CODE_FLAGS		0xCF9A

/* Data Descriptor		*/
#define	GDT_DATA_LIMIT		0xFFFF
#define GDT_DATA_BASE		0x00000000
#define	GDT_DATA_FLAGS		0xCF92
#define	GDT_DATA_FLAGS_BL	0x92
#define	GDT_DATA_FLAGS_BH	0xCF

void set_segmdesc(int segm_num, int base, unsigned int limit, unsigned short flags);
void set_segment_descriptor_table();

#endif // __GDT_H
