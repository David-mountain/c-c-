// #pragma once
#ifndef _BOOKMANAGEMENT_H_
#define _BOOKMANAGE_H_
#include "SeqList.h"
#include "Book.h"

/*@ͼ�����*/
typedef struct BookManage
{
	SeqList books;		// ͼ��˳���
}BookManage;

// ��ʼ��ͼ�����
void bookManage_init (BookManage* bmage);
// ��������
void bookManage_loadData(BookManage* bmage, const char* filename);
// ����
void bookManage_operation(BookManage* bmage);
// ͼ����Ϣ����
void bookManage_input (BookManage* bmage);
//ͼ����Ϣ�޸�
void bookManage_modify (BookManage* bmage);
//ͼ����Ϣ��ѯ
void bookManage_search (BookManage* bmage);
//����ͳ��
void bookManage_statistics (BookManage* bmage);
// ����Ų�ѯ
void bookManage_searchBookNo(BookManage* bmage);
//��������ѯ 
void bookManage_searchBookName(BookManage* bmage);
//�����߲�ѯ
void bookManage_searchBookAuthor(BookManage* bmage);
//���������ѯ 
void bookManage_searchBookPHouse(BookManage* bmage);

#endif // !_BOOKMANAGE_H_