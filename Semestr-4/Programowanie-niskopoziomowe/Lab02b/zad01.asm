.CODE

PUBLIC szescian, funk

szescian PROC
	movsxd rax, ecx
	mul eax
	mul ecx
	ret
szescian ENDP

funk PROC
	movsxd rax, ecx
	movsxd r10, edx
	mul eax
	mul r10
	ret
funk ENDP

END
