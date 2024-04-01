第一部分VIM:
xshell打不开gedit编辑器 必须要去虚拟机中打开
vi编辑器是Linux中最常用的文本编辑器，vi在linux界有编辑器之神的美称
几乎所有的linux都包含vi程序。
vim是vi的升级版，它不仅兼容vi的所有指令，而且还有一些新特性。
vim普遍被推崇为类vi编辑器中最好的一个。
甚至可以配置成vs

命令模式 文本输入模式(编辑模式) 末行模式
模式的切换。
打开默认是命令模式
末行模式-用户可以对文件进行一些附加处理  尽量命令模式可以完成洋房多功能
但是执行字符串查找 替换 显示行号等还是必须要进入末行模式
命令模式中，输入 冒号即可进入末行模式 
:set nonu 
:set nu 显示行号

vim a.txt 打开或新建
原来命令模式下也可以退出 shift+zz 即保存退出
末行模式：   :wq

命令切换到编辑模式 i o(向下插入一行) a s 大小写意义不一样
文件有颜色，不要随便编辑，否则可能就没有了
拷贝 再编辑 cp 

光标移动：命令模式下 编辑模式就吧这些输入进去了
ctfl + f  向上上一个屏幕
ctrl + b 向下一个屏幕
gg  文件第一行行首
G   文件最后一行行首
mG / mgg 到指定行 m是目标行数 28gg

0 行首
$  行尾

l 小写L 右移 
h  左移
k  上移
j 下移

^ 行首 第一个有效字符

复制粘贴：
[n]yy 复制从当前行开始的n行  3yy 我要去数？
p  吧粘贴板内容粘贴到当前行
ctrl + v 挪动光标选中文字   y  p  可部分选中


删除 多用
都是在命令模式下哈
[n]x 删除光标后n个字符
[n]X 删除光标前n个字符
D  光标所在 到行尾的字符
[n]dd  删除当前行开始 的n行 准备说是剪切，不粘贴即删除
dG 光标到文件尾的所有字符  
dw  删光标所在的字符
d0  光标前所有内容 不含光标所在字符 
dgg  光标之前全部删除 

撤销恢复
. 点  执行上次命令
u  	   撤销上次命令  用多
ctrl + r  反撤销 恢复
100 + .    执行上次操作100次

保存退出
shft + zz(ZZ)

查找
/字符串  从当前光标位置向下查找()
？字符串 从当前光标位置向上查找
输入后，按回车，然后 n(下一个) N 切换所查内容，
：nohl 不要高亮 我觉得要好

替换
r 替换当前字符
R 替换当前行光标后的字符 esc退出替换模式 到命令模式

可视模式
这个就是我之前的疑问，不可能数要操作多少行，一般都是选中。
v 即可行选列选 按字符移动 选中文本 配合h j k l 选择内容 使用d删除 使用y复制
shift + v 行选 
ctrl + v  列选

末行模式
保存退出：
:wq  
:x 小写
:w filename(绝对路径) 另存为
:q 
:q! 退出 不保存 

替换
一定光标在所操作行 前提
:s/abc/123/ 光标所在行 第一个abc替换为123
:s/abc/123/g 所在行 所有abc替换成123
:1,10s/abc/123/g 1-10行替换
:%s/abc/123/gc %当前文件 替换
:1,$s/abc/123/g 1-文件尾 即当前文件所有 替换

分屏
:sp  水平分屏
ctrl-w-w 切换光标 多个分屏中
:q 退出光标所在分屏中
:wq 
:vsp 垂直分屏
:wall / :wqall / :qall 保存/保存退出/退出所有分屏窗口
:split txt ? 另外一个文件分屏 相对 绝对路径都可以
vim -O a.c b.c 垂直分屏
vim -o a.c b.c 水平分屏

其他用法
:!man 2 printf vim中执行命令 vim中突然不会某函数 想查哈
:r !ls -l 将ls -l执行的结果写入当前文件中
:r /etc/passwd 将/etc/passwd文件中的内容写入到当前文件中
u撤销 
:w /tmp/txt 将当前文件内容写入到/tmp/txt文件中 (文件不存在用这个)
:w! /tmp/txt 强制将 将当前文件内容写入到/tmp/txt文件中

:1,10s/^/\/\ 批量注释 还有其他方法
删除注释 列选+d删除 可不用批量注释的方法
:1,10s#//## #临时代替/分割 去注释
:1,10s#^#//# 

分号替换成{ return 0 } 省略了 有点难了 多了 

配置文件
局部-推荐
vim ~/.vimrc 
全局-最好不要修改这个


