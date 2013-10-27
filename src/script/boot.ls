OUTPUT_FORMAT("elf32-i386");
ENTRY(_start);
IPLBASE = 0x00100000;

SECTIONS {
	. = IPLBASE;
	.text		: {
		_text_start = .;
		*(.text)
		_text_end = .;
	}

	.rodata		: {
		_rodata_start = .;
		*(.rodata*)
		_rodata_end = .;
	}
		
	.data		: {
		_data_start = .;
		*(.data)
		_data_end = .;
	}

	.bss		: {
		_bss_start = .;
		*(.bss)
		_bss_end = .;
	}
}
