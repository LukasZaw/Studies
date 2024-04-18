.CODE

zad1 PROC ;rcx - a
	mov rax, rcx
	mul rcx
	mul rcx

	ret
zad1 ENDP

zad2 PROC ;rcx - a, rdx - b, r8 - c, r9 - x
	imul rdx, r9 ; rdx - b*x
	mov r10, r9
	imul r10, r10
	imul r10, rcx ; r10 - a*x*x

	mov rax, r10
	add rax, rdx
	add rax, r8

	ret
zad2 ENDP


END