第二部分：编译 链接 
------11、GCC工作流程和常用选项----
vs集成了编译器 调试器
vs是微软开发的，无linux版本
编译器 gcc-GNU编译套件 最初是用来编译C，后来多了很多语义
GCC是编译器 GNU组织开发的

type gcc 
外部命令
gcc --help 这里能看到-E -S等的作用
当然也可以 man gcc 

hello.c 预处理 gcc -E 
hello.i 编译器 gcc -S 
hello.s 汇编文件 汇编器 gcc -c 
hello.o 二进制文件 连接器 gcc 
a.out 可执行文件  

预处理-编译-汇编-链接生成可执行文件。
-E 只是做了预处理-宏替换 去掉注释 头文件展开
-S 编译 没有汇编和链接 生成一个汇编文件.s 
-C 编译和汇编 没有链接 把汇编文件生成一个目标文件 .o 
-o 

编译工具链：
预处理器cpp 宏替换 去掉注释 头文件展开
编译器gcc c变成汇编文件
汇编器as  汇编文件变二进制文件
链接器ld 将库函数中相应的代码组合到目标文件中

vim hello.c 
gcc -E hello.c -o hello.i 预处理完了
vim hello.i 看
gcc -S hello.i -o hello.s 得汇编文件
vim hello.s X86汇编 大写学的8086 工作多用arm汇编
gcc -c hello.s -o hello.o 得目标文件 
-o无法被执行的，看不懂，二进制文件
file hello.c 查到LSB小端模式
gcc hello.o -o hello 得可执行文件
./hello 执行文件

实际一步到位即可：
gcc hello.c -o hello  做了四步
如果不指定-o 后面的名字，会默认生成一个 a.out 

可能工作中因为版本的原因编译失败。

mv a b.c 移动 不是很熟悉

gcc 选项
-o file 
-E
-S 
-c 
-v/--version 编译失败可能就是版本原因
-g 	gcc -g hello.c -o hello2
	ls -l hello.c hell2 看谁大点 大多少
	突然想到买土豆案例 让你问多少钱 你就真的只问多少钱 质量？还可以砍价不？等等 
-On  n=0-3 代码优化  
-Wall
-D

-g
gcc -g hello.c -o hello2 包含调试信息
ll -l hello hello2 
-On n=0-3
 编译优化，n越大优化越多
-Wall
写代码尽量不要出现警告，编译时候有警告，但不是致命的
我们要显示 gcc -Wall hello.c 
gcc -Wall -Werror hello.c 
把警告当作错误处理 这样就无法编译通过

调试版本 生产版本
-D 
场景：开关语句 参数
#ifdef #else 的语句开关
#ifdef DEBUG
	printf(1213);
#else  
	printf(999);
gcc a.c 
./a.out  999
gcc a.c -DDEBUG	
./a.out  1213

--静态链接和动态链接
源码不能给客户，
把我们的核心代码做成一个库，给客户，静态库，动态库
静态链接和动态链接区别：看MD把，省略。 
默认是动态编译。
程序对比：
liunx gcc 编译，生成的那个是用的动态链接
gcc a.c -o a_share 默认动态  
gcc -static a.c -o a_static 静态
./a_share 
./a_static 
ls -l a* 可以看到a开头的文件 信息
静态编译的包很大 ，动态很小 1 0 倍 

动态链接：程序运行时 按需加载
静态链接：整个加入到可执行程序中

--静态库制作和使用
touch add.c add.h 
ls 
vim add.h  
#ifndef __ADD_H__
#define __ADD_H__

int add(int x, int y);

#endif /* __ADD_H__ */

vim add.c 
#include "add.h"

int add (int x, int y)
{
	return x + y;
}

继续减法：
cp add.h sub.c 这里视频搞错了 看怎么纠正的
mv sub.c sub.h   这里想少些代码，复制之前add
ls  
cp add.c sub.c  
vim sub.h   
看它怎么把ADD改成SUB的
:%s/ADD/SUB/g  
:%s/add/sub/g 
同理改sub.c 但是有个符号要手动
同理，乘法 除法 

还没有主函数，vim test.c 
#include <stdio.h> 直接搜索库目录
#include "add.h" 先搜索当前目录，再搜索库目录
#include "sub.h"
#include "mul.h"
#include "div.h"

int main ()
{
	int x = 15;
	int y = 5;

	printf("x + y = %d \n", add(x, y));
	printf("x + y = %d \n", sub(x, y));
	printf("x + y = %d \n", mul(x, y));
	printf("x + y = %d \n", div(x, y));

	printf("hello world \n");

	return 0;
}
如何编译呢？这么多.c 
gcc add.c sub.c mul.c div.c test.c 
./a.out  gcc是生成a.out的文件的
或者可以 gcc *.c 加上正则了

