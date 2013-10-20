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
	"*************************************\n\n";

void _kernel_entry(uint magic, MULTIBOOT_INFO *info) {
	init_screen();
	set_cursor(CURSOR_DEFAULT, CURSOR_DEFAULT, COLOR_LIGHT_CYAN, CURSOR_DEFAULT);
	printf(message);

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
		asm("hlt");
	}
}
