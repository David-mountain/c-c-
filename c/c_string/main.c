#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void test_fprintf()
{
	//Formatted input/output ��ʽ���������
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
	// %-10.10s ??? -�����  -10��ʾ ���10�ַ������ű�ʾ����10�ַ�ʱ����� 
	// ��ߵ�.10��ʾ������10�ַ�ʱ���ϡ�
	
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
	fprintf(pFile, "%d %d", 111, 99); // ��Ȼ����� �Ҿ���˼����������������ݵ� ��������ϵ�
						// fscanf�����ո�ͻ���ʱ������ע��ո�ʱҲ������ %d%d�����ӡ   %d %d
	rewind(pFile);
	int a = fscanf(pFile, "%f", &f);
	int b = fscanf(pFile, "%s", str);
	fclose(pFile);
	printf("I have read: %f and %s \n", f, str);
	// rewind�������õ�ͬ�� (void)fseek(stream, 0L, SEEK_SET); �� ��: void rewind(FILE *stream);
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
	// %d plus %d is %d 13��
}

void test_sscanf()
{
	// int sscanf ( const char * s, const char * format, ...);
	//Read formatted data from string
	 //sscanf ��scanf �Ĳ�ͬ��������Դ��ǰ����һ���ַ������������Ǳ�׼�����豸��
	//sscanf() �Ὣ����str���ַ������ݲ���format �ַ�����ת������ʽ������
	// return value: the count of read successfully 

	// demo1
	//char str[512];
	//sscanf_s("123456 ", "%s", str, 10*(unsigned int)sizeof(char));
	//printf("str= %sn", str);
	// ��ӡ�� str= 123456n

	// demo2 
	//��ȡ�ַ����е�һ������Ϊ��������������
	//int a, b;
	//b = sscanf_s("123456abcdef", "%d", &a);
	//a++;
	//printf("%d %d", a, b);
	// ��ӡ�� 123457 1 (1��%d���ֶ�ȡ�ɹ���1�ξͷ���1)

	// demo3
	// ȡָ�����ȵ��ַ��� %4s��
	//char str[512];
	//sscanf_s("123456 ", "%4s", str, 10);
	//printf("str = %sn", str);
	// ��ӡ�� str = 1234n

	// demo4
	// ȡ��ָ���ַ�Ϊֹ���ַ��� ���������У�ȡ�����ո�Ϊֹ�ַ���
	//char str[512];
	//sscanf_s("123456 abcdef", "%[^ ]", str, 100);
	//printf("str = %sn", str);
	// ��ӡ�� str = 123456n

	// demo5
	// ȡ������ָ���ַ������ַ��������������У�ȡ������1��9��Сд��ĸ���ַ�����
	// �Ƿ������ѡ�񵽺����Сд��ĸ�أ��� 
	//char str[512];
	//sscanf_s("123456abcdedfBCDEF", "%[1-9a-z]", str, 100);
	//printf("str = %sn", str);
	// ��ӡ�� str = 123456abcdedfn

	// demo6
	// ȡ��ָ���ַ���Ϊֹ���ַ��������������У�ȡ������д��ĸΪֹ���ַ�����
	//char str[512];
	//sscanf_s("123456abcdedfBCDEF", "%[^A-Z]", str, 100);
	//printf("str = %sn", str);
	// ����� str = 123456abcdedfn
}

int main()
{
	test_sscanf();



	return 0;
}

