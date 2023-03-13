# 数据结构-c语言版本

## (一) 数据结构介绍

### 1. 数据结构三要素

#### 1.1. 普通意义

 一个数组、一个结构体、一个单链表，就是数据结构。

#### 1.2. 必须记住的

1. 数据的逻辑关系和数据的存储结构之间的关系。
2. 当我们的业务需要数据处理的时候，如何用C语言完成。
3. 如何存数据，如何存这些数据的关系。
4. 如何取这些数据，如何用这些数据进行运算。
5. 由于计算机硬件的原因，它的存储器是连续的存储单元，因此，我们需要设计一系列的方法，让非线性的数据元素可以在计算机中存储。

### 2. 数据结构难学

1. 数据结构与算法是一门数学、软件、计算机硬件交叉的学科。
2. 数据结构和算法最核心的问题：计算机中内存分布与组织、在这些内存空间中数据如何操作的问题。
3. 刻画实际问题中信息及其信息关联，如何存储，如何运算的问题。

### 3. 软件开发认识

1. 程序开发，核心是实现我们的业务需求，希望计算机自动完成一系列复杂任务，并且自动化程序越高，程序的价值越大。->由此引出自动化概念。
2. 自动化，用一条一条的语句执行过程按照预设的目的，来操作计算机完成信息的维护。这也是数据结构的核心问题：我们要思考什么能够被自动化，什么才能够有效的自动化。->沿着这条思路我们想到了把实际的问题变成计算机求解。->我们会思考如何变呢？
3. 对问题进行定量分析，提取功能要素，提取信息要素。信息与功能的建立。问题模型的建立。其中对于数据的分析，就是要解决，如何把数据存入计算机并进行处理。这便是计算思维。->提供把输入存入计算机，就会联想到程序设计。
4. 用变量、数组、结构体等等结构，去完成信息的描述，信息的记录，信息的关系的维护。语句的组织是函数，函数的关联就是信息流动的关联。函数的语句组合就是算法。而数据结构就是这一系列的组合以及附加在这些组合的关系。

## (二) 数组顺序表

### 原始模板

```c
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int ElemType; // 假定线性表的元素类型是整型
#define LIST_SIZE 1024 // 假定我们的线性表长度是1024
#define TRUE 1
#define FALSE 0

typedef struct 
{
	ElemType data[LIST_SIZE];
  	int last; // 指向最后一个结点的位置
}SequenList;
SequenList* IPtr;

// ... 后续所有封装的代码都放在此位置 main上方
int main ()
{
	return 0;
}
```



### 初始化

```c
SequenList* InitSeq ()
{
	SequenList* pList = NULL;
  	pList = (SequenList*)malloc(sizeof(SequenList));
  	if ( pList != NULL )
    {
      pList->last = 0;
      return pList;
    }
}
```



### 求长度

```c
int GetSizeSeq (SequenList* pList)
{
  return pList->last;
}
```



### 取元素(给位置)

```c
返回值：TURE FALSE
pos这里是下标，正常来说应该是位序 [0, pLlist->last-1]
int GetElemSqList (SequenList* pList, int pos, ElemType* e)
{
  if ( pos<0 || pos>pList->last-1 )
  {
	return FALSE;
  }
  if ( pList->last <= 0 )
  {
	return FALSE;
  }
  
  *e = pList->data[pos];
  return TRUE;
}
```



### 查元素(给元素)

```c
返回下标
int LocateElemSqList (SequenList* pList, ElemType key)
{
  int i;
  for ( i=0; i<pList->last; i++ )
  {
    if ( pList->data[i] == key )
      	return i;
  }
  return -1;
}
```



### 插入元素(指定位置)

```c
边界判断-插入之后，数组不能超过长度，因为是静态数组，这我容易忘
int InsertElemSqList (SequenList* pList, ElemType x, int k)
{
	int j;
  	if ( pList->last >= LIST_SIZE ) // pList->last+1 > LIST_SIZE
    	return FALSE;
  	if ( k<0 || k>(pList->last) )
      	return FALSE;
  
  	for ( j=pList->last; j>=k; j-- )
    {
      pList->data[j+1] = pList->data[j]; // 缓冲区溢出？
    }
  	pList->data[k] = x;
  	pList->last++;
  	return TRUE;
}
```



### 删除(指定位置)

