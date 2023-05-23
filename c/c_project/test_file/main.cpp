#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 创建临时文件
void createTempFile()
{
	FILE *temp;
	char c;
	if ((temp = tmpfile()) != NULL)
	{
		fputs("hello ghost \n", temp); // 向临时文件写入内容
	}
	rewind(temp); // 文件指针返回文件首
	while ((c = fgetc(temp)) != EOF) // 读取临时文件中内容
		printf("%c", c);
	fclose(temp);
}

int Rename_File(const char* src_name, const char* dst_name)
{
	FILE *fp = fopen(src_name, "r");
	if (fp != nullptr)
	{
		rename(src_name, dst_name);
		fclose(fp);
	}
	return 0;
}

int main()
{
	Rename_File("d:/testRename", "d:/testtestname");


	return 0;
}