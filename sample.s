	.file	"test.c"
	.globl	from
	.bss
	.align 8
	.type	from, @object
	.size	from, 8
from:
	.zero	8
	.section	.rodata
.LC0:
	.string "%ld"
.LC1:
	.string "%s"
.LC2:
	.string	"\n"
.LC3:
	.string	"\n"
.LC4:
	.string	"\n"
.LC5:
	.string	"\n"
.LC6:
	.string	"how are you"
.LC7:
	.string	"\n"
.LC8:
	.string	"dogs"
.LC9:
	.string	"\n"
.LC10:
	.string	"\n"
.LC11:
	.string	"hello, world!"
.LC12:
	.string	"\n"
.LC13:
	.string	"\n"
.LC14:
	.string	"\n"
.LC15:
	.string	"\n"
.LC16:
	.string	"\n"
.LC17:
	.string	"hi"
.LC18:
	.string	"\n"
.LC19:
	.string	"theres"
.LC20:
	.string	"\n"
.LC21:
	.string	"a"
.LC22:
	.string	"\n"
.LC23:
	.string	"aa"
.LC24:
	.string	"\n"
.LC25:
	.string	"aaa"
.LC26:
	.string	"\n"
.LC27:
	.string	"aaaa"
.LC28:
	.string	"\n"
.LC29:
	.string	"aaaaa"
.LC30:
	.string	"\n"
.LC31:
	.string	"aaaaaa"
.LC32:
	.string	"\n"
.LC33:
	.string	"aaaaaaa"
.LC34:
	.string	"\n"
.LC35:
	.string	"aaaaaaaa"
.LC36:
	.string	"\n"
.LC37:
	.string	"aaaaaaaaa"
.LC38:
	.string	"\n"
.LC39:
	.string	"aaaaaaaaaa"
.LC40:
	.string	"\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	 $32, %rsp
	subq	 $8, %rsp
	movl	$10, %eax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, -8(%rbp)
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	subq	 $8, %rsp
	movl	$6, %eax
	movq	%rax, (%rsp)
	subq	 $8, %rsp
	movl	$5, %eax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	imulq	 (%rsp), %rax
	movq	%rax, (%rsp)
	subq	 $8, %rsp
	movl	$4, %eax
	movq	%rax, (%rsp)
	subq	 $8, %rsp
	movl	$2, %eax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	imulq	 (%rsp), %rax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	cqto
	idivq	 (%rsp)
	movq	%rdx, (%rsp)
	subq	 $8, %rsp
	movl	$3, %eax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	cqto
	idivq	 (%rsp)
	movq	%rax, (%rsp)
	subq	 $8, %rsp
	movl	$1, %eax
	movq	%rax, (%rsp)
	movq	(%rsp), %rdx
	addq	 $8, %rsp
	movq	(%rsp), %rax
	addq	 $8, %rsp
	addq	 %rdx, %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, -16(%rbp)
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	subq	 $8, %rsp
	movl	$90, %eax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	negq	 %rax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, -24(%rbp)
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	-8(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC2, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movq	-16(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC3, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movq	-24(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC4, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movq	-16(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	-8(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	subq	 (%rsp), %rax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC5, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC6, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC7, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC8, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC9, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	subq	 $8, %rsp
	movl	$0, %eax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, -16(%rbp)
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	cmpq	 $0, (%rsp)
	je	.L0
	subq	 $8, %rsp
	movl	$6, %eax
	movq	%rax, (%rsp)
	subq	 $8, %rsp
	movl	$5, %eax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	imulq	 (%rsp), %rax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, -8(%rbp)
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	-8(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	subq	 $8, %rsp
	movl	$7, %eax
	movq	%rax, (%rsp)
	subq	 $8, %rsp
	movl	$21, %eax
	movq	%rax, (%rsp)
	subq	 $8, %rsp
	movl	$14, %eax
	movq	%rax, (%rsp)
	subq	 $8, %rsp
	movl	$6, %eax
	movq	%rax, (%rsp)
	subq	 $8, %rsp
	movl	$9, %eax
	movq	%rax, (%rsp)
	movq	-16(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	imulq	 (%rsp), %rax
	movq	%rax, (%rsp)
	movq	-8(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	subq	 (%rsp), %rax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	subq	 (%rsp), %rax
	movq	%rax, (%rsp)
	movq	(%rsp), %rdx
	addq	 $8, %rsp
	movq	(%rsp), %rax
	addq	 $8, %rsp
	addq	 %rdx, %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	cqto
	idivq	 (%rsp)
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	cqto
	idivq	 (%rsp)
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, -8(%rbp)
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	-8(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC10, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC11, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC12, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
.L0:
	subq	 $8, %rsp
	movl	$1, %eax
	movq	%rax, (%rsp)
	movq	-16(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	subq	 (%rsp), %rax
	movq	%rax, (%rsp)
	cmpq	 $0, (%rsp)
	je	.L1
	movq	-16(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, -8(%rbp)
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	-8(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC13, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
.L1:
	movl	$1, %eax
	movq	%rax, from(%rip)
	jmp	.L2
.L3:
	subq	 $8, %rsp
	movl	$1, %eax
	movq	%rax, (%rsp)
	movq	-16(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rdx
	addq	 $8, %rsp
	movq	(%rsp), %rax
	addq	 $8, %rsp
	addq	 %rdx, %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, -16(%rbp)
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	-16(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC14, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movq	-16(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	-8(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rdx
	addq	 $8, %rsp
	movq	(%rsp), %rax
	addq	 $8, %rsp
	addq	 %rdx, %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, -8(%rbp)
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	from(%rip), %rdx
	movl	$2, %eax
	addq	 %rdx, %rax
	movq	%rax, from(%rip)
.L2:
	movl	$10, %eax
	cmpq	 %rax, from(%rip)
	jle	.L3
	subq	 $8, %rsp
	movl	$4000000000, %eax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	negq	 %rax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, -24(%rbp)
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	-24(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC15, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movq	-16(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	-8(%rbp), %rax
	subq	 $8, %rsp
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	subq	 (%rsp), %rax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	 $8, %rsp
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC16, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC17, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC18, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC19, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC20, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC21, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC22, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC23, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC24, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC25, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC26, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC27, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC28, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC29, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC30, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC31, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC32, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC33, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC34, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC35, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC36, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC37, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC38, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC39, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC40, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 6.1.1 20160501"
	.section	.note.GNU-stack,"",@progbits