程序库，简单说，就是包含了数据和执行码的文件，其不能单独执行，
可以作为其他执行程序的一部分来完成某些功能
静态库 动态库 
程序没问题后，然后看静态库怎么制作
按照习惯，一般以.a作为文件后缀名。静态库的命名一般分三个部分：
前缀：lib 
库名称：自定义
后缀：.a  
最终： libxxx.a  

流程：
源文件.h .c -> 预编译 -> 编译 -> 汇编 目标文件a1.o a2.o ... 
-> ar工具 编译、索引、压缩打包 -> 静态库 libxxx.a 

gcc -c add.c -o add.o 
gcc -c sub.c -o sub.o
gcc -c mul.c -o mul.o
gcc -c div.c -o div.o
ls 
ls *.o 查看文件
库函数，就不需要test了哈。搞清楚哈。
打包生成静态库 用到工具ar 
使用ar工具时候需要添加参数：rcs 
r更新 c创建 s建立索引 

ar -rcs libtest.a add.o sub.o mul.o div.o 
ls 
vim listest.a 都是二进制文件 
到这里一个静态库就做好了。

--静态库测试
先自测。
cp 2static_lib/ 3static_test -rf 
ls 
rm -rf *.o  删除
ls   
rm -rf add.c sub.c div.c mul.c  
ls 

gcc test.c -I./ -L./ -ltest 
-I 指定头文件目录
-L 指定要链接的库的路径
-l test 库名字(这里去掉前后缀的) 指定链接时需要的库
./a.out 成功运行

多个程序都引用了这个静态库，多份拷贝，浪费
静态库在内存中存在多份拷贝 导致空间浪费。
这就是静态库大的原因之一。

---动态库制作
学一个东西：是什么 为什么 解决了什么 怎么用 优缺点
动态库解决了静态库对程序的更新，部署和发布带来的麻烦。
用户只需要更新动态库即可，增量更新。
按照习惯，一般以 .so 作为文件后缀名，共享库的命名一般分三个部分：
前缀：lib 库名称：自定义 后缀：so  
libxxx.so  

cp a c -rf cp,a到c
rm -rf *.o 删除
rm -rf *.a 

1.生成目标文件，此时要加编译选项
 -fpic 创建与地址无关的编译程序
2. 生成共享库，此时要加连接器选项：-shared(指定生成动态链接库)
3. 通过nm命令查看对应的函数

gcc -fpic -c add.c 
gcc -fpic -c sub.c 
gcc -fpic -c mul.c 
gcc -fpic -c div.c 
ls 4 个 .o

gcc -shared add.o sub.o mul.o div.o -o libaaa.so 
-o libaaa.so 输出文件名 aaa 
ls 
nm lisaa.so  
nm libaa.so | grep "add" 找到一个add文件
说明已经制作好了，动态库 libaa.so目录中有个表示成功

--动态库测试
cp 3static_test/ 5share_test -rf 
cd 5share_test/
ls 
rm -rf a.out *.a 
ls 
对应的头文件和库给客户，不要给源码

vim test.c 
gcc test.c -L. -I. -laa 
./a.out 报错了 
链接器不知道文件 哪里 
1.把我们的库 拷贝到标准库里面 不推荐的
sudo cp libaa.so /lib 
gcc test.c -I. -laa 
成功了。

2.跳 其他办法 
失败那集跳了 

-- GDB启动和设置运行参数
GNC工具集中的调试器是GDB，该程序是一个交互式工具
工作在字符模式。除GDB外，其他有名的调试器还有xxgdb ddd kgdb ups 
gdb主要帮你完成4个方面的功能：
1.启动程序，可以按照你的自定义的要求运行程序
2.可让被调试的程序在你所指定的设置的断点处停住
3.当程序被停住时，可以检查测试你的程序中所发生的事
4.动态的改变你程序的执行环境

vim test.c 
int i = 0;
for (i = 0; i < 100; i++)
{
	printf(i);
}
fun();
printf("hello");

gcc test.c 
./a.out 执行 
但是没有调试信息
gcc -g test.c 
ls  
生成了一个有调试信息的./a.out  可执行程序

然后 启动GDB 
gdb program(你的执行文件，一般在 当前目录下)
设置运行参数：
set args  可指定运行时参数 set args 10 20 30 40 50
show args 命令可以查看设置好的运行参数
启动程序：
run 程序开始执行，如果有断点，停在第一个断点处
start 程序向下执行一行

main函数可以接收 命令行的参数
int main (int arg, char **argv)
gdb a.out  
进入调试界面了
set args 10 20 30 40 
show args 
quit 退出