```c
int DelElemSqList (SequenList* pList, int pos)
{
	if (( pos >= 0 && pos <= pList->last-1 ) && ( pList->last != 0 ))
    {
      for ( int j=k; j<=pList->last; j++ )
      {
        pList->data[j] = pList->data[j+1];
      }
      pList->last--;
      return TRUE;
    }
  	return FALSE;
}
```



### 遍历元素

```
void showSeqList (SequenList* pList)
{
  for ( int i=0; i<pList->last; i++ )
  {
    printf(" %d", pList->data[i]);
  }
}
```

### 测试

```c
int main ()
{
  	printf("haha \n");
	IPtr = InitSeq(); // 初始化
	showSeqList(IPtr); // 遍历
	InsertElemSqList(IPtr, 100, 0); // 插入
	InsertElemSqList(IPtr, 200, 0);
	InsertElemSqList(IPtr, 300, 0);
	InsertElemSqList(IPtr, 400, 0);
	InsertElemSqList(IPtr, 500, 4);
	showSeqList(IPtr);

	int len;
	len = GetSizeSeq(IPtr);
	printf("长度：%d \n", len);

	//DelElemSqList(IPtr, 4);
	//showSeqList(IPtr);

	int elem = 10;
	int flag = 1;
	flag = GetElemSqList(IPtr, 5, &elem); // 获取
	printf("获取元素返回值：%d \n", flag);
	printf("元素%d \n", elem);
}
```



## (三) 链表

### 单链表

#### 原始模板

```c
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef struct node 
{
	ElemType data;
  	struct node* pNext;
}LinkListNode;

// ... 后续所有封装的代码都放在此位置 main上方
int main ()
{
	return 0;
}
```

#### 初始化

```c
LinkListNode* InitLinkList (void)
{
  LinkListNode* pHead = NULL;
  pHead = (LinkListNode*)malloc(sizeof(LinkListNode));
  if ( pHead )
  	pHead->pNext = NULL;
  // 我联系没有加if防御性编程，警告：取消对null指针phead的引用，原因分析：在给一个指针分配内存（malloc）之后需要检查还有没有剩余空间，如果没有剩余空间，该指针就会返回null
  
  return pHead;
}
```

#### 求长度

```c
int GetSizeLinkList (LinkListNode* pHead)
{
	int n = 0;
  	while ( pHead->pNext )
    {
      n++;
      pHead = pHead->pNext;
    }
  return n;
}
```



#### 取元素(给位置 位序)

```c
有意思的是：如果你想 if(pos<=0 || pos>??)
所以这里就应该下面这样写
LinkListNode* GetLinkListNode (LinkListNode* pHead, int pos)
{
  if ( pos <= 0 )
    return NULL;
  
  LinkListNode* p = pHead;
  int j = 0;
  while ( j<pos && p->pNext!=NULL )
  {
    p = p->pNext;
    j++;
  } // 这里可转成for，但是多用while
  // 这里还需要加一个判断，万一p->pNext就结束了
  if ( pos == j ) 
    return p;
  else 
    return NULL;
}
```



#### 查位置(给元素)

```c
LinkListNode* LocateLinkList (LinkListNode* pHead, Elemtype objData)
{
  LinkListNode* p;
  p = pHead->pNext;
  
  while ( p != NULL && p->data != objData )
  {
	p = p->pNext;
  }
  return p;
  // 我思考没有找到呢？返回啥？
  // 最后都没有找到就是NULL 找到了就是返回指针
}

while写法2：对比
while (p != NULL)
{
  if ( p->data != objdata )
    p = p->pNext;
  else 
    break;
}
```



#### 插元素(给位置)_尾插法

```c
// 给你一个顺序表数据，这里用数组存放
// q指针始终指向最后一个元素
// p始终指向最新插入的元素
// p新q尾 (q初始化是头节点，可以改不？) 似乎也能理解头节点是尾元素
LinkListNode* Create_Rear_LkList (ElemType arr[], int length)
{
  LinkListNode *pHead=NULL, *p=NULL, *q=NULL;
  pHead = (LinkListNode*)malloc(sizeof(LinkListNode));
  pHead && (q = pHead); //初始化时 可以理解头节点是最后一个结点
  
  for ( int i=0; i<length; i++ )
  {
    p = (LinkListNode*)malloc(sizeof(LinkListNode));
   if (p)
   	   p->data = arr[i];
   if (q)
    {
     q->pNext = p;
     q = p;     
    }
  }
  q && (q->pNext = NULL); // 这里p q都可以，都是指向最后一个元素
  return pHead;
}
```

