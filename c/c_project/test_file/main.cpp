#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// ������ʱ�ļ�
void createTempFile()
{
	FILE *temp;
	char c;
	if ((temp = tmpfile()) != NULL)
	{
		fputs("hello ghost \n", temp); // ����ʱ�ļ�д������
	}
	rewind(temp); // �ļ�ָ�뷵���ļ���
	while ((c = fgetc(temp)) != EOF) // ��ȡ��ʱ�ļ�������
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