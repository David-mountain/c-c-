# Pramming C logic 

## 1. string

### 1. 1 strcpy 

```c
// algorithm: src != '\0'   one by one

// 版本1 
char * _strcpy (dest, src)
  char *dest;
  const char *src;
{
  register char *d = dest;
  register const char *s = src;
  
  do 
    *d++ = *s;
  while (*s++ != '\0');
  
  return d-1;
}
// 版本2 my_
char * My_strcpy (char *dest, const char *src)
{
  char *p = dest;
  while (*src != '\0') // while (*src)
  {
	*p = *src;
    p++;
    src++;
    // *p++ = *src++;
  }
  *p = '\0'; // 我写成了 "\0" 双引号的 我说怎么一直不对 这里可以 *p = *src;
  return dest;
}
// 版本3 microsoft  💪💪💪
char * strcpy (char *dst, const char *src)
{
  char *p = dst;
  while (*p++ = *src++) // beause judge src is equal to p
    ;
  return (dst);
}
// 版本4 <<高质量C++/C编程指南>> 
#include <assert.h>
char * strcpy (char *dest, const char *src)
{
	assert((dest!=NULL) && (src != NULL));
    char *address = dest;
    while ((*dest++ = *src++) != '\0' ) // while (a != 0)  ==  while (a)
      ;
  return address;
}
```

###  1.2 strcat

```c
// algorithm: 

// 版本1

```



### 1.3 strcmp

```c
// 思路：循环判断是否相等(注要两者都有值哈) 如果不等，则直接返回两者相减的值
// 比较两个字符串的比较(根据什么编码格式 ascii码?)
// 返回：大于1 0 小于1 

// 版本1：
int My_strcmp (const char* str1, const char* str2)
{
  while (*str1 == *str2 && *str1) // && str2省略了，因为两者相等且str1存在，则str2必存在
    str1++, str2++;
  
  return (unsigned char)*str1 - (unsigned char)*str2; // 有些汉字等特殊符号，转成无符号
}

// 版本2：库函数源代码
// 先用 unsigned char * 将其指针转化为无符号型，在去取里面存的值，即得到字符的ASCⅡ值；
// return ((-ret) < 0) - (ret < 0); 这一句就是让差值大于 0 的返回 1；差值小于0的返回 -1
int strcmp (const char * src, const char * dst)
{
	int ret = 0;
    while ((ret = *(unsigned char *)src - *(unsigned char *)dst) == 0 && *dst)
      ++src, ++dst;
    return ((-ret) < 0) - (ret - 0));
}

// 版本3：版本1的简单模拟版
int My_strcmp (const char* str1, const char* str2)
{
  while (*str1 == *str2)
  {
    if (*str1 == '\0')
      return 0;
    ++str1;
    ++str2;
  }
  return *str1 - *str2;
}
```

### 1.4 strchr

```c
// 用于查找字符串中的一个字符，并返回该字符在字符串中第一次出现的位置

// 版本1
char * My_strchr (const char* str, int c)
{
  while (*str)
  {
    if (*str == c)
      return str;
    ++str;
  }
  return NULL;
}

demo:	找出字符串中所有这个字符的第几个
	  char str[] = "This is a sample string";
	  char * pch;
	  printf ("Looking for the 's' character in \"%s\"...\n",str);
	  pch = strchr(str,'s'); // "s is a sample string" 第一次 确实是返回后面的字符串指针

	  while (pch != NULL)
	  {
		  printf("found at %lld \n", pch - str + 1);
		  pch = strchr(pch + 1, 's');
	  }
```

### 1.5 strlen

