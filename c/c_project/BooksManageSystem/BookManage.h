// #pragma once
#ifndef _BOOKMANAGEMENT_H_
#define _BOOKMANAGE_H_
#include "SeqList.h"
#include "Book.h"

/*@图书管理*/
typedef struct BookManage
{
	SeqList books;		// 图书顺序表
}BookManage;

// 初始化图书管理
void bookManage_init (BookManage* bmage);
// 加载数据
void bookManage_loadData(BookManage* bmage, const char* filename);
// 操作
void bookManage_operation(BookManage* bmage);
// 图书信息输入
void bookManage_input (BookManage* bmage);
//图书信息修改
void bookManage_modify (BookManage* bmage);
//图书信息查询
void bookManage_search (BookManage* bmage);
//汇总统计
void bookManage_statistics (BookManage* bmage);
// 按书号查询
void bookManage_searchBookNo(BookManage* bmage);
//按书名查询 
void bookManage_searchBookName(BookManage* bmage);
//按作者查询
void bookManage_searchBookAuthor(BookManage* bmage);
//按出版社查询 
void bookManage_searchBookPHouse(BookManage* bmage);

#endif // !_BOOKMANAGE_H_