#include "multiboot.h"
#include "stdio.h"
#include "video.h"
#include "gdt.h"
#include "idt.h"
#include "asm_func.h"

char message[] = 
	"********** Welcome to myOS **********\n\n"
	" this OS is under construction.\n\n"
	"*************************************\n\n";

void _kernel_entry(uint magic, MULTIBOOT_INFO *info) {
	init_screen();
	printf(message);
	set_cursor(CURSOR_DEFAULT, CURSOR_DEFAULT, COLOR_LIGHT_GREEN, CURSOR_DEFAULT);

	set_segment_descriptor_table();
	set_interrupt_descriptor_table();
	init_pic();

	__asm__ __volatile__ ("sti");
	out(PIC0_IMR, 0xfd);

	printf(">>> ");
	while(1) {
		if(keybuf.updated = true) {
			printf("%x ", keybuf.data[keybuf.pointer]);
			keybuf.updated = false;
		}
		asm("hlt");
	}
}
