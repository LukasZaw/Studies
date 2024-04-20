.CODE

suma32 PROC ; rcx - tablica **tab, rdx - n, r8 - m
	push rsi

	xor rax, rax ; suma

	petlaN:
		mov rsi, [rcx + 8*rdx - 8]
		mov r10, r8 ; m
		petlaM:
			movsxd r9, dword ptr [rsi + 4*r10 - 4]
			add rax, r9
			dec r10
		jnz petlaM
		dec rdx
	jnz petlaN

	pop rsi
	ret
suma32 ENDP

suma64 PROC ; rcx - tablica **tab, rdx - n, r8 - m
	push rsi

	xor rax, rax ; suma

	petlaN:
		mov rsi, [rcx + 8*rdx - 8]
		mov r10, r8
		petlaM:
			add rax, [rsi + 8*r10 - 8]
			dec r10
		jnz petlaM
		dec rdx
	jnz petlaN


	pop rsi
	ret
suma64 ENDP

uemxv proc uses rbx rsi, mm:ptr, v:ptr, u:ptr, k:qword, l:qword
			; //RCX = **vv, RDX = *u, R8 = *y, R9 = k, Stos = l;
	mov r11, l

	petlaN:
		mov rsi, [rcx + 8*r9 - 8]
		mov rbx, r11 ; l
		xor r10, r10 ; suma

		petlaM:
			mov rax, [rsi + 8*rbx - 8]
			imul rax, [rdx + 8*rbx - 8]
			add r10, rax

			dec rbx
		jnz petlaM
		mov [r8 + 8*r9 - 8], r10
		dec r9
	jnz petlaN

	ret
uemxv endp

sumaMeUpV proc uses rbx rsi rdi, qwe:ptr, asd:ptr, zxc:ptr, a:qword, b:qword
			;RCX = **qwe, RDX = **asd, R8 = **zxc, R9 = a, Stos = b;
	mov r11, b

	petla1:
		mov rsi, [rcx + 8*r9 - 8]
		mov rdi, [rdx + 8*r9 - 8]
		mov rbx, [r8 + 8*r9 - 8]
		mov r10, r11

		petla2:
			mov rax, [rsi + 8*r10 - 8]
			add rax, [rdi + 8*r10 - 8]
			mov [rbx + 8*r10 - 8], rax

			dec r10
		jnz petla2
		dec r9
	jnz petla1

	ret
sumaMeUpV endp


END