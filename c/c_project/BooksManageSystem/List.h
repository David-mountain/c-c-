// #pragma once
#ifndef _LIST_H_
#define _LIST_H_

#include "Configure.h"
/*@����*/
// �û� ���� ͼ�� ͼ����ͨ
// void* ����ָ������
// ������������
//typedef void* variant;
/*@�ڵ�����*/
typedef struct Node
{
	variant data;		// ָ�����ݵ�ָ��
	struct Node* next;  // ָ����һ���ڵ��ָ��
}Node;
/*@��װ����*/
typedef struct List
{
	int size;     // Ԫ�ظ���(Ԫ�ؽڵ����)
	Node* front;  // ͷָ��
	Node* tail;   // βָ��
}List;

// �ص��������� (ע�⿴����������� �ٺ�
typedef void (*LISTCALLBACK)(variant);

// ��ʼ������
void list_init(List* list);
// ����Ԫ��(β�巨)
void list_pushBack(List* list, variant val);
// ɾ��Ԫ��
void list_removeOne(List* list, variant val);
// ʹ�ûص���������ÿ������
void list_transform(List* list, LISTCALLBACK callBack);
// ��������
void list_destory(List* list);

// ����
typedef bool (*CMPCALLBACK)(variant, variant);
variant list_find(List* list, CMPCALLBACK cmp, variant val);

#endif // !_LIST_H_
