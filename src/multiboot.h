/******************************
 * File: multiboot.h
 * Description: definition of multiboot header
******************************/

#ifndef __MULTIBOOT_H

#define KERNEL_LOAD_ADDRESS				0x00100000

#define MBH_FLAG_PAGE_ALIGN				0x00000001
#define MBH_FLAG_MEMORY_INFO			0x00000002
#define MBH_FLAG_VIDEO_MODE				0x00000004
#define MBH_FLAG_ENABLE_ADDR			0x00010000

#define MULTIBOOT_HEADER_MAGIC			0x1BADB002
#define MULTIBOOT_CHECK_MAGIC			0x2BADB002
#define MULTIBOOT_HEADER_FLAGS			(MBH_FLAG_PAGE_ALIGN | MBH_FLAG_MEMORY_INFO)
#define MULTIBOOT_HEADER_CHECKSUM		-(MULTIBOOT_HEADER_MAGIC+MULTIBOOT_HEADER_FLAGS)
#define KERNEL_STACK_SIZE				0x00100000

#define MULTIBOOT_HEADER_MODE_TYPE		0x00000001	// text mode
#define MULTIBOOT_HEADER_WIDTH			0x00000050
#define MULTIBOOT_HEADER_HEIGHT			0x00000028
#define MULTIBOOT_HEADER_DEPTH			0x00000000

#endif // __MULTIBOOT_H

#ifndef __MULTIBOOT_S
#ifndef __MULTIBOOT_HEADER

#include "types.h"

#define CHECK_MBH_FLAG(flags, bit)	((flags) & (1 << bit))

// multiboot header
typedef struct {
	uint magic;
	uint flags;
	uint checksum;
	// address field
	uint header_addr;
	uint load_addr;
	uint load_end_addr;
	uint bss_addr;
	uint entry_addr;
	// graphics field
	uint mode_type;
	uint width;
	uint height;
	uint depth;
} MULTIBOOT_HEADER;

// multiboot info
typedef struct {
	uint flags;
	// available memory from BIOS
	uint mem_lower;
	uint mem_upper;
	uint boot_device;
	uint cmdline;
	// Boot-Module list
	uint mods_count;
	uint mods_addr;

	uint syms1;
	uint syms2;
	uint syms3;

	// memory mapping buffer
	uint mmap_length;
	uint mmap_addr;
	// drive info buffer
	uint drives_length;
	uint drives_addr;
	// ROM configuration table
	uint config_table;
	// boot loader name
	uint boot_loader_name;
	// video
	uint vbe_control_info;
	uint vbe_mode_info;
	uint vbe_mode;
	uint vbe_interface_seg;
	uint vbe_interface_off;
	uint vbe_interface_len;
} MULTIBOOT_INFO;

#endif // __MULTIBOOT_HEADER
#endif // __MULTIBOOT_S
