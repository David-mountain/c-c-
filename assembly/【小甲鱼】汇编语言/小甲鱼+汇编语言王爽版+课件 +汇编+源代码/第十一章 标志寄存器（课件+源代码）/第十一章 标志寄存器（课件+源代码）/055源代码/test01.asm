assume cs:code
 
code segment
start:	mov al, 98h
		add al, al
		add al, al
		
		mov ax, 4c00h
		int 21h
	
code ends

end start