#### 插元素(给位置)_头插法1

```c
// q始终指向第一个元素结点.
// p指向新加入的元素
// 有一个头指针q始终指向第一个结点，遍历数组，不断加入即可
LinkListNode* Create_Front1_LkList (ElemType arr[], int length)
{
  LinkListNode *pHead=NULL, *p=NULL, *q=NULL;
  pHead = (LinkListNode*)malloc(sizeof(LinkListNode));
  if ( pHead )
  {
    pHead->pNext = NULL;
    q = pHead->pNext;  
  }
  
  // 头插的时候，必须逆序遍历顺序表
  for ( int i=length-1; i>=0; i-- )
  {
    p = (LinkListNode*)malloc(sizeof(LinkListNode));
    if ( p )
    {
      p->data = arr[i];
      p->pNext = q;
      pHead && (pHead->pNext = p);
      pHead && (q = pHead->pNext); // 更新q指针  q = p;更简单些
    }
  }
  
  return pHead;
}
```

#### 插元素(给位置)_头插法2

```c
// 搞个首元素q指针，先不要头节点，不断加入新结点，直到全部加入，最后再申请一个头节点，指向第一个结点 
// q首p新加入
LinkListNode* Create_Front2_LkList (ElemType arr[], int length)
{
  LinkListNode *pHead=NULL, *p=NULL, *q=NULL;
  
  for ( int i=length-1; i>=0; i-- )
  {
    p = (LinkListNode*)malloc(sizeof(LinkListNode));
    if ( p )
    {
      p->data = arr[i];
      p->pNext = q;
      q = p;     
    }
  }
  
  pHead = (LinkListNode*)malloc(sizeof(LinkListNode));
  if (pHead)
  {
    pHead->pNext = q;
    return pHead;
  }
  else 
    return NULL;
  // 优化这里:
  // if ( pHead )
  //   pHead->pNext = q;
  // return pHead;
}
```

#### 插元素(给位置)_头插法3 

```c
// 我最喜欢这个算法，1的升级版。省了一个变量内存。
// pHead头指针固定了，pHead->pNext始终指向第一个元素结点
// p新
LinkListNode* Create_Front3_LkList (ElemType arr[], int length)
{
	LinkListNode *pHead=NULL, *p=NULL;
  	pHead = (LinkListNode*)malloc(sizeof(LinkListNode));
  	pHead && (pHead->pNext = NULL);
  	
  	for ( int i=length-1; i>=0; i-- )
    {
      p = (LinkListNode*)malloc(sizeof(LinkListNode));
      if ( p )
      {
        p->data = arr[i];
        pHead && (p->pNext = pHead->pNext);
        pHead && (pHead->pNext = p);
      }
    }
  
  	return pHead; 
}
```



#### 删除元素(给定结点的后续结点)

```c
// A->B->C  A->C
LinkListNode* Delete_After_LkList (LinkListNode* ptr)
{
  LinkListNode* fpter = ptr->pNext; // B
  ptr->pNext = fptr->pNext; // A -> C
  return fpter; // B
}
```



#### 删除元素(给定位置)

```c
LinkListNode* Delete_i_LkList (LinkListNode* pHead, int i)
{
  // 边界判断-pos 
  if ( pos <= 0 ) return NULL;
  // 边界判断-链表是否为空 !!似乎链表不用像数组那样去思考
  
  LinkListNode *ptr, *qPtr = NULL;
  // 这里区分1和非1，因为当pos是1，GetLinkListNode传过去的是1-1=0，GetLinkListNode直接返回NULL，所以这里加个判断，pos是1，直接返回头节点，因为pos是1代表第一个元素，前驱自然就是头节点了
  if ( pos == 1 )
    ptr = pHead;
  else 
    ptr = GetLinkListNode(pHead, pos-1); //拿到i的前驱结点
  
  if ( ptr != NULL && ptr->pNext != NULL )
  {
    qPtr = Delete_After_LkList(ptr);
  }
  return qPtr;
}
```



#### 遍历元素

```c
void ShowLkList (LinkListNode* pHead)
{
	LinkListNode* p = pHead->pNext;
  	while ( p != NULL ) // p不为空 不是pHead
    {
      printf(" %d", p->data);
      p = p->pNext;
    }
	printf("\n");
}
```

