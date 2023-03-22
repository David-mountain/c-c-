assume cs:codesg

codesg segment
start:
	mov ax,1000h
	mov bh,1
	div bh
	
codesg ends

end start