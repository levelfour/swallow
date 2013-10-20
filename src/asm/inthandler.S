.code32

.global int21
.extern inthandler21

.extern printf
###############################
### Interrupt Handler
###############################
int21:
	pushw %es
	pushw %ds
	pusha
	movl %esp, %eax
	pushl %eax
	movw %ss, %ax
	movw %ax, %ds
	movw %ax, %es
	call inthandler21
	popl %eax
	popa
	popw %ds
	popw %es
	iret
