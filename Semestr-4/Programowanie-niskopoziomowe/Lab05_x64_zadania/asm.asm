.CODE

zad2_32 PROC uses rsi rdi rbx, tab1:ptr, tab2:ptr, tab3:ptr, a:qword, b:qword
		;rcx - tab1, rdx - tab2, r8 - tab3, r9 - a, stos - b
	xor rax, rax
	mov r11, b

	petla1:
		mov rsi, [rcx + 8*r9 - 8]
		mov rdi, [rdx + 8*r9 - 8]
		mov r12, [r8 + 8*r9 - 8]

		mov r10, r11 ;m
		petla2:
			movsxd rax, dword ptr [rsi + 4*r10 - 4]
			movsxd rbx, dword ptr [rdi + 4*r10 - 4]
			cmp rax, rbx
				jle skok
				add rax, rbx
				mov [r12 + 4*r10 - 4], eax
			skok:
			dec r10
		jnz petla2
		dec r9
	jnz petla1
	ret 
zad2_32 ENDP

zad4 PROC uses rbx rsi rdi ;rcx - tablica**, rdx - n
	
	mov rdi, rdx

	petla1:
		mov rsi, [rcx + 8*rdi - 8]
		mov r8, rdx
		petla2:
			movsxd rax, dword ptr [rsi + 4*r8 - 4]
			cmp rdi, r8
			jg skok
				imul rax, rax
				mov [rsi + 4*r8 - 4], eax

			skok:
			dec r8
		jnz petla2
		dec rdi
	jnz petla1
	
	ret 
zad4 ENDP

zad5 PROC uses rbx rsi rdi ;rcx - tablica**, rdx - n
	
	mov rbx, rdx
	mov rdi, rbx

	mov r9, 0 ; licznik ++
	mov r10, 2

	petla1:
		mov rsi, [rcx + 8*rdi - 8]
		mov r8, rbx
		petla2:
			
			mov rax, r9
			xor rdx, rdx
			div r10

			cmp rdx, 0
			jne skok
				mov [rsi + 4*r8 - 4], edx


			skok:
			inc r9
			
			dec r8
		jnz petla2
		inc r9
		dec rdi
	jnz petla1
	

	
	ret 
zad5 ENDP


END