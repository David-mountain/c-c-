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

	// 申请头节点
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
	// 尾插
	list->tail->next = newNode;
	list->tail = newNode;
	list->size++;
}

void list_removeOne(List* list, variant val)
{
	if (!isValid(list))
		return;

	// 删除val
	Node* curNode = list->front->next;  // 指向首元节点
	Node* prevNode = list->front;
	while (curNode)
	{
		// 找到了要删除的元素
		if (curNode->data == val)
		{
			break;
		}
		prevNode = curNode;
		curNode = curNode->next;
	}
	// curNode 就是要删除的节点
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

	// 遍历链表 调用callback函数
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

	Node* curNode = list->front;	// 指向头节点
	Node* nextNode = curNode->next; // 指向首元节点
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
