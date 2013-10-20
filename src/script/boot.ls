OUTPUT_FORMAT("elf32-i386");
ENTRY(_start);
IPLBASE = 0x00100000;

SECTIONS {
	. = IPLBASE;
	.text		: {*(.text)}
	.rodata		: {*(.rodata*)}
	.data		: {*(.data)}
	.bss		: {*(.bss)}
}
