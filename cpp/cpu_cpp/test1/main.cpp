#include <iostream>

int main()
{
	//CPU角度看：
	// 1.main函数 
	// 和普通函数没有区别，看了汇编代码。main是很多函数的默认起点，但是不是绝对，可以设置的。
	//任何函数都可以被设置成函数起点。
	// 2.变量
	//int a;
	//void write()
	//{
	//	a = 1;    mov     DWORD PTR a[rip], 1 
	//}
	// mov     DWORD PTR a[rip], 1
	// 把1给a所代表的内存里，[rip]即内存地址，方括号里面的值
	//由于指令集的原因，CPU不可能直接访问内存。只能通过寄存器配合[]间接访问内存
	//根据指令手册：rip存放着下一条指令的地址
	//局部变量 也叫栈变量 
	// 3.i++ ++i 
	// 通常没有差异，但是出现赋值的时候，前加价快一点点。
	// 如果只是一个简单的int类型变量没有特别大差异，如果是一个类对象，差异就大了。
	// 就会构建一个临时对象，这就大了。对象的首先前加价。
	//void func_1 ()
	//{
	//	int i = 1;
	//	int a = ++i;     add     DWORD PTR [rbp-4], 1
	//}

	//void func_2 ()
	//{
	//	int i = 1;
	//	int a = i++;	mov     eax, DWORD PTR [rbp-4]
	//					lea     edx, [rax+1]     1.创建：临时变量(edx)
	//					DWORD PTR [rbp-4], edx   2.拷贝：临时变量给：变量i
	//				为何要构建临时变量？原来后佳佳的返回值是2，是右值型的
	//				右值的临时变量只能给别人赋值，而且，程序员还看不见。
	//				前加价是左值的，意味着可以直接赋值。一步到位。
	// 比如：
	//  int i = 1;
	//  ++i = 2;  可以
	//  i++ = 2； 报错 
	//}
	//4.i++奇葩
	// ++i + ++i = 6 ?
	/*1. i++ and ++i are functions with returns 
	2. i++ return constant value 
	3. ++i return the reference / pointer of variaable i 
		前加价的返回值不是具体的数，而是变量i的引用-指针。所以，他的值会滞后到加减才能确定

	i++ + i++ = 3 
	i++: i = 1 + 1 = 2 return: 1
	i++: i = 2 + 1 = 3 return: 2

	i++ + ++i = 4
	i++: i = 1 + 1 = 2 return: 1
	++i: i = 2 + 1 = 3 return: int& r = i; 返回值是i的引用？
	1 + r = 1 + 3 = 4;   所以，他的值会滞后到加减才能确定

	++i + ++i = 
	++i: i = 1 + 1 = 2 return: int& r1 = i
	++i: i = 2 + 1 = 3 return: int&2 r2 = i
	所以，他的值会滞后到加减才能确定
	r1 + r2 = 3 + 3 = 6
	都是从左往右的函数调用和加法计算而已。

	++i + ++i + ++i =  10
	第一个和第二个会计算出结果，结果和第三个计算
	++i + ++i = 6 上面算过了
	step: i = 3 return 6
	step: i = 3 + 1 = 4 return: int& r = i
	step:6 + 4 = 6 + 4 = 10

	i += ++i + ++i + ++i 
	先算+=右边的，上面题算过了
	step1: i = 4 return: 10
	step2: i = 4 + 10 = 14

	5. this指针
	class CTest
	{
		public:
		CTest* member_func()
		{
			return this;
		}
	};

	long normal_func (long hidden_this)
	{
		return hidden_this;
	}
	汇编：两者一摸一样
	    push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     rax, QWORD PTR [rbp-8]
        pop     rbp
        ret
	所以，成员函数，跟普通函数是完全等价的。
	this指针就是这个普通函数的参数。
	this指针是每一个成员函数必备的默认参数。语法隐藏了而已。
	int main ()
	{
		CTest test;

		test.member_func();

		normal_func((long)&test);
	}
	汇编：一样的二者。
	    lea     rax, [rbp-1]
        mov     rdi, rax
        call    CTest::member_func()

        lea     rax, [rbp-1]
        mov     rdi, rax
        call    normal_func(long)
	从CPU的角度看，输入this指针，就是输入test对象的地址。normal_func((long)&test); 这行代码。
	当对象调用成员函数时，都会把自己的地址当作this指针输入给成员函数。

	6. 构造函数
	class A
	{
		public:
		int a;

		void func ()
		{
			this->a = 1;
		}

		A()
		{
			a = 1;
		}
	};
	汇编：一样的 甚至this都有夹带的 没有继承情况下 一样的
	    push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     rax, QWORD PTR [rbp-8]
        mov     DWORD PTR [rax], 1
        nop
        pop     rbp
        ret

	class B : public A   加个继承再对比
	{
		public:
		B()
		{
			a = 1;
		}
	};
	汇编：多了三行
	    mov     rax, QWORD PTR [rbp-8]
        mov     rdi, rax
        call    A::A() [base object constructor]
	看过上一集this就知道，这里前两行指令是在输入隐形参数。
	第三条指令是在调用A的构造函数 看A的汇编。这也就是为什么派生类的构造函数总会调用基类构造的原因
	其实就是一个普通函数调用，用语法解释起来就是非常拗口。

	继续增加难度：改成虚函数
	class A
	{
		public:
		int a;

		virtual void func () 虚函数改成
		{
			this->a = 1;
		}

		A()
		{
			a = 1;
		}
	};
	汇编：此时发现A B的构造函数都会多出3条指令。
	A: B 一样的加的3条：
	        mov     edx, OFFSET FLAT:vtable for A+16
        mov     rax, QWORD PTR [rbp-8]
        mov     QWORD PTR [rax], rdx
	B:
	        mov     edx, OFFSET FLAT:vtable for B+16
        mov     rax, QWORD PTR [rbp-8]
        mov     QWORD PTR [rax], rdx
	从字面意思看，是在记录虚函数表的地址。
	A的构造函数只会记录A的虚函数表地址(地址存在this指向的位置)
	B同理。从而保证A B实例在调用虚函数的时候，能区分你我。
	这就是动态绑定。UP对动态绑定无感。
	所有的虚函数绑定早在构造函数的时候就安排好了。
	虚函数表样子：汇编
	vtable for B:
        .quad   0
        .quad   typeinfo for B
        .quad   A::func()
	vtable for A:
			.quad   0
			.quad   typeinfo for A
			.quad   A::func()

	int main ()
	{
		A a;
		a.func();
		 B b;
	}


	7. 虚函数
	class A
	{
		public:
		int a;
		int func ()
		{
			return this->a;
		}

		virtual int vfunc_1 ()
		{
			return a;
		}
	}test;

	void call_func (A* a)
	{
		a->func();
	}

	void call_func_1(A* a)
	{
		a->vfunc_1();
	}
	汇编：
	虚函数和普通函数func一样的。
	调用的时候看看有什么不同。唯一的区别是：调用普通函数时，在编译的时候就确定了。
	即：call 指令的目标地址在编译阶段。 call    A::func()  即：静态绑定
	而调用虚函数时候，call指令只能根据rdx寄存器的值来确定函数的位置，即动态绑定 。
	动态绑定，也不过是3条指令而已。
		mov     rax, QWORD PTR [rbp-8]
        mov     rax, QWORD PTR [rax]
        mov     rdx, QWORD PTR [rax]
	有兴趣可以细品这三条指令。等价下面的C代码：
	/ 获取隐藏的成员变量 V 的值(虚函数表地址):  前两条指令
	long vf_table_address = (*(long*)a);

	/ 虚函数1 vfunc_1 的地址，位于虚函数表的第一项  第三条指令
	long virtual_func_1_address = *(long*)vf_table_address;

	/ 将以上2行代码 合并成一行，精简汇编指令
	return *(long*)(*(long*)a);

	总结：
	当类A有虚函数时候，就会偷偷生成一个隐藏成员变量 
	class A
		void* V (V存放着虚函数表的地址，根据偏移，就可以得到要执行的vfunc_1的地址，将其存在
				寄存器 rdx 里面。随后一个call rdx 指令，就调用了。) 
		int a 

	类会夹带this指针隐藏参数还可以接受的话，我说类还会夹带隐藏变量V，你能接收码？
	那在哪里给它们初始化呢？构造函数，上一集。A的构造函数中，把V初始化成类A的虚函数表地址。

	尽管我没有写构造函数，编译器还是给我生成了一个构造函数。
	A::A() [base object constructor]:
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     edx, OFFSET FLAT:vtable for A+16  ！！！
        mov     rax, QWORD PTR [rbp-8]
        mov     QWORD PTR [rax], rdx
        nop
        pop     rbp
        ret
	它一定、必须要帮我完成隐藏变量V 的初始化。

	当然A有派生类B的化：
	隐藏变量V会在B的构造函数中，被初始化为B的虚函数表地址，从而保证A B的虚函数相互独立。

	但是考虑到派生类B的构造函数，还会调用基类A的构造函数，因此变量V，一会会被初始化成类A的
	虚函数表，一会会被初始化成类B的虚函数表，为了避免晕头，往往会禁止在构造函数里面调用虚函数

	总结：
	1. 虚函数和普通函数没有区别
	2. 虚函数的调用，需要借助类对象的隐藏变量，V来完成。隐藏变量V 会在构造函数中被初始化
	成虚函数表的内存地址。
	最后，调用任何虚函数的套路都是一样的，唯一的区别是要 根据它们在虚函数表的位置。
	因为虚函数出现，函数指针使用率大大降低了。


	8. 多态
	class A
	{
		public:
		int x;
		int y;
	};

	class B : public A
	{
		public:
		int z;
	};

	void func_1 (B& b)
	{
		A* p = &b;
	}

	void func_2 (A& a)
	{
		B* p = (B*)&a;
	}
	汇编：
	func_1(B&):
			push    rbp
			mov     rbp, rsp
			mov     QWORD PTR [rbp-24], rdi
			mov     rax, QWORD PTR [rbp-24]
			mov     QWORD PTR [rbp-8], rax
			nop
			pop     rbp
			ret
	func_2(A&):
			push    rbp
			mov     rbp, rsp
			mov     QWORD PTR [rbp-24], rdi
			mov     rax, QWORD PTR [rbp-24]
			mov     QWORD PTR [rbp-8], rax
			nop
			pop     rbp
			ret
	其实，CPU对多态是无感的。
	类型转换，往往都是不安全的，唯独给多态开了个特例。

	函数func_1 A*p = &b; 把派生类的对象 不正是降级 成基类A的对象在 使用吗！
	这就是常说的 代码复用。
	不能升级使用，为什么？因为没有给 int z 预留空间的，一旦访问就会越界。
	class A: int y     int x      void* V = vftable_A
	class B: int y     int x      void* V = vftable_A   int z 

	如果仅仅是复用了基类的共性，没有体现自己的特性，就没意思了。答案是：虚函数。
	如果要访问类B的特有变量，就可以搞一个虚函数。类A就此虚函数返回一个-1即可。

	多态：调用相同的函数，却会根据对象的实际类型，执行不同函数的版本。

	多态不是C++的专利，很多语言都有。仅仅用CPU看，片面的。

	如果按照多态的设计，著需要一个函数，就可以绘制所有的界面元素。
	不用多态，就可能为每一个界面编写各自的绘制函数。

	9. 指针变量 数组指针 野指针
	指针变量：也是变量，存的是指针
	共性：指针变量 普通变量：就读写而言，汇编没有区别
	{
		int a = 1;
		int* p = &a;
		*p = 2;
	}
	变量是内存地址的别名。
	变量a p 若a:0x1234  p:0x1238 这里假设32位机
	0x1234 1
	0x1238 0x1234 
	
	*p操作分两步：1.去除指针变量p的值 并作为目标地址 也就是：读取地址为0x1238处的内存值0x1234
	2. 把2写入到 地址为0x1234的内存里面。

	指针变量初值很重要。
	普通变量的值往往用来做 数值计算。
	指针变量的值，往往用来：定位内存。

	指针变量做加运算，也是在做地址偏移。

	
	10. 指针
	普通变量也能做指针操作，只要知道变量的地址。开销更小。
	普通变量能像指针变量那样，可以* -> 操作吗？
	int a = 0;

	void func_1 ()
	{
		int*p = &a;
		*p = 1;
	}

	void func_2 ()
	{
		*(int*)&a = 1;
	}

	void func_3 ()
	{
		a = 1;
	}
	汇编：
	a:
        .zero   4
	func_1():
			push    rbp
			mov     rbp, rsp
			mov     QWORD PTR [rbp-8], OFFSET FLAT:a
			mov     rax, QWORD PTR [rbp-8]
			mov     DWORD PTR [rax], 1
			nop
			pop     rbp
			ret
	func_2():
			push    rbp
			mov     rbp, rsp
			mov     DWORD PTR a[rip], 1
			nop
			pop     rbp
			ret

	func_3 func_2 汇编指令一样的。也就是：你最熟悉的变量读写，都等同于对变量地址的指针*操作
	正如变量e定义所言，变量不过是：内存地址的别名。
	func_2函数 仅仅一条指令就完成了赋值。上面3条。

	同样的道理，不借助指针变量，我们也可以通过指针->操作对类的成员变量赋值。
	class A
	{
		public:
		int x;
	} a;

	void func_c1()
	{
		a.x = 1;
	}

	void func_c2()
	{
		(&a)->x = 1;
	}
	汇编：
	a:
        .zero   4
	func_c1():
			push    rbp
			mov     rbp, rsp
			mov     DWORD PTR a[rip], 1
			nop
			pop     rbp
			ret
	func_c2():
			push    rbp
			mov     rbp, rsp
			mov     DWORD PTR a[rip], 1
			nop
			pop     rbp
			ret

	总结；计算机的世界，万物都有地址。内存。
	除了内存管理单元MMU，其他地方都可以乱来。
	黑客大神，一个指针 。。


	11. 参数传递：传值 传指针 传引用
	void func_1 (int x, int y, int z)
	{
		x = 0;
	}

	void func_2 (int* x, int* y, int* z)
	{
		*x = 0;
	}

	int a = 1;
	int b = 2;
	int c = 3;

	int main ()
	{
		func_1(1,2,3);
    
		func_2(&a, &b, &c);
	}
	汇编：截取部分
	        mov     DWORD PTR [rbp-4], edi
        mov     DWORD PTR [rbp-8], esi
        mov     DWORD PTR [rbp-12], edx
		传值 1 2 3 分别存入 edi esi edx 

		        mov     QWORD PTR [rbp-8], rdi
        mov     QWORD PTR [rbp-16], rsi
        mov     QWORD PTR [rbp-24], rdx
		传指针 把0x.. 0x.. 0x..分别给 rdi rsi rdx 

		无论是传值还是传指针，还是把参数给寄存器。CPU眼里没有区别。
		一个是复制品(不影响实参)，一个是内存地址(影响实参)。
		若传递对象，寄存器就不行了，会用堆栈。

		至于传引用，本质还是传指针。
		void func_1 (int& x, int& y, int& z)
		{
			x = 0;
		}

		void func_2 (int* x, int* y, int* z)
		{
			*x = 0;
		}

		int a = 1;
		int b = 2;
		int c = 3;

		int main ()
		{
			func_1(a,b,c);

			func_2(&a, &b, &c);
		}
		汇编：部分main这 调用的部分
		main:
        push    rbp
        mov     rbp, rsp
				mov     edx, OFFSET FLAT:c
				mov     esi, OFFSET FLAT:b
				mov     edi, OFFSET FLAT:a
        call    func_1(int&, int&, int&)

				mov     edx, OFFSET FLAT:c
				mov     esi, OFFSET FLAT:b
				mov     edi, OFFSET FLAT:a
        call    func_2(int*, int*, int*)
        mov     eax, 0
        pop     rbp
        ret
		两者一样的。有兴趣可以对比汇编。

	12. 指针 放弃？
	指针：TCP/IP的应用。驱动硬件。控制机械臂。无穷变身。
	指针可以无代价的变换成：任意数据类型。
	被大量用在：链表和OS中。
	避免了拷贝工作。
	访问硬件的寄存器。
	其他编程语言无法匹敌的。

	眼中有代码，心中有内存。
	OS中大量应用。

	13. 数组 1D/2D/3D
	void func ()
	{
		int a[8];
		a[0] = 1;
		a[1] = 2;
		a[2] = 2;
		a[3] = 2;
		a[4] = 2;
		a[5] = 2;
		a[6] = 2;
		a[7] = 2;
	}
	汇编：间隔是4个字节 

	void func1 (int a[2])
	{
		a[0] = 1;
		a[1] = 2;
	}

	void func2 (int* a)
	{
		*a = 1;
		*(a + 1) = 2;
	}
	汇编：一摸一样 这就有意思了
	编译器不会像普通变量那样，为你在堆栈中构建一个数组变量
	而是，简单的传递一个数组的内存首地址，并存放在一个临时的指针变量里面。
	而数组读写，则等价于指针的*操作
	万物皆是指针。数组尤其。
	func1(int*):
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     rax, QWORD PTR [rbp-8]
        mov     DWORD PTR [rax], 1
        mov     rax, QWORD PTR [rbp-8]
        add     rax, 4
        mov     DWORD PTR [rax], 2
        nop
        pop     rbp
        ret
func2(int*):
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        mov     rax, QWORD PTR [rbp-8]
        mov     DWORD PTR [rax], 1
        mov     rax, QWORD PTR [rbp-8]
        add     rax, 4
        mov     DWORD PTR [rax], 2
        nop
        pop     rbp
        ret

	void func(int* array) 我们要习惯这种：传递指针的形式
	为了防止越界，会传一个数组长度。
	CPU眼里，都是一维数组。一段连续的一维内存。索引的方式不同，使用场景不同而已


	14. 数组越界 





	18. 进程 线程 MMU系列
	.c文件 vscode写的
	int a = 1;
	int main ()
	{ printf("address: 0x%p, value: %d", &a, a);
	  sleep(1000000);
	}
	两个进程中运行。
	然后发现，无论是哪个进程，输出的地址都是一样的。但是a的值却不一样。
	难道同一个内存地址里面，既能存放1，又能存放0？？
	这是因为 CPU的内存管理单元：MMU 
	虚拟内存 p1: a 0x...01  p2: a: 0x...01
	然后通过MMU 映射到 物理内存 物理内存则是两个不同的物理地址了
	这就是进程的空间独立性。
	井底之蛙，MMU就是束缚这些青蛙的，不知道真实的物理内存空间。只知道一个进程空间。
	那没有MMU可以吗？那就是线程了。
	有MMU，是进程。
	有了MMU，才有进程的，才真正落地。没有MMU，只有线程的概念
	没有MMU,就没有办法实现内存空间的隔离。也就无法实现进程要求的空间独立性。
	至于进程中的多线程，就好理解，一堆青蛙，放在一个井里。都认为自己有一个天空
	因为，这些线程都处于一个进程空间中，大家可以相互访问，很便利，但是不安全，
	所以，网络服务器一般使用多进程，很少使用多线程。
	所以，进程 线程不仅仅是一个软件设计的问题，硬件问题，以后讨论进程 线程 问有 MMU吗？

	19. 内存映射 地址映射 页表 MMU 
	MMU 用一个地址映射表就可以实现，如果是一个物理地址映射1个，那按照一个地址4个字节
	如果内存是1G字节，地址映射表就需要1G行，光存储地址映射表就要4个G，即使把整个内存用上，
	还倒欠3个G，8-1-4=3 解决？内存分页
	分页是让表1行为1段，4K字节的连续内存，建立：映射关系。而这连续的4KB内存快也就是页。
	这时，我们也称这个地址映射表为：页表。
	此时页表的存储开销：1G的内存可以被分成：256K个页，(1024Mb/4)?
	所以，页表的行数也是：256K。整张页表占用的开销就是 1MB .相比第一种方法内存开销大大缩小了。
	现在为什么要分页了？
	虚拟地址到物理地址的转化？ 
	0x00003 005 32位的虚拟地址 高20位表示该虚拟地址所在的虚拟内存页信息
	值是3，就是让MMU查看页表的第3行的值(起始行：第0行) 也就是0x8000 3000 
	它就是虚拟内存页 对应的物理内存页 的起始地址
	让我进入这个内存页看看，内存页有4KB，那对应的是哪个字节呢？
	是看虚拟地址的低12位。正好可以表示4K个自然数。
	用来做内存页的内部索引刚刚好。
	这里是5，所以就是对应物理地址的5 
	
	整个过程由MMU自动完成，CPU全程无感。
	每个进程都有一张自己的页表。
	若页表不同，则它们的进程空间是：被隔离的。
	若页表相同，或者部分相同，则是在做进程间的内存共享。
	而线程，没有独立的页表。它们共享同一个进程的页表。
	所以，线程之间天生就可以内存共享。
	分页，不仅对于物理地址，也针对于虚拟地址。
	能有效减少地址映射表的体量。
	页表里的值，不仅可以是真实物理地址，也可以是硬盘上的扇区信息。这样在内存不够用的时候，
	也可以用硬盘来补位。
	夸张的说，虚拟内存，就是为了实现这个功能而生的。

	当然，很多程序，都不会用尽全部的内存，但一级页表，却为整个内存，建立映射
	是在有点浪费。为了按需分配，现代OS，往往会引进二级页表。

	20. 虚拟内存
	int main ()
	{ int a = 0;
		printf("%p" &a);
	}
	虚拟内存就是在物理内存的基础上，为每一个进程营造一个更加庞大的内存。
	这个虚拟内存的大小 由CPU的位数决定。
	CPU能寻址多少位，虚拟内存就有多大。
	32位的CPU，虚拟内存的空间是：4GB
	64位则是，4GB * 4GB
	从此后，CPU都会在这个虚拟内存中进行读写操作。
	中间MMU，会进行虚拟内存映射到物理内存，中间是无感的，不影响效率。
	好处：1.简化程序，如果用真实物理地址，那么这个地址必须确保在用的时候 不能被占用，
	而虚拟内存就不用担心这个问题，最后映射到哪个物理地址，随便。
	为程序加载提供了便利性。
	再运行程序，又会生成一个虚拟地址，虽然两者一样，但是实际上是会映射到不同的物理内存的。
	即使进程A奔溃，也不会影响到B。
	并且A不能非法探测其他进程的内存。提供了进程的安全性。
	3.有效的利用资源。比如，电脑的字体，都是共享的。
	MMU会映射到同一字体内存中。
	但是如果要改下，则需要自己进程中拷贝一份字体了，这叫copy on write
	4.以小博大。虚拟列表与物理列表一一对应，此时，如果还需要申请一个内存页，？
	为了让程序运行下去，OS会通过一定的算法，选择将某一个内存页，暂时转移到硬盘上，
	同时更新一下对应的页表信息。记录一下内存也所在的：硬盘扇区号码。这样就临时腾出了一个空间的
	内存页。更新一下页表，完成内存映射后。就可以返回给程序使用了。
	那如果程序需要读取，刚才转移到硬盘上的内存页，？
	 还是上面老办法。

	 但是，之前机械硬盘，效率慢，诟病，不如不用这个。
	 直到现在 固态硬盘发展，SWAP功能才打开。
	 虚拟内存是OS和硬件MMU的结合体。为了不损失效率，往往有由MMU来做虚拟内存到物理内存的
	 地址翻译工作。
	 进程安全性。
	 不是所有的计算机系统都需要虚拟内存。

	 21. heap stack
	 这是值程序运行所必备的堆和堆栈，不是数据结构中的堆栈。
	 虽然原理相同，但是使用场景不一样的。
	 定义一个最简单的函数：
	 int main () {}
	 经过编译器编译后，生成的可执行程序a.out 双击运行
	 OS将a.out中唯一的函数main，加载到内存后，尽管，我们没有定义任何变量，
	 也没有进行任何函数调用，无论程序需要与否，OS会附送一段内存块给我们，
	 这就是堆栈。
	 当然，不大，有几十K的，几十MB的，几M的，OS决定。
	 这个堆栈，未来将承载着函数返回地址、提供临时变量的内存空间等职责。
	 所以，只要我们使用函数，这个堆栈就必须存在。他是函数运行的前提。
	 此时，创建一个线程B 
	 我们也要为B提供，同等大小的内存块，用来做线程B的堆栈。
	 从此之后，主线程A和线程B，就可以独立运行了。
	 增加难度，A B同时调用func()?执行完后，怎么知道返回A B?
	 其实，它们的返回地址分别存储在：线程A和线程B的堆栈里面。不会相互干扰。
	 使用的时候都是无感的。
	 每次函数调用，都是在申请内存，每次函数返回，都是在释放堆栈内存。
	 所有这些操作，只需要简单移动一下栈顶指针。也就是改变CPU寄存器rsp的值。
	 函数也不知道有多少线程调用它，所以，谁调用它，它就操作哪个线程的堆栈。

	 堆 
	 也是OS附送的， 空间大，存放超大数据，
	 使用非常明确，程序员通过malloc calloc realloc函数，
	 或者new申请内存，手动释放内存
	 Unix Linux前身居然还有个 minix 。
	 堆中，使用 内存碎片。

	 22. 竞争 线程切换 上下文
	 关中断，但是对系统影响太大，实际中，我们会选择，加锁。
	 使用互斥锁，他会让，不符合条件的线程放弃执行。
	 并进入，类似休眠的等待状态。
	 解决竞争： 就是加锁。

	 23. 线程切换 上下文 线程调度
	 时钟中断，线程切换。
	 时钟中断，回到内核代码(kernel)，内核将当前的CPU上下文，保存到当前线程2所在的内存颗粒上
	 调度器决定让线程1继续运行。
	 一个完整的上下文保存 恢复 和切换的过程就完成了。
	 保存和恢复上下文，不过是在保存和恢复，CPU的寄存器
	 根据被打断的：程序主体和时机的不同，还吧上下文细分成：
	 线程上下文 进程上下文 中断上下文
	 都是一样的配方，一样的味道，虽然名称多。

	 24. 线程互斥 同步 mutex semaphore
	 锁，因何而来？即使最简单的代码也会产生竞争问题。
	 int sum = 0;
	 void func() sum++;
	 void thread_1() {func()}
	 void thread_2() {func()}
	调用两次func 变量值sum是多少？
	极可能是2，也可能是1.
	演示。sum++不是原子操作，由3条汇编指令组成。
	第一次的++还没有存储，第二次的++就来了。
	这导致第一次的++结果不能被 第二次的++运算所用。
	所以，尽管执行了两次，依然是1.
	
	举例，红路灯，就是熟悉的mutex，加锁，解锁的API。
	代码就是临界区。

	若放开2个线程执行，但线程1 2一直没有搞完，线程3无法执行，就是死锁。
	红路灯闸机就是 semaphore的wait api 和 post api 

	mutex 本质就是semaphore ，只不过可用的共享资源上线是1而已。从而变相的实现了互斥。
	加锁操作，会让当前线程，消耗1份共享资源。但若资源枯竭，当前线程只能就地休眠。
	死锁，优先级就是这个环节，一定要慎重。
	解锁操作，释放资源，唤醒等待中的线程。

	锁，通过线程主动放弃运行机会的方法，来协调多线程对公路共享资源的竞争，
	实现线程之间的协调，就是说的同步。

	25. template 模板
	模板是编译器根据我们提供的脚本，自动补齐代码，CPU是无感的。
	编译器 补齐的代码 程序员无法看到

	26. 左值 右值 
	i = i + 1
	左边的变量i是左值的，用于写操作，可以存储数据
	右边的变量i是右值的，用于读操作，读到的数据存在在一个看不见的临时变量里
	代码：
	int i = 0;
	void func () { i = i + 1; }
	看汇编：

	左值可以降级成右值使用，但是右值不能升级成左值。
	注意：变量的后佳佳是右值的。

	27. 函数指针 
	typedef void(*foo)(int);
	void test (int a) {}
	void func_1()
	{ foo func = &test;  func(1);

	void func_2() 
	{ long a = 0x401106;   ((foo)a)(1)
	汇编： 一样的。所以我们可以确定，函数干的是同一件事。

	0x401106 是函数test的内存首地址。
	吧函数指针叫做函数类型的变量，更加清晰

	万物皆可指针。











	*/

	/*
		双重指针
		char *a[] = {"abc", "def", "hij"};
		char **p = a;

		这三个字符串，并不是保存在函数func的堆栈里面。相反，它们保存在一个块 称为
		数据段的内存块里面。

		Stack
		a[0]= 0x000001
		a[1]= 0x000005
		a[2]= 0x000009

	 	  a  b c     d ...       h i j 
		0x000001 0x000005 0x000009
		
		访问hij 的i ?
		printf("%c", *(char*)(a[2]+1));
		a[2][1]
		p[2][1]   数组和指针在很多时候是可以相互替代的

		p: 0x000001 数组a的首地址
		p + 2 到a[2]所在的内存地址了这个地址存这字符串第三个的地址 所以*解引用 *(a + 2) 的首地址
		偏移一个字节即可 *(p + 2) + 1 然后拿到这个i的地址了 最后做*解引用即可
		*(*(p + 2) + 1)

		我们可以读，不要修。只读的。
		把内存图画出来，答案很多。
	*/



	return 0;
}