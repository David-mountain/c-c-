// #pragma once
#ifndef _LIST_H_
#define _LIST_H_

#include "Configure.h"
/*@链表*/
// 用户 读者 图书 图书流通
// void* 万能指针类型
// 抽象数据类型
//typedef void* variant;
/*@节点类型*/
typedef struct Node
{
	variant data;		// 指向数据的指针
	struct Node* next;  // 指向下一个节点的指针
}Node;
/*@封装链表*/
typedef struct List
{
	int size;     // 元素个数(元素节点个数)
	Node* front;  // 头指针
	Node* tail;   // 尾指针
}List;

// 回调函数类型 (注意看懂下面这个哈 嘿嘿
typedef void (*LISTCALLBACK)(variant);

// 初始化链表
void list_init(List* list);
// 插入元素(尾插法)
void list_pushBack(List* list, variant val);
// 删除元素
void list_removeOne(List* list, variant val);
// 使用回调函数处理每个数据
void list_transform(List* list, LISTCALLBACK callBack);
// 销毁链表
void list_destory(List* list);

// 查找
typedef bool (*CMPCALLBACK)(variant, variant);
variant list_find(List* list, CMPCALLBACK cmp, variant val);

#endif // !_LIST_H_