#### 测试

```c
注意：下面条件判断不一样，假设下一个是NULL，
while ( p!=NULL ) 多了行代码 LinkListNode *p = pHead->pNext;
while ( p->pNext )
  
int main ()
{
  //LinkListNode *LNode = InitLinkList();

	// 尾插法
	int arr[10] = { 1,3,5,7,9,2,4,6,8,10 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	LinkListNode *LHead = Create_Rear_LkList(arr, sz);
	showLkList(LHead); // 遍历

	// 头插法1
	//int arr2[] = { 2,3,6,7,1, 9,4,5,10 };
	//int sz2 = sizeof(arr2) / sizeof(arr2[0]);
	//LinkListNode* LHead6 = Create_Front1_LkList(arr2, sz2);
	//showLkList(LHead6); // 遍历

	// 头插法2
	//int arr2[] = { 2,3,6,7,1, 9,4,5,10,8 };
	//int sz2 = sizeof(arr2) / sizeof(arr2[0]);
	//LinkListNode* LHead6 = Create_Front2_LkList(arr2, sz2);
	//showLkList(LHead6); // 遍历

	// 头插法3
	int arr2[] = { 2,3,6,7,1, 9,4,5,10,8 };
	int sz2 = sizeof(arr2) / sizeof(arr2[0]);
	LinkListNode* LHead6 = Create_Front3_LkList(arr2, sz2);
	showLkList(LHead6); // 遍历

	//int len;
	//len = GetSizeLinkList(LHead); // 长度获取
	//printf("%d \n", len);

	//LinkListNode *LHead2 = GetLinkListNode(LHead, 1);  // 获取
	//if ( LHead2 )
	//	printf("%d \n", LHead2->data);
	
	// 查位置(给元素)
	//LinkListNode *LHead3 = LocateLinkList(LHead, 88);
	//if ( LHead3 )
	//	printf("%d \n", LHead3->data);
	//else 
	//	printf("空指针 \n");

	// 删除元素(给定结点的后续结点)
	//LinkListNode* LHead5 = Delete_After_LkList(LHead->pNext);
	//if ( LHead5 )
	//	printf("%d \n", LHead5->data);
	//else 
	//	printf("空指针 \n");
	//showLkList(LHead);

	// 按照位置删除
	//Delete_i_LkList(LHead, 10);
	//showLkList(LHead);
}
```

#### 题目一-顺序表逆转

```c
// 设有一个顺序表，其数据为a,b,c,d,e,f,g，要求将其就地转置为g,f,e,d,c,b,a，要求不能额外开辟内存，顺序表仍然占据原空间。

// 顺序表实现反转
// 算法思路：首尾对调
// 奇数个 7 7/2=3 只需要对调三次即可
// 偶数个 6 6/2=3 只需要对调三次即可 
// 0 + (last - 1) = last - 1
// 1 + (last - 2) = last - 1
// ...
// i + (?) = last - 1
// ? = last - 1 - i; 即对调后面的那个元素的下标
SequenList* pGlobalSeq;
void ReverSeqList ( SequenList* pList )
{
  int temp;
  int cout = pList->last / 2;
  if ( pList->last == 0 || pList->last == 1 ) return;
  
  for ( int i=0; i<cout; i++ )
  {
    temp = pList->data[i];
    pList->data[i] = pList->data[pList->last - 1 - i];
    pList->data[pList->last - 1- i] = temp;
  }
}

// 测试 
int main ()
{
	pGlobalSeq = InitSeq();
  	for ( int i=0; i<10; i++ )
    {
      InsertElemSqList(pGlobalSeq, i*2, i);
    }
  	showSeqList(pGlobalSeq); 
  	ReverseSeqList(pGlobalSeq);
  	showSeqList(pGlobalSeq);
  
  	free(pGlobalSeq);
  	return 0;
}
```

