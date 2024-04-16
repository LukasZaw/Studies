.CODE

PUBLIC sum, roz, mno, dzi

sum PROC ;rcx, rdx
	movsxd rax, ecx
	add rax, rdx
	ret

sum ENDP

roz PROC ;rcx, rdx
	movsxd rax, ecx
	sub rax, rdx
	ret

roz ENDP

mno PROC ;rcx, rdx
	movsxd rax, ecx
	imul rdx
	ret

mno ENDP

dzi PROC ;rcx, rdx
	movsxd rax, ecx
	movsxd r10, edx
	cqo
	idiv r10
	ret

dzi ENDP

			;x		a		b		c
fun1 PROC	;rcx,	rdx,	r8,		r9
	movsxd rax, ecx
	movsxd r10, edx
	imul rax, rax
	imul r10
	mov r10, rax
	movsxd rax, ecx
	imul r8
	add eax, r10d
	add eax, r9d

	ret

fun1 ENDP
			;a		b		h
fun2 PROC	;rcx,	rdx,	r8
	add rcx, rdx
	mov rax, rcx
	mul r8

	mov r9, 2
	div r9

	ret

fun2 ENDP


END