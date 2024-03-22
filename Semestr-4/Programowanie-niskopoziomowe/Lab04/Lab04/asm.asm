.CODE

fun1 PROC
	mov rax, 0
	petla: 
		movsxd r8, dword ptr [rcx+4*rdx-4]
		imul r8, r8
		add rax, r8
		dec rdx
	jnz petla
	ret
fun1 ENDP

fun2 PROC
	petla:
		mov eax, [rdx+4*r8-4]
		add [rcx+4*r8-4], eax
		dec r8
	jnz petla
	ret
fun2 ENDP

fun3 PROC
	petla:
		mov eax, [rdx+4*r8-4]
		add [rcx+4*r8-4], eax
		dec r8
	jnz petla
	ret
fun3 ENDP

END