#define __MULTIBOOT_S 1
#include "multiboot.h"

.text
.code32

.extern _kernel_entry
.global _start

_start:
	jmp entry
	.align 4
	# multiboot header
	.long MULTIBOOT_HEADER_MAGIC
	.long MULTIBOOT_HEADER_FLAGS
	.long MULTIBOOT_HEADER_CHECKSUM

entry:
	# reset eflags
	pushl $0x0
	popf

	push %ebx		# push MULTIBOOT_HEADER_MAGIC
	push %eax		# push multiboot info structure pointer

	call _kernel_entry

loop:
	hlt
	jmp loop