```c
// 链表实现反转
LinkListNode* ReverseLkList (LinkListNode* pHead)
{
  LinkListNode *Pointer, *Next;
  LinkListNode *Back;
  Back = pHead;
  Pointer = Back->pNext;
  Next = Pointer->pNext;
  
  Pointer->pNext = Back;
  Back = Pointer;
  Pointer = Next;
  
  while ( Pointer->pNext != NULL )
  {
    Next = Pointer->pNext;
    Pointer->pNext = Back;
    Back = Pointer
    Pointer = Next;
  }
  
  Pointer->pNext = Back;
  pHead->pNext->pNext = NULL;
  pHead->pNext = Pointer;
  
  return pHead;
}

// 测试
int main ()
{
  LinkListNode* pHead = NULL;
  int arr[] = { 0,1,2,3,4,5,6,7,8,9 };
  pHead = Create_Rear_LkList(arr, 10);
  ShowLkList(pHead);
  
  pHead = ReverseLkList(pHead);
  showLkList(pHead);
  ShowLkList(pHead);
  
  return 0;
}
```

#### 题目二-一元多项式运算

```c
// 为简便起间，默认次序是升序的。
// 假设多项式的最低项是常数项，不要有-1次方这种。
// 假定所有的元素都是关于x的多项式 
// PolyA: 1+2x+3x^2
// PolyB: 3x+x^4
// 将PolyA和PolyB进行相加，将结果放入Poly中

#include <stdio.h>
#include <stdlib.h>

typedef struct Polynode 
{
	int coef; // 系数
  	int exp; // 指数
  	Polynode* pNext;
}LinkPolyNode;

// pc: 新结点要插入的位置
LinkPolyNode* attach (int coef, int exp, LinkPolyNode* pc)
{
	LinkPolyNode* p;
  	p = (LinkPolyNode*)malloc(sizeof(LinkPolyNode));
  	p->coef = coef;
  	p->exp = exp;
  	pc->pNext = p;
  	return p;
}

LinkPolyNode* MergePoly (LinkPolyNode* headA, LinkPolyNode* headB)
{
	LinkPolyNode* headC;
  	LinkPolyNode *pa, *pb, *pc, *p;
  
  	int x;
  	pa = headA->pNext;
  	pb = headB->pNext;
  	pc = (LinkPolyNode*)malloc(sizeof(LinkPolyNode));
  	
  	while ( pa && pb )
    {
      if ( pa->exp == pb->exp )
      {
		x = pa->coef + pb->coef;
         if ( x != 0 )
           	pc = attach(x, pa->exp, pc);
         pa = pa->pNext;
         pb = pb->pNext;
         continue;
      }
      if ( pa->exp < pb->exp )
      {
        p = pa;
        pa = pa->pNext;
      }
      else 
      {
		p = pb;
         pb = pb->pNext;
      }
      
      pc = attach(p->coef, p->exp, pc);
    }
  	
  	p = pa;
  	if ( pa == NULL ) p = pb;
  	while ( p )
    {
      pc = attach(p->coef, p->exp, pc);
      p = p->pNext;
    }
  	pc->pNext = NULL;
  
  	return headC;
}

//设计辅助的显示函数 
void ShowList (LinkPolyNode* pHead)
{
  LinkPolyNode* p = pHead->pNext;
  while ( p != NULL )
  {
    // 常数项
    if ( p->exp == 0 )
    {
      printf("%d", p->coef);
      p = p->pNext;
      continue;
    }
    // 一次项
    if ( p->exp == 1 )
    {
      if ( p->exp == 0 )
        printf("+%x", p->coef);
      else 
        printf("%dx", p->coef);
      
      p = p->pNext;
      continue;
    }
    // 高次项
    if ( p->coef > 0 )
      printf("+%x^%d", p->coef, p->exp);
    else 
      printf("%dx^%d", p->coef, p->exp);
    
    p = p->pNext;
  }
}

// 测试
int main ()
{
	// PolyA: 1+2x+3x^2
  	// PolyB: 3x+x^4
  	LinkPolyNode HeadA,A1,A2,A3;
  	LinkPolyNode HeadB,B1,B2;
  
  	HeadA.pNext = &A1;
  	A1.pNext = &A2;
  	A2.pNext = &A3;
  	A3.pNext = NULL;
  
  	HeadB.pNext = &B1;
	B1.pNext = &B2;
	B2.pNext = NULL;

	//建立多项式:PolyA: 1+2x+3x^2
	A1.coef = 1;
	A1.exp = 0;
	A2.coef = 2;
	A2.exp = 1;
	A3.coef = 3;
	A3.exp = 2;

	//PolyB: 3x+x^4
	B1.coef = 3;
	B1.exp = 1;
	B2.coef = 1;
	B2.exp = 4;

	printf("\n*********PolyA********\n");
	ShowList(&HeadA);
	printf("\n*********PolyB********\n");
	ShowList(&HeadB);

	LinkPolyNode* pPloyC;
	pPloyC = MergePoly(&HeadA, &HeadB);
	printf("\n*********PolyC********\n");
	ShowList(pPloyC);
}
```

