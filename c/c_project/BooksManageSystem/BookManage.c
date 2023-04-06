#define _CRT_SECURE_NO_WARNINGS
#include "BookManage.h"
//#include "Configure.h"
#include "Menu.h"

void bookManage_init(BookManage* bmage)
{
	SeqList_init(&bmage->books);
	bookManage_loadData(bmage, "./data/book/books.txt");
}

void bookManage_loadData(BookManage* bmage, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		perror("file open failed");
		return;
	}
	char buf[BUFSIZ] = { 0 };
	fgets(buf, BUFSIZ, fp);
	while (!feof(fp))
	{
		fgets(buf, BUFSIZ, fp);
		SeqList_pushBack(&bmage->books, book_fromString(buf));
	}

	fclose(fp);
}

void bookManage_operation(BookManage* bmage)
{
	bool isDone = false;
	while (!isDone)
	{
		int op = bookMenu();
		switch (op)
		{
		case 1:
			bookManage_input(bmage);
			break;
		case 2:
			bookManage_modify(bmage);
			break;
		case 3:
			bookManage_search(bmage);
			break;
		case 4:
			bookManage_statistics(bmage);
			break;
		case 5:
			isDone = true;
			break;
		}
	}
}

void bookManage_input(BookManage* bmage)
{

}

void bookManage_modify(BookManage* bmage)
{
}

void bookManage_search(BookManage* bmage)
{
	// 具体的查询
	bool isDone = false;
	while (!isDone)
	{
		int op = bookSearchMenu();
		switch (op)
		{
		case 1:
			bookManage_searchBookNo(bmage);
			break;
		case 2:
			bookManage_searchBookName(bmage);
			break;
		case 3:
			bookManage_searchBookAuthor(bmage);
			break;
		case 4:
			bookManage_searchBookPHouse(bmage);
			break;
		case 5:
			isDone = true;
			break;
		}
	}
}

void bookManage_statistics(BookManage* bmage)
{
}

void bookManage_searchBookNo(BookManage* bmage)
{
}

void bookManage_searchBookName(BookManage* bmage)
{
}

void bookManage_searchBookAuthor(BookManage* bmage)
{
}

void bookManage_searchBookPHouse(BookManage* bmage)
{
}
