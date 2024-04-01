#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void test_fprintf()
{
	//Formatted input/output 格式化输入输出
	//int fprintf ( FILE * stream, const char * format, ... );
	//Write formatted data to stream

	FILE *pFile;
	int n;
	char name[100];

	pFile = fopen("myfile.txt", "w");
	for (n = 0; n < 3; ++n)
	{
		puts("please enter a name: ");
		gets_s(name, 100);
		fprintf(pFile, "Name %d [%-10.10s] \n", n+1, name);
	}
	fclose(pFile);
	// %-10.10s ??? -左对齐  -10表示 域宽10字符，负号表示不足10字符时左对齐 
	// 后边的.10表示超出其10字符时戴断。
	
	//Name 1 [Alice     ] 
	//Name 2 [Bob       ] 
	//Name 3 [Cat       ] 
}

void test_fscanf()
{
	// int fscanf ( FILE * stream, const char * format, ... );
	//Read formatted data from stream

	char str[80];
	float f;
	FILE* pFile;

	pFile = fopen("myfile2.txt", "w+");
	//fprintf(pFile, "%f %s", 3.1416, "PI");
	fprintf(pFile, "%d %d", 111, 99); // 果然会出错 我就在思考它是如何区分数据的 如何做隔断的
						// fscanf遇到空格和换行时结束，注意空格时也结束。 %d%d错误打印   %d %d
	rewind(pFile);
	int a = fscanf(pFile, "%f", &f);
	int b = fscanf(pFile, "%s", str);
	fclose(pFile);
	printf("I have read: %f and %s \n", f, str);
	// rewind函数作用等同于 (void)fseek(stream, 0L, SEEK_SET); 用 法: void rewind(FILE *stream);
	// fopen w+?
}

void test_sprintf()
{
	// int sprintf ( char * str, const char * format, ... );
	//Write formatted data to string

	char buffer[50];
	int n, a=5, b=3;
	n = sprintf(buffer, "%d plus %d is %d", a, b, a+b);
	printf("[%s] is a string %d chars long \n", buffer, n);
	// [5 plus 3 is 8] is a string 13 chars long
	// %d plus %d is %d 13个
}

void test_sscanf()
{
	// int sscanf ( const char * s, const char * format, ...);
	//Read formatted data from string
	 //sscanf 和scanf 的不同是输入来源，前者是一个字符串，后者则是标准输入设备。
	//sscanf() 会将参数str的字符串根据参数format 字符串来转换并格式化数据
	// return value: the count of read successfully 

	// demo1
	//char str[512];
	//sscanf_s("123456 ", "%s", str, 10*(unsigned int)sizeof(char));
	//printf("str= %sn", str);
	// 打印： str= 123456n

	// demo2 
	//截取字符串中的一部分作为整数或其他类型
	//int a, b;
	//b = sscanf_s("123456abcdef", "%d", &a);
	//a++;
	//printf("%d %d", a, b);
	// 打印： 123457 1 (1是%d这种读取成功了1次就返回1)

	// demo3
	// 取指定长度的字符串 %4s？
	//char str[512];
	//sscanf_s("123456 ", "%4s", str, 10);
	//printf("str = %sn", str);
	// 打印： str = 1234n

	// demo4
	// 取到指定字符为止的字符串 如在下例中，取遇到空格为止字符串
	//char str[512];
	//sscanf_s("123456 abcdef", "%[^ ]", str, 100);
	//printf("str = %sn", str);
	// 打印： str = 123456n

	// demo5
	// 取仅包含指定字符集的字符串。如在下例中，取仅包含1到9和小写字母的字符串。
	// 是否会跳过选择到后面的小写字母呢？？ 
	//char str[512];
	//sscanf_s("123456abcdedfBCDEF", "%[1-9a-z]", str, 100);
	//printf("str = %sn", str);
	// 打印： str = 123456abcdedfn

	// demo6
	// 取到指定字符集为止的字符串。如在下例中，取遇到大写字母为止的字符串。
	//char str[512];
	//sscanf_s("123456abcdedfBCDEF", "%[^A-Z]", str, 100);
	//printf("str = %sn", str);
	// 结果： str = 123456abcdedfn
}

int main()
{
	test_sscanf();



	return 0;
}