#### 题目三-学生管理系统

```c
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define LIST_SIZE 50
#define TRUE 1
#define FALSE 0
typedef struct student 
{
	int num;
  	float score;
}
typedef struct 
{
	node data[LIST_SIZE];
  	int last;
}SeqList;

// 获取班级人数
int GetSzie (SeqList* pList)
{
  return pList->last;
}
// 遍历全体学生信息
void ShowSeqList (SeqList* pList)
{
	for ( int i=0; i<pList->last; i++ )
    {
		printf("学生的学号是%d,成绩是%f\n", pList->data[i].num, pList->data[i].score);
    }
}
// 初始化
SeqList* InitSeq ()
{
	SeqList* pList = NULL;
  	pList = (SeqList*)malloc(sizeof(SeqList));
  	// 因为在服务器分配中，连续分配大量空间，往往很不容易
  	// 所以我们常常在内部就进行判断
  	if ( pList != NULL )
      pList->last = 0;
  
  	return pList;
}
// 插入元素
int InsertStuSeq (SeqList* pList, node* pNode, int k)
{
  int j;
	/*if (pList->last >= LIST_SIZE - 1)
		return FALSE;*/
	//移到函数之外，有业务人员维护插入
	//如果这个函数被反复调用的开销很大，那么我们会放弃内部校验
	//但是，如果这是一个对安全要求很高程序，内部校验依然需要
	//如果去掉了内部校验，在实际的公司开发中，会有Team leader做codereview
  
  for ( j=pList->last; j>=k; j-- )
  {
    pList->data[j + 1].num = pList->data[j].num;
    pList->data[j + 1].score = pList->data[j].score;
  }
  
  pList->data[k].num = pNode->num;
  pList->data[k].score = pNode->score;
  pList->last++;
  return TRUE;
}
// 删除
int DelSeqList (SeqList* pList, int k) 
{
  // if ( k<=0 || k>pList->last ) return FALSE;
  if ( pList->last == 0 ) return FALSE;
  
  for ( int j=k; j<=pList->last; j++ )
  {
    pList->data[j].num = pList->data[j+1].num;
    pList->data[j].score = pList->data[j+1].score;
  }
  pList->last--;
  return TRUE;
}
// 按学号查找
void DisplayStu (SeqList* pList, int stuNo)
{
	for ( int i=0; i<pList->last; i++ )
    {
      if ( pList->data[i].num == stuNo )
      {
        printf("该学生的成绩是%f\n", pList->data[i].score);
        return;
      }
    }
  	printf("该学生不存在\n");
}

// 测试
int main ()
{
  	SeqList* stuList = InitSeq();
	node stu[2];
	stu[0].num = 1;
	stu[0].score = 99;
	stu[1].num = 2;
	stu[1].score = 100;
	if (stuList) {
		for (int i = 0;i < 2;i++) {
			InesrtStuSeq(stuList, &stu[i], i);
		}

	}
	ShowSeqList(stuList);
	//DelSeqList(stuList, 1);
	//ShowSeqList(stuList);
	printf("\n************\n");
	DisplayStu(stuList, 1);
}
```



### 循环链表

#### 原始模板

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
  int data;
  struct node *pNext;
}LinkCircleListNode;

