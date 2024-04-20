.CODE

zad0 proc uses rbx, v1:ptr, v2:ptr, v3:ptr, v4:ptr, n:dword
	mov rsi, rcx
	mov rdi, rdx
	movsxd rcx, n
	petla:
		mov rax, qword ptr [rsi + rcx * 8 - 8]
		cmp rax, 0
		cmovnle rax, qword ptr [rdi + rcx * 8 - 8]; //not less or equal
		cmovnle rbx, qword ptr [r8 + rcx * 8 - 8]
		cmovle rax, qword ptr [r8 + rcx * 8 - 8]; // less or equal
		cmovle rbx, qword ptr [rdi + rcx * 8 - 8]
		sub rax, rbx
		mov qword ptr [r9 + rcx * 8 - 8], rax
		loop petla
	ret
zad0 endp

zad1 proc
	cmp rcx, rdx
	cmovge rax, rcx
	cmovnge rax, rdx

	ret
zad1 endp

zad2 proc uses rbx ; rcx - a, rdx - b, r8 - c
	cmp rcx, rdx
	cmovle rbx, rcx
	cmovnle rbx, rdx


	cmp rbx, r8
	cmovle rax, rbx
	cmovnle rax, r8

	ret
zad2 endp

zad3 proc uses rbx; rcx - a, rdx - b
	mov r8, rcx
	sub r8, rdx
	
	mov r9, rdx
	sub r9, rcx

	cmp rcx, rdx
	cmovg rax, r8
	cmovng rax, r9

	ret
zad3 endp

zad4 proc uses rbx rsi rdi ; rcx - **tab, rdx - n
	
	mov rdi, rdx

	petla1:
		mov rsi, [rcx + 8*rdi - 8]
		mov r8, rdx
		petla2:
			mov rax, 0
			movsxd r9, dword ptr [rsi + 4*r8 - 4]
			cmp r9, 10
			cmovge r9d, eax
			mov [rsi + 4*r8 - 4], r9d

			dec r8
		jnz petla2
		dec rdi
	jnz petla1

	ret
zad4 endp

zad5 proc uses rbx rdi rsi; rcx - a, rdx - b
	mov rsi, rcx ; a
	mov rdi, rdx ; b
	
	mov rax, rsi
	inc rax
	xor rdx, rdx
	div rdi
	mov r8, rax ; wynik 1

	mov r9, rdi
	inc r9
	imul r9, rsi


	cmp rsi, rdi
	cmovle rax, r8
	cmovnle rax, r9

	ret
zad5 endp

END