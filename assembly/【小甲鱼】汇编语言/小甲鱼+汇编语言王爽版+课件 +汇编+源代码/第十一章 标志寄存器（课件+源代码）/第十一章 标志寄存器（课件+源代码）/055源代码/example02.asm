assume cs:code

code segment

start: 	mov al, 10001000b
		add al, 11110000b
		
		mov ax, 4c00h
		int 21h
code ends

end start