```c
// 看上去简单，让我们一步一步走进这个坑

// 版本1：
size_t strlen (const char *str)
{
  if (str == NULL)
    return 0;
  
  size_t  length = 0;
  while (str[length] != 0)
    length++;
  
  return length;
}

// 版本2：
size_t strlen (const char* str)
{
  if (str == NULL)
    return 0;
  
  const char *cp = str;
  while (*cp++)
    ;
  
  return (cp - str - 1); // 因为没有计算\0 所以-1了
}

// 版本3：
// 通过减少数据从内存存取到寄存器的次数，手段就是先字节对齐，
// 然后每次读取一个4/8字节的多字节数据，对多字节数据遍历是否存在\0。
// 为什么内存中需要对齐呢？
// 　在CPU眼中，它把内存当成是一块一块的，块的大小可以是2，4，8，16字节大小，它在读取内存时也是一块一块进行读取的。同时不同的数据类型又是按照自己所占的字节数来进行存储的。
// 假设现在一个int型存储在0-3字节中，当CPU要读取这个int型的数据到寄存器中，就能一次过把这4个字节读到寄存器中。但是当该数据是从1字节开始存储的，问题变的有些复杂。CPU要先读取0—3字节的数据进寄存器，并再次读取4—7字节的数据进寄存器，接着把0字节和6，7字节的数据剔除，最后合并1，2，3，4字节的数据进寄存器。对一个内存未对齐的数据进行了这么多额外的操作，大大降低了CPU性能。即使内存在对齐数据之后，可能会使得占用的多余空间变多，经过内存对齐后，CPU的内存访问速度大大提升，这样的牺牲也是值得的。
// 手机有个公式 

// 版本4：汇编代码

demo:
  char szInput[256];
  printf ("Enter a sentence: ");
  gets (szInput);
  printf ("The sentence entered is %u characters long.\n",(unsigned)strlen(szInput));
```

### 1.6 strpbrk

```c
// algorithm: double while(for)

// 版本1
char My_strpbrk (const char *str, const char *s)
{
	while (*str)
    {
      	char c = *str; 
      	for (const char *q = s; *q; ++q)
         	if (*q == c)
              return (char *)str;
      
		++str;
    }
  return NULL;
}
// 版本2
char* My_strpbrk (const char *str, const char *s)
{
	while (*str)
    {
      char c = *str;
      if (strchr(s, c)) // strchr ?
        return (char *)str;
      ++str;
    }
    return NULL;
}

demo:
  char str[] = "This is a sample string";
  char key[] = "aeiou";
  char * pch;
  printf ("Vowels in '%s': ",str);
  pch = strpbrk (str, key);
  while (pch != NULL)
  {
    printf ("%c " , *pch);
    pch = strpbrk (pch+1,key);
  }
```

### 1.7 strtok

```c
// algorithm: 
// split string into tokens
// change original str  to '\0'

// 版本1
char * My_strtok (char *str, const char *delimiters)
{
  static char *last = NULL;
  if (!str) str = last;
  if (!str) return NULL;
  
  while (*str)
  {
    char c = *str;
    const char *q = delimiters;
    
    while (*q != c && *q)
      ++q;
    
    if (*q == '\0')
    {
		char *p = str;
      	 while (c = *p)
         {
           q = s;
           while (c != *q && *q)
             ++q;
           if (*q)
           {
			*p = '\0';
             last = p + 1;
             return str;
           }
           ++p;
         }
      	return str;
    }
    ++str;
  }
  last = NULL;
  return NULL;
}
// 版本2 源码
char * strtok (char *s, const char *declim)
{
  const char *spanp;
  int c, sc;
  char *tok;
  static char *last;
  if (s == NULL && (s = last) == NULL)
    return (NULL);
  
  const c = *s++;
  for (spanp = delim; (sc = *spanp++) != 0)
  {
	if (c == sc)
      goto cont;
  }
  
  if (c == 0)
  {
	last = NULL;
    return (NULL);
  }
  tok = s - 1;
  
  for (;;)
  {
	c = *s++;
    spanp = declim;
  }
  
  do 
  {
	if ((sc == *spanp++) == c)
    {
      if (c == 0)
        s = NULL;
      else 
        s[-1] = 0;
      last = s;
      return (tok);
    }
  } while (sc != 0);
}
```

### 1.8 strstr

```c
// algorithm: find substring 
// Returns a pointer to the first occurrence of str2 in str1, or a null pointer if str2 is not part of str1.

// 版本1 💪💪💪
char * My_strstr (const char *str, const char *substr)
{
  while (*str)
  {
    const char *p = str;
    const char *q = substr;
    
    while (*p == *q && *q)
      ++q, ++p;
    if (*q == '\0')
      return (char *)str;
    
	++str;
  }
  return NULL;
}
```

### 1.9 strrch

```c
// reverse find char

// 版本1
char* My_strrch (const char* str, inc c)
{
  char* p = str;
  while (*p)
    ++p;
  while (--p >= str)
  {
	if (*p == c)
      return p;
  }

  return NULL;
}
```

