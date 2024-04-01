共计9天。
前四天 基础命令和文件操作
后五天 多进程 多线程 进程通信

linux系统作用，向下封装硬件，向上提供操作接口。
Unix家族 -> Linux家族 
Minix仿照BSD的源代码 -> Linux人出了mini内核linux
GNU计划：GNU is not unix 主旨开源，
Emacs编辑系统 BASH shell程序，GCC，GDB等开发工具都是GNU的产品
POSIX标准：定义了OS应该为应用程序提供的接口标准，用来统一UNIX LINUX各分支编程接口，以提高通用性和可移植性。
linux在x86架构上实现了UNIX的全部特性
推荐使用命令，不要使用鼠标，完全可以做到的

linux内核介绍：Kernel 
内核源码网站：http://www.kernel.org 
linux有稳定版和开发版(多用来裁剪然后移植另外硬件)
OpenWRT(Linux内核 + 文件系统) 这是路由器，没有界面，也不需要

linux kernel map 图。
如果是做数据库orical的开发，用Centos
一般的开发就用ubuntu 

Unix/Liniux应用领域：
服务器：Web Ftp DNS 
嵌入式Linux系统：一般都是经过移植或裁剪，能够在计算机系统上运行的OS
桌面应用

Linux目录结构：
windows: 跨盘复制文件很慢，本盘快？改了一个指针
每一个盘符属于一个分区，独立的。
linux没有盘符，都是目录。一切皆文件。

看再安装一个还是怎么搞。那个韩的必须看的。

linux常见目录介绍，熟悉。
cdrom 光驱
dev 设备 -鼠标 键盘等都是文件
etc 系统配置文件 -配置背景 亮度 网卡设置等
home 所有普通用户的家目录 
lib 系统使用的函数库的目录
lib64 6 4 位平台的库函数 
media: 光盘默认挂载点 U盘等等
mnt: 同上 ？
opt 安装其他三方软件就放在这
proc 当内核启动之后才有的文件 此目录的数据都在内存中
/root 系统管理员的家目录 最高权限 慎重
	即使要用也只是授权加sudo即可 
/sbin 超级管理员的可执行命令 
/srv 服务启动之后需要访问的数据目录
/user 应用存放目录
/var 放置系统执行过程中经常变化的文件，如随时更改的日志文件

ctrl + alt + t 快捷打开终端
linux命令解析器
	shell命令解释器
