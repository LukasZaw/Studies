.CODE

poleKwad PROC ;rcx - tablica v, rdx - N
	mov rax, 0

	petla1:
		movsxd r8, dword ptr [rcx + 4*rdx - 4]
		imul r8, r8
		add rax, r8
		dec rdx
	jnz petla1

	ret
poleKwad ENDP

sumaTab PROC ;rcx - tablica v, rdx - tablica u, r8 - N
	
	petla1:
		mov rax, [rdx+4*r8-4]
		add [rcx+4*r8-4], rax 
		dec r8
	jnz petla1

	ret
sumaTab ENDP

skalar PROC ;rcx - tablica v, rdx - tablica u, r8 - N
	
	mov rax, 0	

	petla1:
		mov r9d, [rcx+4*r8-4]
		imul r9d, [rdx+4*r8-4]
		add eax, r9d

		dec r8
	jnz petla1

	ret
skalar ENDP

zad1 PROC ;rcx - tablica v, rdx - N
	
	petla1:
		movsxd r8, dword ptr [rcx+4*rdx-4]
		imul r8, r8
		mov [rcx+4*rdx-4], r8d

		dec rdx
	jnz petla1
	ret
zad1 ENDP

zad2 PROC ;rcx - tablica v, rdx - N
	push rsi

	mov r9, 2	
	mov rsi, rcx
	mov rbx, rdx

	petla1:
		movsxd r8, dword ptr [rsi+4*rbx-4]
		
		mov rax, r8
		xor rdx, rdx
		idiv r9
		cmp rdx, 0
		jne pomin1
			movsxd r8, dword ptr [rsi+4*rbx-4]
			imul r8, r8
			mov [rsi+4*rbx-4], r8d
		pomin1:

		dec rbx
	jnz petla1

	pop rsi
	ret
zad2 ENDP

zad3 PROC ;rcx - tablica v, rdx - N
	mov rbx, 2
	mov r8, rdx
	petla:
		xor rdx, rdx
		mov rax,r8
		idiv rbx
		cmp rdx, 0
		jne skok
			xor rax, rax
			mov [rcx+4*r8-4] , eax
		skok:
		dec r8
	jnz petla
	ret
zad3 ENDP

zad4 PROC ;rcx - tablica v, rdx - N
	push rsi
	
	mov rsi, rcx
	mov r8, rdx
	mov r9, rdx
	mov rax, 0 ; suma

	petla:
		
		add eax, [rsi + 4*r8 - 4]

		dec r8
	jnz petla

	xor rdx, rdx
	div r9

	pop rsi
	ret
zad4 ENDP

zad9 PROC ;rcx - tablica a, rdx - tablica b, r8 - tab c, r9 - N
	push rsi
	push rdi
	push rbx

	mov rsi, rcx
	mov rdi, rdx


	petla:
		movsxd rax, dword ptr [rsi + 4*r9 - 4]
		movsxd rbx, dword ptr [rdi + 4*r9 - 4]
		xor rdx, rdx
		idiv rbx

		mov [r8 +4*r9 - 4], eax

		dec r9
	jnz petla

	
	pop rsi
	pop rdi
	pop rbx
	ret
zad9 ENDP

END