assume cs:codesg,ds:datasg,ss:stacksg

stacksg segment
dw 0,0,0,0,0,0,0,0
stacksg ends

datasg segment
db '1. display......'
db '2. brows........'
db '3. replace......'
db '4. modify.......'
datasg ends

codesg segment
start: mov ax,stacksg
       mov ss,ax
       mov sp,16
       mov ax,datasg
       mov ds,ax
       mov bx,0    ;定义行

       mov cx,4
   s0: push cx
       mov si,0    ;定义列
       mov cx,4
    s: mov al,[bx+3+si]   ;这里是定位到每个要索引的字母，总共每行有四个字母
       and al,11011111b   ;实现使他变为大写字母,OK？
       mov [bx+3+si],al
       inc si     ;使他指向下一个字母。
       loop s

       add bx,16
       pop cx
       loop s0

       mov ax,4c00h
       int 21h
codesg ends
end start

