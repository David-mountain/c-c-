assume cs:codesg,ds:datasg

datasg segment
db 'ibm             '
db 'dec             '
db 'dos             '
db 'vax             '
datasg ends

codesg segment
start: mov ax,datasg
       mov ds,ax
       mov bx,0       ;用BX来定位行

       mov cx,4
   s0: mov dx,cx      ;我们用dx寄存器来临时存放外层cx的值
	   mov si,0       ;用SI来定位列
       mov cx,3
	   
    s: mov al,[bx+si]
       and al,11011111b
       mov [bx+si],al

       inc si

       loop s       ;此时的CX已经为零了，对吧？

       add bx,16
	   mov cx,dx   ;在进行外层循环的时候恢复CX的值。
       loop s0     ; CX = CX - 1  再判断是否为零

       mov ax,4c00h
       int 21h
codesg ends
end start