## 2. memory

### 2.1 memcpy

```c
void *memcpy(void *str1, const void *str2, size_t n)
str1 -- 指向用于存储复制内容的目标数组，类型强制转换为 void* 指针。
str2 -- 指向要复制的数据源，类型强制转换为 void* 指针。
n -- 要被复制的字节数。

该函数返回一个指向目标存储区 str1 的指针。

案例1：
   const char src[50] = "http://www.runoob.com";
   char dest[50];
 
   memcpy(dest, src, strlen(src)+1);
   printf("dest = %s\n", dest);

案例2：
将 s 中第 11 个字符开始的 6个连续字符复制到 d 中:
	const char *s = "abcde12345";
	char d[11];

	memcpy(d, s+5, 3);
	d[3] = '\0';
	printf("%s \n", d);

    123

案例3：
覆盖原有部分数据:
  char src[] = "***";
  char dest[] = "abcdefg";
  printf("使用 memcpy 前: %s\n", dest);
  memcpy(dest, src, strlen(src));
  printf("使用 memcpy 后: %s\n", dest);

  使用 memcpy 前: abcdefg
  使用 memcpy 后: ***defg
  
## 封装
	void * memcpy (void* pDest, const void* pSrc, size_t nCount)
  {
    char *p = (char*)pDest;
    const char* q = (const char*)pSrc;
    
    while (nCount--)
    {
		*p++ = *q++;
    }
  }
```

### 2.2 memmove

```c
另一个用于从 src 复制 n 个字符到 dest 的函数。
但是在重叠内存块这方面，memmove() 是比 memcpy() 更安全的方法。
如果目标区域和源区域有重叠的话，memmove() 能够保证源串在被覆盖之前将重叠区域的字节拷贝到目标区域中，复制后源区域的内容会被更改
如果目标区域与源区域没有重叠，则和 memcpy() 函数功能相同。

void *memmove(void *str1, const void *str2, size_t n)
str1 -- 指向用于存储复制内容的目标数组，类型强制转换为 void* 指针。
str2 -- 指向要复制的数据源，类型强制转换为 void* 指针。
n -- 要被复制的字节数。

该函数返回一个指向目标存储区 str1 的指针。

例子：
   const char dest[] = "oldstring";
   const char src[]  = "newstring";

   printf("Before memmove dest = %s, src = %s\n", dest, src);
   memmove(dest, src, 9);
   printf("After memmove dest = %s, src = %s\n", dest, src);

  Before memmove dest = oldstring, src = newstring
  After memmove dest = newstring, src = newstring
```



### 2.3 memcmp

```c
int memcmp(const void *str1, const void *str2, size_t n)
str1 -- 指向内存块的指针。
str2 -- 指向内存块的指针。
n -- 要被比较的字节数。

如果返回值 < 0，则表示 str1 小于 str2。
如果返回值 > 0，则表示 str1 大于 str2。
如果返回值 = 0，则表示 str1 等于 str2。

案例：
	char str1[15];
	char str2[15];
	int ret;

	memcpy(str1, "abcedf", 6);
	memcpy(str2, "ABCDEF", 6);

	ret = memcmp(str1, str2, 5);

	if (ret > 0)
		printf("str2 小于 str1");
	else if (ret < 0)
		printf("str2 大于 str2");
	else 
		printf("str1 等于 str2");

	str2 小于 str1
	
	
## 封装
	int memcmp (const void* str1, const void* str2, size_t nCount)
    {
      const unsigned char *p = (const unsigned char*)str1;
      const unsigned char *q = (const unsigned char*)str2;
      
      while (*p == *q && nCount--)
        ++p, ++q;
      
      return *p - *q;
    }
```

### 2.4 memchr

```c
void *memchr(const void *str, int c, size_t n)
str -- 指向要执行搜索的内存块。
c -- 以 int 形式传递的值，但是函数在每次字节搜索时是使用该值的无符号字符形式。
n -- 要被分析的字节数。

该函数返回一个指向匹配字节的指针，如果在给定的内存区域未出现字符，则返回 NULL。

例子：
   const char str[] = "http://www.runoob.com";
   const char ch = '.';
   char *ret;
 
   ret = (char*)memchr(str, ch, strlen(str));
// 第一次，我想还要强制转成char*,这么麻烦？
// 如果不转，报错：不能将const void类型的值分配到char*类型实体
 
   printf("|%c| 之后的字符串是 - |%s|\n", ch, ret);

   |.| 之后的字符串是 - |.runoob.com|
```