vim test.c 
for (i=0; i<argv;i++)
{
	printf(i, argv[i]);
}
gcc -g test.c 
gdb a.out 
进入调试界面
set args 10 20 30 40 
show args 
start 程序向下执行一行
run  
quit  

重新改
for (i = 0; i < argc; i++)
{
	printf("argv[%d]: %s \n", i, argv[i]);
}

run 开始执行，如果有断点，停在第一个断点处
start 程序向下执行一行
n 下一步？？

GDB的启动 设置等 第一部分。

显示源代码和断点操作--

显示源代码： 可简写成 l 小写L
用list命令来打印程序的源代码，默认打印10行
list linenum 打印第linenum行的上下文内容 
list funcion 显示函数名为function的函数的源程序
list 显示当前行后面的源程序
list - 显示当前行前面的源程序

一般是打印当前行的上5行和下5行，如果显示函数是上2行和下8行
默认是10行，当然，可以制定显示的范围，使用下面命令可以设置一次显示源程序的行数：
set listsize count: 设置一次显示源代码的行数
show listsize: 查看当前listsize的设置

gdb a.out 
b main 
list   10 行出现
list  又增加10行
list main 只显示主函数也可以
set listsize 20 
list 1 第一行开始
show listsize 

打断点操作：
1.简单断点
break 设置断点 可以简写成b
b 10 设置断点 在源程序第10行 
b func 设置断点 func函数入口处

设置断点 可以设置行号 设置断点 设置函数名

显示断点：
info break 
info b 
i b 
i break 
简写写法多样。

2. 多文件设置断点 ！！！
c++中 多个类 .c 文件 
c++中可以使用class::function / function (type, type)格式来执行函数名 
break filename:linenum 
break filename:function
break class::function/functioni(type,type) 在类的funcion函数入口停住
break namespace::class::function 

gdb a.out 
b main  
run 
n 下一步？
n
n 
quit 

gdb a.out 
run 
直接跑完了 如果不设置断点

条件断点：
一般来说，为断点设置一个条件，使用if，后面紧跟断点条件
设置一个条件断点：
b test.c:8 if Value == 5
条件断点不能停在{}括号行，只能函数体内的语句

gdb a.out 
b test.c:23 if i == 5  
set args 1 2 3 4 5 6 7 
start 执行第一行
run 执行到第一个断点处 
continue 到第一个断点处 停了 
p i 查看此时i的值 是5 

维护断点：
1. delete [range...] 删除指定的断点，简写命令是d
如果不指定断点号，则表示删除所有的断点，range表示断点号的范围 如: 3-7 
比删除更好的一种方法是disable停止点，disable了的停止点，GDB不会删除
当你还需要时，enable即可，好像回收站一样
2. disable [range...] 使指定断点无效，简写dis 
如果什么都不指定，表示disable所有的停止点
3. enable [range...]
如果什么都不指定，表示enable所有的停止点

info break
b 2
b 3 
b 4 
b 5 
info break
d 
提示：删除所有断点
info break 没有断点了

7 b 2
8 b 3 
9 b 4 
10  b 5
info break
你会发现打断编号 第一列 
d 断点编号小-断点编号
d 8-10 

disable 3 禁用这个断点
info break  看到这行变了： Enb N(无法使用)
enbale 3 
info break   Enb Y 启用了

--调试代码
run 运行程序 简写r 
next f10 单步跟踪，函数调用当作一条简单语句执行,n  
step f11 单步跟踪，函数调用进入被调用函数体内，s 
finish 退出进入的函数
until 在一个循环体内单步跟踪时，这个命令可以运行程序直到退出循环体，u
continue 继续运行程序，停在下一个断点的位置，c
quit 退出gdb q 


gdb a.out 
b main 
b fun 
run 停在第一个断点 
n 
n 
n 
continue 停在下一个断点位置 没有断点就执行完毕
quit 

gdb a.out  
b main 
b fun
fun 
continue 到下一个断点了
s 进入函数内部了
n 
n 
n 
until 12 12行

数据查看：
1.查看运行时数据
print 打印变量 字符串 表达式等值 p  
p cout 打印pcout的值

5min 跳了 看不下去了

自动显示：
设置一些变量的显示 当你单步跟踪时 会显示 就像VS中下面
有个监视某变量一样
display 变量名
.. 
info display  
undisplay 编号
disable display 编号
enable display 编号

查看修改变量的值：
ptype width 查看这个变量width的类型
type = int 

p width 打印变量的值 
$4 = 13 

set var width=14 设置变量的值 width是程序的变量名
set var 格式



