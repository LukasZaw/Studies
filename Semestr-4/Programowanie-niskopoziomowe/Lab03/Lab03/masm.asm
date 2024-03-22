.CODE

if_1 PROC
	cmp rcx, rdx 
	jl jezeliPrawda1
		xor rax, rax ; 0
	jmp pomin1
	
	jezeliPrawda1:
		sub rdx, rcx ; x = b - a
		mov rax, rdx
	pomin1:

	ret
if_1 ENDP


if_2 PROC
	cmp rcx, rdx 
	jl jezeliPrawda2
		sub rcx, rdx ; x = a - b
		mov rax, rcx
	jmp pomin2
	
	jezeliPrawda2:
		sub rdx, rcx ; x = b - a
		mov rax, rdx
	pomin2:

	ret
if_2 ENDP


if_3 PROC
	cmp rcx, rdx ; a >= b
	jge jezeliPrawda3
		mov r8, rdx
		mov rax, rcx
		mul rax
		sub rax, r8
	jmp pomin3
	
	jezeliPrawda3:
		mov r8, rdx
		mov rax, rcx
		mul rax
		add rax, r8
	pomin3:

	ret
if_3 ENDP

switch_1 PROC
	

	cmp rdx, 0
	je case10
	cmp rdx, 1
	je case11
	cmp rdx, 2
	je case12
	cmp rdx, 3
	je case13
	jmp deff1

	case10:
		mov rax, rcx
		add rax, 7
		jmp exit1
	case11:
		mov rax, rcx
		add rcx, 3
		mul rcx
		jmp exit1
	case12:
		mov rax, rcx
		mul rax
		mov r8, rax
		mov rax, rcx
		mov r9, 2
		mul r9
		add rax, r8

		jmp exit1
	case13:
		mov rax, rcx
		mul rax
		sub rax, 12
		jmp exit1
	deff1:
		mov rax, 0

	exit1:

	ret
switch_1 ENDP

for_1 PROC
	mov r8, rcx
	mov r9, 2

	mov rax, 0
	mov rcx, 0
	petlaFOR:
	cmp rcx, r8 ;N
	jge koniecFOR

		mov rax, rcx
		mul r9
		add rbx, rax

	inc rcx
	jmp petlaFOR
	koniecFOR:

	mov rax, rbx
	ret
for_1 ENDP



for_2 PROC
	mov r8, rcx

	mov rcx, 0
	petlaFOR:
	cmp rcx, r8 
	jge koniecFOR

		add rbx, r8

		inc rcx
	jmp petlaFOR
	koniecFOR:

	mov rax, rbx
	ret
for_2 ENDP


silnia PROC
	mov rbx, rcx
	mov rcx, 0
	mov rax, 1

	petlaFOR:
	
		mul rbx
		dec rbx
		cmp rbx, 1 
		jg petlaFOR

	koniecFOR:

	ret
silnia ENDP

END
