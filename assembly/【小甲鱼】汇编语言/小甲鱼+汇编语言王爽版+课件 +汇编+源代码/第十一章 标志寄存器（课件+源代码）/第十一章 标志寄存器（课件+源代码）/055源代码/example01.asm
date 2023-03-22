assume cs:code

code segment

start: 	mov al, 01100010b
		add al, 01100011b
		
		mov ax, 4c00h
		int 21h
code ends

end start