.code32

.global sti, cli
.global load_gdtr, load_idtr
.global out, in

.text
sti:
	sti
	ret

cli:
	cli
	ret

load_gdtr:
	lgdt 4(%esp)
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	ljmpl $0x08, $_flush_seg
_flush_seg:
	ret

load_idtr:
#	movw 4(%esp), %ax
#	movw %ax, 6(%esp)
#	lidt 6(%esp)
	lidt 4(%esp)
	ret

out:
	movl 4(%esp), %edx
	movb 8(%esp), %al
	outb %al, %dx
	ret

in:
	movl 4(%esp), %edx	# port
	xorl %eax, %eax
	inb %dx, %al
	ret