### 2.5 memset

```c
void *memset(void *str, int c, size_t n)
str -- 指向要填充的内存块。
c -- 要被设置的值。该值以 int 形式传递，但是函数在填充内存块时是使用该值的无符号字符形式。
n -- 要被设置为该值的字符数。

该值返回一个指向存储区 str 的指针。

例子：
   char str[50];
 
   strcpy(str,"This is string.h library function");
   puts(str);
 
   memset(str,'$',7);
   puts(str);

   This is string.h library function
   $$$$$$$ string.h library function
   
## 封装
	// void * memset (void *str, int c, size_t n) 老师的是char c? 能否存下
	void * memset (void *str, char c, size_t n)
   {
     char* p = (char*)str;
     while (n--)
     {
		*p++ = c;
     }
   }
```

## 3. while 

### 3.1 print_star

```c
// 1. 打印7列13行的菱形两角 竖向三角形
int i = 0;
int dir = 1; // 请注意，这个真的绝了 💪💪💪

for (; i > -1; i+=dir)
{
  for (int j = -1; j < i; ++j)
    printf("* ");
  putchar(10);
  
  if (i == 6)
    dir = -1;
}
分析：
i   打印*数量
0	1
2	3
3   4
4	5
5	6
  		dir=1
6 	7	if(i==6) dir=-1
  		dir=-1
5	6  
4	5
3	4
2	3
1 	2
0	1
-1
  
// 2. 打印13列7行的菱形两角
/*

              *
            * * *
          * * * * *
        * * * * * * *
      * * * * * * * * *
    * * * * * * * * * * *
  * * * * * * * * * * * * *

*/
int i = 7;

while (i--)
{
	int j = 0;
  	for (; j<i; ++j)
      printf(" ");
  	for (; j<13-i; ++j)
      printf("* );
     putchar(10); // 换行
}
             
// 3. 打印13行13列完整的菱形。 ???
            *
          * * *
        * * * * *
      * * * * * * *
    * * * * * * * * *
  * * * * * * * * * * *
* * * * * * * * * * * * *
  * * * * * * * * * * *
    * * * * * * * * *
      * * * * * * *
        * * * * *
          * * *
            *
             
    for (int i = 6, dir = -1; i < 7; i += dir)
    {//6 5 4 3 2 1 0 1 2 3 4 5 6
        int j = 0;
        for (; j < i; ++j)
            printf("  ");
        for (; j < 13 - i; ++j)//7 8 9 
            printf("* ");
        if (i == 0)
            dir = 1;
        putchar(10);
    }
```



### 3.2 isPalin

### 3.3 reverse char string

### 3.4 bubble sort

### 3.5 print 16 or 2 use pow

```c
// 版本1：
    unsigned int m = 2012848223;

	for (int n = 31; n >= 0; n--)
	{
		unsigned int sum = 1;
		int i = 0;
		for (; i<n; ++i)
			sum *= 2;

		printf("%d", m / sum % 2);
	}

打印：01110111111110011010000001011111

// 版本2：
	unsigned int m = 2012677777;
	unsigned int sum = 0x80000000;

	for (int n = 31; n >= 0; n--)
	{
		printf("%d", m / sum % 2);
		sum /= 2;
		if (n % 4 == 0)
			putchar(32);
	}

打印：0111 0111 1111 0111 0000 0110 1001 0001
  
// 版本3：
  	unsigned int m = 2012677777;
	
	for (int n = 31; n >= 0; n--)
	{//31 .. 0（2的n次方）
		printf("%d", (m >>n) % 2);
		if (n % 4 == 0)
			putchar(32);
	}

打印：0111 0111 1111 0111 0000 0110 1001 0001
  
// 版本4：
  	unsigned int m = 2012677777;

	for (int n = 31; n >= 0; n--)
	{
		printf("%d", m / (1<<n) % 2);
		if (n % 4 == 0)
			putchar(32);
	}
  
打印：0111 0111 1111 0111 0000 0110 1001 0001
```



## 4. continuation

### 4.1 KMP



