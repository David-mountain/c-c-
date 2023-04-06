// #pragma once
#ifndef _BOOK_H_
#define _BOOK_H_

/*@book ͼ��*/
typedef struct Book
{
	int recordNo;		// ��¼��
	int bookNo;			// ���
	char name[20];		// ����
	char author[20];	// ����
	char publishingHouse[20]; // ������
	int bookCnt;		// ������
	int borrowCnt;		// �����
	int p1;
	int p2;
	int p3;
}Book;
// �����յ�ͼ��
Book * createEmptyBook();
// ���ַ�������book
Book * book_fromString(const char * str);
// ���ͼ����Ϣ
void book_print(Book * book);

#endif // _BOOK_H_