命令解析器，输入命令后，会去调用相关可执行文件
不会命令行，就不会linux系统
提供了大量的命令，利用它有效完成工作：如：磁盘操作、文件存取、目录操作、进程管理、文件权限设定等。
用户 -> 使用者界面shell KDE application
-> 内核kernal -> 硬件
linux系统中提供了好几种不同的命令解释器，如shell(/bin/sh) bash(bin/bash) 一般默认bash作为默认的解释器。
命令查看：
ls /bin/*sh -l 
查看当前默认的解析器：
echo $SHELL
which bash
ls -l /bin/bash 


文件操作 网络使用的命令最多，其他多半没权限

echo $SHELL 当前的默认解析器
ls /bin/*sh -l 
ls -l /bin/bash 

Bash解析器常用快捷键：
tab: 
	补齐命令 tou后面忘记了 按哈tab 
	补齐路径 按2下 什么鬼 是 表示当前匹配多个 按两下切换
	显示当前目录下的所有目录 
clear: 
	清屏 clear  or ctrl + L小写字母
	I l 这两个很像 
中断进程：
	ctrl + c 中断终端 sleep 3000情况下
遍历输入的历史命令：
	从当前位置向上遍历： ctrl + p 
	从当前位置向下遍历： ctrl + n
光标相关操作：
	ctrl + b 光标坐移
	ctrl + f 光标右移
	ctrl + a 移动到头部
	ctrl + e 移动到尾部
字符删除：
	删除光标前边的字符 ctrl + h 或+空格一个
	删除光标后面的字符 ctrl + d 一个
	光标后边的字符即光标覆盖的字符
	删除光标前所有内容 ctrl + u 
	删除光标后所有内容 ctrl + k 

ifconfig 
Linux系统相关快捷键：
图形打开终端方式：三种
alt + f2 
搜索 输入终端 打开 
右击桌面打开终端 

终端相关的快捷键：前提是终端必须选中哈
ctrl + shift + n 新建一个终端 
ctrl + shift + t 在终端里新建一个标签 
ctrl + shift + w 关闭标签页
ctrl + shift + q 关闭窗口 

ctrl + shift + c 复制 
ctrl + shift + v 粘贴 

alt + 1-9 标签之间切换
ctrl + shift + =放大终端字体
ctrl+- 缩小终端字体
ctrl + 0 普通大小
f11 全屏
ctrl + d 关闭当前一个终端
alt + f4 关闭整个终端 
ctrl + shift + f 查找

注意区分 bash 和 这里的终端快捷键。
I l 0 o ; ； 不好区分这几个。

字体推荐使用 DejaVu Sans Mono Book 
编辑-首选项-自定义文字
alt + tab 程序切换
ctrl + alt + backspace 注销
ctrl + alt + f7 回到图形界面 如果不小心进到其他虚拟控制台，可以用这个
ctrl+alt+f2到f6 可以访问6个虚拟控制台

虚拟机最好不要直接删除掉，你可以挂起，。


内建命令 外部命令
外部命令是安装外部软件的命令
外部命令执行时往往需要fork出一个子进程，而内建命令不用。
外部命令是在bash之外额外安装的，通常放在/bin /user/bin /user/sbin ..等 可通过echo $PATCH 查看外部命令的存储路径。
查看命令的类型，是内建还是外部：
type 名称 
出现内建两字 说明是内建命令 没有就是外部命令
冲突时 内建命令为主

linux命令格式：
command [-options] [parameter1] ...
command: 命令名 
[-options] 选项，可用来对命令进行控制，可省略
[parameter1] 传给命令的参数 可0个或多个

命令参数前的：
1. 大多数命令参数前有 - 
ls -a     rm -r dir   SYSTEM V 风格 
2. 有些命令参数前没有横杠都可以 
tar xvf filename 
tar -xvf filename 
ps aux 
ps -aux 
BSD风格
3. 一般格式
-+ 字母 [-r|-p|-l]
 --+ 单词 [--help]

ctrl+shift +上下 可以终端上下滚动

帮助文档：
内建命令help
help + 内建命令 
help pwd
help cd 

外部命令帮助可以：--help 或者 man
长短选项
ls --help 

man 帮助文档
man man 这样两个查看自己
man [选项] 命令名
man设置了快捷键：
	空格键 显示手册的下一屏
	enter 一次滚动手册页的一行
	b 回滚一屏 
	f 前滚一屏
	q 退出man命令
	h 列出所有功能键
	/word 搜索word字符串

man中各个section意义：省略
直接 man printf 是没有的 因为printf是一个库函数
man 3 printf 查看第3章 
man 2 read 看函数的原型
man read 

man -k passwd 只知道包含关键词 passwd 
它这个第几章 区分 还是有点混乱
八章 1-标准命令 2-系统调用 3-库函数
man还设置了功能键 

绝对路径：cd /home/deng
第一个/是根目录  后面的都是分隔符 

相对路径：
cd test 
第一个绝对不是/

cd / 回根目录
cd ~ 回家目录

两个特殊的目录： .   .. 

目录相关的命令：
查看当前目录 + 切换目录 + 新建目录 + 删除目录
pwd cd mkdir rmdir 
pwd [-LP] 打印当前工作目录的名字 是绝对路径哈
help cd 查看帮助cd 

cd . 
cd.. 都是一个目录 ，那肯定是在根目录

cd 后面什么都不接 切换到当前用户的主目录 -当前的家目录
cd ~ 切换到当前用户的主目录
cd . 切换到当前目录
cd .. 切换到上级目录
cd - 可进入上一个进入的目录

man mkdir 查看
mkdir 新建一个空文件夹 无法重名 且有权限
mkdir test (相对路径这里)
mkdir /tmp/test (绝对路径这里)
mkdir d1 d2 d3 创建3个
mkdir dir{1..100} 创建100个 有正则
mkdir "dir{1..100}" 创建一个
mkdir "a b" 创建一个 名字有空格 特殊符号等
mkdir a b 创建目录a和b 
mkdir /tmp/test 根目录..
mkdir -p dir1/dir2/dir3 没有dir1目录加了-p就不会报错了，而是会创建它
tree dir1 查看树形结构目录

ls -a 
ls -l

rmdir 怎么创建就怎么删除
rmdir {a..c}
rmdir a b c 
rmdir -p a/b 先删除a然后删除b 



文件类型：
linux下，一切皆文件。
unix/linux也必须区分文件类型，在unix/linux系统中文件可以没有扩展名

文件类型分类：
通常unix/linux系统中常用的文件类型有7种：
普通文件 
目录文件 特殊的文件
设备文件 /dev目录中存放
管道文件 
	是unix/linux中比较特殊的文件类型，这类文件多用于进程间的通信。
链接文件 
	windows的快捷方式，链接又可以分为软链接(符合链接)和硬链接
	符号链接相当于我们的快捷方式
套接字 

颜色显示：
普通文件：
	白色-普通文件 stdio.h
	绿色-可执行文件 dash date
	红色-压缩文件 tar.gz
蓝色-目录 Documents Downloads
青色-链接文件 stdio
黄色-设备文件 
	block块 字符设备的存取是以字符为单位
	char字符 块设备的存取是以块为单位
	fifo管道
灰色-其他文件

file 文件名或者*   查看文件类型
ls -l /..
-开头 普通文件
d 目录文件
c 字符设备
b 快设备
p 管道文件 pipe
l 符号链接 link 
s 套接字 

文件相关命令：
ls [选项] [文件]
常用参数：
-a 显示指定目录下所有子目录与文件，包括隐藏文件
-l 以列表方式显示文件的详细信息
-h 配合.l 以人性化的方式显示文件大小

ls 默认当前所有文件
ls -a 包含隐藏文件 .开头是隐藏文件
ls -l 以列表方式显示文件的详细信息
ls -lh 文件大小

Linux中隐藏文件以 . 开头。

ls正则查询：通配符
ls -ld linu* 
ls ???.txt 
ls te* te开头的文件
？-匹配一个字符 *-匹配任意多个字符
ls [a-z][a-z][a-z].txt
ls -l [^a-z]*
跳。后面看。

touch命令： 这是文件相关命令，不能是文件夹
man touch 查看文档
touch[选项] 文件
1.如果文件不存在，创建新文件(只能是普通文件，不是文件夹)
2. 如果文件存在，更新文件时间 

touch b.txt 
touch b.txt  文件已存在，更新创建时间
ls -l b.txt  查看创建时间

cp命令
	mkdir test
	pwd 
	ls 
	cp /etc/
	ls 

	cp xxx test/
	tree test 

	touch a b c 
	ls 
	拷贝到当前目录下一个test目录下
	cp a b c test/
	tree test/

rm命令
	rmdir 只能删除空目录 不能删除非空目录
	rm 删除文件
	rm dir 不行
	rm -r dir 可以

mv命令
	移动文件或目录 重命名


跳。--
文件内容查看命令：
cat 无法展示完 如果很多
	cat -n 1.txt 编号
more 只能向下浏览 无法回退 了解吧
less 可自由上下 将文件内容分页显示到终端
head 查看文件的前n行  默认是10行
tail 

du 查看某个目录大小
	du -sh 1.txt 
	stat 1.txt ?
df 检测文件系统的磁盘控件占用和空余情况 可以显示所有文件系统。。。

-------
查找相关命令 -重点

1.找文档中的内容 2.找目录中的文件
find命令
通常用来在特定的目录下搜索符合条件的文件，也可以用来搜索特定用户属主的文件。
1. 按文件名查询：使用参数-name 
find + 路径 + -name + "文件名"
find /home -name "a.txt"
2. 按文件大小查询：使用参数 -size
find + 路径 + -size + 范围 
find ./ size +100k 大于100K
3. 按文件类型查询 使用参数 -type  7类文件类型
find + 路径 + -type + 类型
find ./ -type d 
find ./ -type c 查询是字符设备
find ./ -type b 查询是块设备
find ./ -type s 查询是套接字
find ./ -type p 查询是管道

----2-------

grep命令
linux中grep命令是一种强大的文本搜索工具，允许对文本文件进行模式查找，如果找到匹配模式，打印包含是模式的所有行。
grep [-选项] '搜索内容串' 文件名
-v -n -i 具体省略。
场景：某个头文件中是否包含一个函数？
跳
查文本里的文本
grep "root" /etc/passwd
有"root"字符的行都会打印

grep -r "u_char" ./ 
这个就是递归查看当前目录下 所有出现字符u_char的位置
默认没有光亮，自己加 -color

linux命令设计原则--单一功能原则
管道：把一个命令的输出作为另外一个命令的输入
ifconfig | grep "333"
然后就是可以把含有字符"333"的行过滤出来了 

ctrl + alt + 左右 切多桌面

28课
压缩包管理
tar 工具 这不叫解压 压缩
案例 二次看视频
ls -ld 文件名 可以看到文件的权限相关属性
归档文件

查看归档文件内容 再确定是否要解压

压缩
哈夫曼编码
gizp or bzip2
gzip:  gzip 1.txt 默认压缩 不保留原文本
不能压缩目录 man gzip 
但是工作中肯定压缩目录，咋办？
先打包后压缩 

gzip -d a.gz 不保留原文件 解压 
gunzip a.gz 

目录一定要是先打包后压缩
tar -cvf a.tar xx/
gzip a.tar 

搞成一条命令：
tar -czvf sysctl.tar.gz xx/

查看文件类型 file ..
查看文件目录树 tree ..

解压到某个目录：
tar -xzvf a.tar.gz -C /b 解压到b目录

tar + gzip 一般是结合使用

跳过29 30 
------权限管理----
不要使用root权限 工作中 加sudo就可以了

修改权限：chmod 
权限是 rwx 读写执行
ls -l a 看当前用户堆a文件的权限
r__ 没有权限就用_替代 

chmod o+w a 追加写的权限
chmod g-w a 所属组的写权限撤销
chmod o=x a 赋值权限

需求：文件所属者读写，文件所属组读，文件其他读？如何设置
chmod u=rw,g=r,o=r a  不要加空格
ls -l a 
-rw-r--r-- ..

rwx
111 -> 7 满格权限就是7 
rw_ 110 -> 6 
r-- 100 -> 4
-w- 010 -> 2
--x 001 -> 1
r-x 101 -> 5
-wx 011 -> 3 

chmod 0754 a 和上面效果一样
ls -l a 

ls -l * 
使用数字较为专业

chown 文件所属者
man chown 
ls -l a
chown root a
sudo chown root a
ls -l a

只改文件所属组
sudo chown :root a
ls -l a

chgrp 有了上面的这里可以不要了 为了兼容以前的系统

---软件安装和卸载 
新版本都用 apt 不用apt-get了
sudo apt install tree
sudo apt remove tree
sudo apt update 

软件包安装
离弦的包安装 放到ubuntu中 如何安装命令呢
nautilus什么东西？
ls 
sudo dpkg -i 文件包(比如tree)
which tree

sudo dpkg -r tree 卸载

在ubuntu下安装文件位 deb格式
还有二进制安装 源码文件 后面说了。

重定向：
大量的控制台输出，我们吧它搞到一个文件里，方便我们看
标配输出是 控制台输出，我们需要重定向到文件里去
ls /etc/xxx
ls /etc/xxx > test.txt 
ls
cat test.txt 就打印了之前控制台输出的内容

重定向回覆盖原来的内容，
ls /etc/xx > test.txt 
cat test.txt 之前的没了 可以追加吗？

ls /etc/xx >> test.txt 
cat test.txt

>> 追加   > 覆盖

linux吧错误输入 重定向到 黑洞文件-就是一个字符设备
进去了 就永远不见了
&> 吧标准输出和标准错误输出 重定向

其他命令：
tree 

in 创建链接文件
类似windows下的快捷方式
软链接 硬链接 
in a a_hard  
sudo chown deng:deng a
in a a_hard
ls -a a a_hard 
stat a a_hard 文件相关的属性

改变文件内容
硬链接访问也会改变 就会指针一样 
硬链接不能是目录

软硬区别？
符号链接-软连接 存储的是路径 占个字符

应用场景：版本库兼容不同版本 ？


----2节课-----------------


