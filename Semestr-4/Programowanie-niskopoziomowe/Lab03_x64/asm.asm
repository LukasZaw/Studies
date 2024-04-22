.CODE

if_1 PROC ;rcx - a, rdx - b
	
	cmp rcx, rdx
	jl skok1
		xor rax, rax

		jmp end1
	skok1:
		sub rdx, rcx
		mov rax, rdx

	end1:
	ret
if_1 ENDP

if_4 PROC ;rcx - a, rdx - b
	
	cmp rcx, rdx
	jl skok1
		mov r8, rdx
		mov rax, rcx
		mul rcx

		sub rax, r8

		jmp end1
	skok1:
		mov r8, rdx
		mov rax, rcx
		mul rcx

		add rax, r8

	end1:
	ret
if_4 ENDP

case_2 PROC ;rcx - x, rdx - op
	
	mov r8, rdx

	cmp r8, 0
	je case0
	cmp r8, 1
	je case1
	cmp r8, 2
	je case2
	cmp r8, 3
	je case3
	jmp def

	case0:
		add rcx, 7
		mov rax, rcx
		jmp end1
	case1:
		mov rax, rcx
		add rax, 3
		imul rax, rcx
		jmp end1
	case2:
		mov rax, rcx
		imul rax, 2

		imul rcx, rcx
		add rax, rcx
		jmp end1
	case3:
		imul rcx, rcx
		sub  rcx, 12
		mov rax, rcx
		jmp end1
	def:
		xor rax, rax
	end1:
	ret
case_2 ENDP

for_1 PROC ;rcx - N
	
	xor rax, rax
	mov rdx, 0
	petla1:
		mov r8, rdx
		imul r8, 2
		add rax, r8
		inc rdx
	cmp rdx, rcx
	jl petla1

	ret
for_1 ENDP

silnia PROC ;rcx - N
	mov rdx, 1

	petla1:
		imul rdx, rcx
		dec rcx
	jnz petla1
	mov rax, rdx

	ret
silnia ENDP

while_1 PROC ;rcx - a, rdx - r, r8 - max
	xor rax, rax
	mov r9, rcx
	add r9, rdx ; w

	petla1:
		cmp r9, r8
		jge end1

		add rax, r9
		add r9, rdx

	jmp petla1
	end1:

	ret
while_1 ENDP

zad3 PROC ;rcx - a, rdx - b
	
	cmp rcx, 0
	jne skok1
		cmp rdx, 0
		je koniec1
			mov r8, rdx
			mov rax, rcx
			xor rdx, rdx
			idiv r8
		jmp koniec1
	jmp koniec1
	skok1:
		mov r8, rcx
		mov rax, rdx
		xor rdx, rdx
		idiv r8
	koniec1:

	ret
zad3 ENDP

zad4 PROC ;rcx - op, rdx - a, r8 - b 

	cmp rcx, 1
	je switch1
	cmp rcx, 2
	je switch2
	jmp def1

	switch1: 
		imul rdx, 2
		mov rax, rdx
	jmp koniec1
	switch2:
		mov r9, 2
		mov rax, r8
		xor rdx, rdx
		div r9
	jmp koniec1

	def1:
		add rdx, r8
		mov rax, rdx

	koniec1:

	ret
zad4 ENDP

zad6 PROC ;rcx - a
	
	mov rdx, 1
	mov r8, rcx

	skok1:
	cmp rdx, rcx
	jge koniec1
		add r8, rcx

		inc rdx
		jmp skok1
	koniec1:


	mov rax, r8
	ret
zad6 ENDP

min PROC ;rcx - a, rdx, r8
	
	cmp rcx, rdx
	jg skok1
		mov rdx, rcx
	skok1:
	cmp rdx, r8
	jg skok2
		mov r8, rdx
	skok2:
	mov rax, r8
	
	ret
min ENDP

END