#include "multiboot.h"
#include "stdio.h"
#include "video.h"
#include "gdt.h"
#include "idt.h"
#include "asm_func.h"
#include "interrupt.h"

char message[] = 
	"********** Welcome to myOS **********\n\n"
	" this OS is under construction.\n\n"
	"************* Boot Info *************\n";

void _kernel_entry(uint magic, MULTIBOOT_INFO *info) {
	init_screen();
	if(magic != MULTIBOOT_CHECK_MAGIC) {
		printf("Error: invalid magic '%x'\n", magic);
		return;
	}

	printf(message);
	if(CHECK_MBH_FLAG(info->flags, 0)) {
		int memory_size = (info->mem_lower + info->mem_upper + 1024) / 1024;
		printf(" Total Memory: %d[MB]\n", memory_size);
	}
	if(CHECK_MBH_FLAG(info->flags, 1))
		printf(" Boot Device : 0x%x\n", info->boot_device);
	if(CHECK_MBH_FLAG(info->flags, 2))
		printf(" cmdline = \"%s\"\n", info->cmdline);
	printf("*************************************\n\n");

	set_segment_descriptor_table();
	set_interrupt_descriptor_table();
	init_pic();
	init_interrupt();

	printf(">>> ");
	while(1) {
		if(is_keyupdated()) {
			cli();
			unsigned char c = get_keycode();
			if(c < 0x80) printf("%c", keytable[c]);
			if(c == 0x1c) printf("\n>>> ");
			sti();
		}
		refresh();
		asm("hlt");
	}
}
