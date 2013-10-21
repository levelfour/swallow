.code32

.global sti, cli
.global load_gdtr, load_idtr
.global outb, inb

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
	lidt 4(%esp)
	ret

outb:
	movl 4(%esp), %edx
	movb 8(%esp), %al
	outb %al, %dx
	ret

inb:
	movl 4(%esp), %edx	# port
	xorl %eax, %eax
	inb %dx, %al
	ret