// ... 后续代码在main上面
int main ()
{
  
}
```

#### 创建

```c
// 这采用尾插法，头节点也可算最后一个结点
// q指向最后一个结点，初始化时候是头节点
// 最后需要最后一个元素pNext指针指向头节点
// 返回尾指针
LinkCircleListNode* Create_Circle_LkList (int ar[], int length)
{
  LinkCircleListNode *pHead=NULL, *p=NULL, *q=NULL;
  pHead = (LinkCircleListNode*)malloc(sizeof(LinkCircleListNode));
  pHead && (q = pHead);
  
  for ( int i=0; i<length; i++ )
  {
    p = (LinkCircleListNode*)malloc(sizeof(LinkCircleListNode));
    p->data = arr[i];
    q && (q->pNext = p);
    q && (q = p);
  }
  
  pHead && p && (p->pNext = pHead);
  return p;
  // if ( pHead && q ) q->pNext = pHead;
}
```

#### 遍历

```c
void ShowCircleLkList (LinkCircleListNode* pRear)
{
	LinkCircleListNode* p = pRear->pNext;
  	p = p->pNext;
  
  // p==头节点 元素遍历完了 跳出循环
  	while ( p != pRear->pNext )
    {
      printf("%d\n", p->data);
      p = p->pNext;
    }
}
```

#### 测试

```c
int main ()
{
  int arr[] = { 8,7,9,4,5,12,4,2,6,16,1,2,3 };
      int sz = sizeof(arr) / sizeof(arr[0]);
      LinkCircleListNode* pCircle = Create_Circle_LkList(arr, sz);
      ShowCircleLkList(pCircle);

      int arr2[] = { 99,88,77,55,66,33,55,22 };
      int sz2 = sizeof(arr2) / sizeof(arr2[0]);
      LinkCircleListNode* pCircle2 = Create_Circle_LkList(arr2, sz2);
      ShowCircleLkList(pCircle2);

  // 合并两个链表
      LinkCircleListNode* pCircle3 = Connect_Circle_LkList(pCircle, pCircle2);
      ShowCircleLkList(pCircle3);
}
```

#### 两个循环链表合并

```c
// 输入两个链表的尾指针 带头节点的
//  free(rb->pNext); 回收空间，意味着b链表的头节点空间不可达，但是rb->pNext依然是有值的
// 假定rb 0x20空间，在这个空间有一个next分量，是可以存储地址值。
// free(rb) 才是rb->pNext不可用
// free(rb->pNext)，则是里面的分量pNext不可用
// rb->pNext始终指向的是原b链表的头节点
LinkCircleListNode* Connect_Circle_LkList (LinkCircleListNode* ra, LinkCircleListNode* rb)
{
  LinkCircleListNode* p = ra->pNext; // 保存第一个链表的头节点
  ra->pNext = rb->pNext->pNext; // 第一个链表尾部指向 第二个链表的第一个元素
  free(rb->pNext); 
  rb->pNext = p; // 第二个链表的尾元素指向第一个链表的头节点
  
  return rb;
}

// 测试
int main ()
{
  int a[] = { 1,3,5 };
  int b[] = { 2,4,6 };
  LinkCircleListNode *ra, *rb;
  ra = Create_Circle_LkList(a, 3);
  rb = Create_Circle_LkList(b, 3);
  LinkCircleListNode* pRear = Connect_Circle_LkList(ra, rb);
  ShowCircleLkList(pRear);
}
```

### 双向链表

#### 原始模板

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct DNode
{
  int data;
  struct DNode *prior, *next;
}DLinkListNode;

// ...后续代码main上面
int main ()
{
  
}
```

#### 插入？

```c
void Insert_Before_DL (DLinkListNode* p, int x)
{
  DLinkListNode* s;
  s = (DLinkListNode*)malloc(sizeof(DLinkListNode));
  s->data = x;
  
  s->prior = p->prior;
  if ( p->prior != NULL )
    	p->prior->next = s;
  s->next = p;
  p->prior = s;
}
```

#### 删除

```c
DLinkListNode* Delete_DL (DLinkListNode* ptr)
{
  ptr->prior->next = ptr->next;
  ptr->next->prior = ptr->prior; // 逻辑上，无法找到ptr了
  return ptr;
}
```



#### 测试

```c
int main(void) {
    // 双向链表的初始化
	DLinkListNode x;
	DLinkListNode *head;
	DLinkListNode *ptr;
	ptr = &x;
	ptr->data = 3;
	ptr->prior = NULL;
	ptr->next = NULL;

	Insert_Before_DL(ptr, 1);
	Insert_Before_DL(ptr, 2);
	DLinkListNode *p,*q;
	p = &x;
	while (p != NULL) {
		printf("%d\n", p->data);
		if (p->prior == NULL)
			q = p;//q记录了第一个节点
		p = p->prior;
	}
	
	while (q != NULL) {
		printf("%d\n", q->data);
		q = q->next;
	}
	getchar();
	return 0;
}
```

#### 题目一-约瑟夫环

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
  int data;
  struct node* pNext; 
}LinkJoeNode;

