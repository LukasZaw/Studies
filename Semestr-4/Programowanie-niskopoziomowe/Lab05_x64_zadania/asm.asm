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

END