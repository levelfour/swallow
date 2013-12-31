#include "multiboot.h"
#include "stdio.h"
#include "video.h"
#include "gdt.h"
#include "idt.h"
#include "asm_func.h"
#include "interrupt.h"
#include "memory.h"

void print_loadinfo(uint magic, MULTIBOOT_INFO *info);

void _kernel_entry(uint magic, MULTIBOOT_INFO *info) {
	init_screen();
	print_loadinfo(magic, info);
	set_segment_descriptor_table();
	set_interrupt_descriptor_table();
	init_pic();
	init_interrupt();

	bool is_extended = false;
	printf(">>> ");
	while(1) {
		if(is_keyupdated()) {
			cli();
			unsigned char c = get_keycode();
			if(is_extended) {
				is_extended = false;
				continue;
			}
			if(c < 0x80) printf("%c", keytable[c]);
			if(c == 0x1c) printf(">>> ");
			if(c == 0xe0) {
				is_extended = true;
				continue;
			}
			sti();
		}
		refresh();
	}
}

char message[] = 
	"********** Welcome to myOS **********\n\n"
	" this OS is under construction.\n\n"
	"************* Boot Info *************\n";

void print_loadinfo(uint magic, MULTIBOOT_INFO *info) {
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
	printf(" kernel size = 0x%x\n", get_kernel_size());
	printf("*************************************\n\n");
}
