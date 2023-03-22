assume cs:code
 
code segment
start:	mov al, 97h
		sub al, 98h
		sub al, al
		
		mov ax, 4c00h
		int 21h
	
code ends

end start