// 考虑建立约瑟夫环的循环链表
// 不带头节点，需要模拟约瑟夫环的工作过程
LinkJoeNode* CreateLkList (int arr[], int length)
{
  LinkJoeNode *head, *p, *q;
  head = (LinkJoeNode*)malloc(sizeof(LinkJoeNode));
  head->data = arr[0];
  q = head;
  
  for ( int i=1; i<length; i++ )
  {
    p = (LinkJoeNode*)malloc(sizeof(LinkJoeNode));
    p->data = arr[i];
    q->pNext = p;
    q = p;
  }
  
  p->pNext = head;
  return p;
}

int main ()
{
  // 从位置1开始，初始30个人，剩余15个人
  int s = 1;
  int m = 9; // 逢9出圈
  int k = 15; // 出圈者是15个人
  int arr[30];
  
  for ( int i=0; i<30; i++ )
  {
    arr[i] = i + 1;
  }
  
  LinkJoeNode *p, *q;
  LinkJoeNode* rear = CreateLkList(arr, 30);
  p = rear;
  
  while ( k > 0 )
  {
    for ( int j=0; j<m-1; j++ )
    {
		p = p->pNext;
    }
    // p指针停在在m-1处 
    q = p->pNext;
    printf("第%d个元素出圈\n", q->data);
    p->pNext = q->pNext; // 相当于删除第15的这个元素了
    free(q);
    k--;
  }
}
```



## (四) 栈

### 顺序栈

#### 原始模板

```c
#include <stdio.h>

#define stackSize 100
#define TRUE 1
#define FALSE 0
typedef int BOOL;
typedef int ElemType;
typedef struct 
{
  ElemType stack[stackSize];
  int top;
}SeqStack;

// ...后续代码在main之上
int main ()
{
}
```



#### 初始化

```c
Bool init (SeqStack* pStack)
{
  pStack->top = 0;
  return TRUE;
}
// 我不是很理解这里没有申请内存？之前顺序表都申请了
```

#### 判空

```c
BOOL isEmpty (SeqStack* pStack)
{
  return (pStack->top == 0);
}
```

#### 压栈

```c
BOOL pushStack (SeqStack* pStack, ElemType x)
{
  if ( pStack->top + 1 > stackSize )
  {
    printf("空间溢出\n");
    return FALSE;
  }
  // ♥：先增加top，然后下标访问
  pStack->top++;
  pStack->stack[pStack->top] = x;
  return TRUE;
}
```

#### 出栈

```c
ElemType popStack (SeqStack* pStack)
{
  ElemType temp;
  if ( pStack->tpo == 0 )
  {
    printf("当前是空栈 \n");
    return -1;
  }
  
  temp = pStack->stack[pStack->top];
  pStack->top--; // 逻辑上的出栈
  return temp;
}
```

#### 获取栈顶元素

```c
BOOL GetSeqStack (SeqStack* s, ElemType* data)
{
  // 边界判断-是否存在元素
  if ( s->top == 0 )
    return FALSE;
  
  *data = s->stack[s->top];
  return TRUE;
}
```

#### 测试

```c
int main ()
{
    // 初始化
	SeqStack pStack;
	initSeqStack(&pStack);
	// 压栈
	pushStack(&pStack, 300);
	pushStack(&pStack, 200);
	pushStack(&pStack, 100);
	pushStack(&pStack, 3);
	// 获取栈顶元素
	int data = 0;
	getSeqStack(&pStack, &data);
	printf("栈定元素：%d \n", data);
	// 出栈
	int delData = 0;
	delData = popStack(&pStack);
	printf("被删除元素：%d \n", delData);

	int data2 = 0;
	getSeqStack(&pStack, &data2);
	printf("栈定元素：%d \n", data2);
}
```

#### 题目一-十进制转八进制(10->N)

```c
void myConv (SeqStack* pStack ,int n)
{
  int e;
  while (n)
  {
    pushStack(pStack, n%8);
    n /= 8;
  }
  while ( !isEmpty(pStack) )
  {
    e = popStack(pStack);
    printf("%d", e);
  }
}

// 测试 
int main ()
{
  SeqStack s;
  init(&s);
  printf("十进制数1348，转为的8进制是：\n");
  myConv(&s, 1348);
  return 0;
}
```



### 链栈

## (五) 队列

### 顺序队

### 链队

## (六) 树

## (七) 实战

### 1. 代码是一步一步的调试出来的，不是一蹴而就的 









