.code
	suma32 proc ; //RCX = **tab, RDX = m, R8 = n;
		push rsi

		xor rax, rax ;suma=0
		
		petlaM:
			mov rsi, [rcx + 8*rdx - 8] ; // wskaünik do wiersza
			mov r10, r8 ; n
			petlaN:
				movsxd r11, dword ptr[rsi + 4*r10 - 4]
				add rax, r11
				dec r10
			jnz petlaN
			dec rdx
		jnz petlaM
		
		pop rsi
		ret
	suma32 endp


	suma64 proc uses rsi; //RCX = **tab, RDX = n, R8 = m;
		xor rax, rax ;suma=0

		petlaN:
			mov rsi, [rcx + 8*rdx - 8] ; // wskaünik do wiersza
			mov r10, r8 ; m
			petlaM:
				add rax, [rsi + 8*r10 - 8]
				dec r10
			jnz petlaM
			dec rdx
		jnz petlaN
		ret
	suma64 endp

	
	uemxv proc uses rbx rsi, mm:ptr, v:ptr, u:ptr, m:qword, n:qword
		; //RCX = **mm, RDX = *v, R8 = *u, R9 = m, Stos = n;
	mov r11, n

	petlaM:
		mov rsi, [rcx + 8*r9 - 8] ;mm[m]* ustawiamy siÍ na ostatni element
		mov rbx, r11 ;n
		xor r10, r10 ;suma
		petlaN:
			mov rax, [rsi + rbx*8 - 8] ; rax = m[m][n]
			imul rax, [rdx + rbx*8 - 8]; rax *= v[n]
			add r10, rax
			dec rbx
		jnz petlaN
		mov [r8 + r9*8 - 8], r10
		dec r9
	jnz petlaM
	ret
	uemxv endp



END