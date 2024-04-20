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

END