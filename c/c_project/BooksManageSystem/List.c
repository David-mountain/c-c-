#include "List.h"
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

static bool isValid(List* list)
{
	if (list == NULL)
		printf("list invalid \n");
	return list != NULL;
}

Node* createNode(variant val)
{
	Node* newNode = calloc(1, sizeof(Node));
	if (!newNode)
	{
		printf("createNode failed \n");
		return NULL;
	}
	newNode->data = val;
	return newNode;
}

void list_init(List* list)
{
	if (!isValid(list))
	{
		return;
	}

	// ����ͷ�ڵ�
	list->front = list->tail = calloc(1, sizeof(Node));
	if (!list->front)
	{
		printf("head Node calloc failed \n");
		return;
	}
	list->size = 0;
}

void list_pushBack(List* list, variant val)
{
	if (!isValid(list))
		return;

	Node * newNode = createNode(val);
	// β��
	list->tail->next = newNode;
	list->tail = newNode;
	list->size++;
}

void list_removeOne(List* list, variant val)
{
	if (!isValid(list))
		return;

	// ɾ��val
	Node* curNode = list->front->next;  // ָ����Ԫ�ڵ�
	Node* prevNode = list->front;
	while (curNode)
	{
		// �ҵ���Ҫɾ����Ԫ��
		if (curNode->data == val)
		{
			break;
		}
		prevNode = curNode;
		curNode = curNode->next;
	}
	// curNode ����Ҫɾ���Ľڵ�
	if (curNode)
	{
		prevNode->next = curNode->next;
		free(curNode);
	 }
}

void list_transform(List* list, LISTCALLBACK callBack)
{
	if (!isValid(list))
		return;

	// �������� ����callback����
	Node* curNode = list->front->next;
	while (curNode)
	{
		callBack(curNode->data);
		curNode = curNode->next;
	}
}

void list_destory(List* list) {
	if (!isValid(list))
		return;

	Node* curNode = list->front;	// ָ��ͷ�ڵ�
	Node* nextNode = curNode->next; // ָ����Ԫ�ڵ�
	while (curNode)
	{
		free(curNode);
		curNode = nextNode;
		if (curNode == NULL)
			break;
		nextNode = curNode->next; 
	}
}

variant list_find(List* list, CMPCALLBACK cmp, variant val)
{
	Node* curNode = list->front->next;
	while (curNode)
	{
		if (cmp(curNode, val))
		{
			return curNode;
		}
		curNode = curNode->next;
	}
	return NULL;
}
