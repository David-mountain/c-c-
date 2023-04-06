// #pragma once
#ifndef _BOOK_H_
#define _BOOK_H_

/*@book 图书*/
typedef struct Book
{
	int recordNo;		// 记录号
	int bookNo;			// 书号
	char name[20];		// 书名
	char author[20];	// 作者
	char publishingHouse[20]; // 出版社
	int bookCnt;		// 藏书量
	int borrowCnt;		// 借出数
	int p1;
	int p2;
	int p3;
}Book;
// 创建空的图书
Book * createEmptyBook();
// 从字符串创建book
Book * book_fromString(const char * str);
// 输出图书信息
void book_print(Book * book);

#endif // _BOOK_H_