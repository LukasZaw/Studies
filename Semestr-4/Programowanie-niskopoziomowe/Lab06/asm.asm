.code
pierwiastek32 proc
	push rcx;
	push rbx;
	mov ebx, eax;			*number* to find sqrt of
	mov ecx, 32768;			32BIT: bitmask(starting with b15 bit set) => 0x8000 = decimal 32768
	xor rax, rax;			result <-0	
sqrt_loop:
	xor rax, rcx;			set bit in eax
	push rax;				store result(will be destroyed by mul)
	mul eax;				edx:eax <-eax*eax(ignoring edx next)
	cmp eax, ebx;			compare with *number*
	pop rax;				restore result
	jbe keep_bit;			res ^ 2 <= *number*->bit stays set
	xor eax, ecx;			unset bit in eax
	keep_bit:
	shr ecx, 1;				next bit
	jnz sqrt_loop;			loop till all bits are tried
	pop rbx;
	pop rcx;
	ret;
pierwiastek32 endp


pierwiastek64 proc
	push rcx;
	push rbx;
	mov rbx, rax;			*number* to find sqrt of
	mov rcx, 2147483648;	64bit: bitmask(starting with b31 bit set) => 0x80000000 = decimal 2147483648
	xor rax, rax;			result <-0
	sqrt_loop:
	xor rax, rcx;			set bit in eax
	push rax;				store result(will be destroyed by mul)
	mul rax;				rdx:rax <-rax*rax(ignoring rdx next)
	cmp rax, rbx;			compare with *number*
	pop rax;				restore result
	jbe keep_bit;			res ^ 2 <= *number*->bit stays set
	xor rax, rcx;			unset bit in rax
	keep_bit:
	shr rcx, 1;				next bit
	jnz sqrt_loop;			loop till all bits are tried
	pop rbx;
	pop rcx;
	ret;
pierwiastek64 endp


dlugosc32 proc ; //RCX = **tab, RDX = *v, R8 = m, R9 = n;
	push rsi
	push rdi
	push rbx

	mov rdi, rcx
	mov rbx, rdx
	p1: 
		mov rsi, [rdi + 8*r8 - 8]
		mov r10, r9
		p2: 
			movsxd rax, dword ptr[rsi + 4*r10 - 4]
			imul rax, rax
			movsxd rcx, dword ptr[rbx + 4*r10 - 4]
			imul rcx, rcx
			add rax, rcx
			call pierwiastek64;
			mov dword ptr[rsi + 4*r10 - 4], eax
		dec r10
		jnz p2
	dec r8
	jnz p1

	pop rbx
	pop rdi
	pop rsi
	ret
dlugosc32 endp
end