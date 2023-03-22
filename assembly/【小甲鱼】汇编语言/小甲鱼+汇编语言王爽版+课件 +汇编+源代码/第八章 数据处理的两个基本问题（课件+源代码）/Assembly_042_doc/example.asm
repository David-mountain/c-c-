assume cs:codesg,ds:data,es:table

 

data segment

        db '1975','1976','1977','1978','1979','1980','1981','1982','1983'

        db '1984','1985','1986','1987','1988','1989','1990','1991','1992'

        db '1993','1994','1995'

        ;以上是表示21年的21个字符串

 

        dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514

        dd 345980,590827,803530,1183000,1843000,2759000,3753000,4649000,5937000

        ;以上是表示21年公司总收的21个dword型数据

 

        dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793,4037,5635,8226

        dw 11542,14430,45257,17800

        ;以上是表示21年公司雇员人数的21个word型数据

data ends

 

table segment

        db 21 dup('year summ ne ?? ')

table ends

 

codesg segment

 

start:

        mov ax,data

        mov ds,ax

        mov ax,table

        mov es,ax

 

        mov bx,0

        mov si,0

        mov di,0

        mov cx,21

 

        s:   ;进入循环

                mov al,[bx]

                mov es:[di],al

                mov al,[bx+1]

                mov es:[di+1],al

                mov al,[bx+2]

                mov es:[di+2],al

                mov al,[bx+3]

                mov es:[di+3],al

                ;以上8句的作用是存放年份

 

                mov ax,54h[bx]     ;第一个'年收入'的段基址为54H

                mov dx,56h[bx]

                mov es:5h[di],ax

                mov es:7h[di],dx

                ;以上4句的作用是存放公司总收入

 

                mov ax,0A8h[si]    ;第一个'人数'的段基址为0A8H

                mov es:0Ah[di],ax

                ;以上2句是存放公司的人数

 

                mov ax,54h[bx]

                div word ptr ds:0A8h[si]

                mov es:0dh[di],ax

                ;以上3句是存放人均收入

 

                add bx,4

                add si,2

                add di,16

                ;以上3句是为下一次循环时存放数据做准备

                ;3个寄存器递增的速度决定了所要存取的数据的位置的偏移地址

        loop s  ;跳到标号s处

 

mov ax,4c00h

int 21h

 

codesg ends

end start
