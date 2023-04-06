#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include "Configure.h"

Book* createEmptyBook()
{
    Book * book = calloc(1, sizeof(Book));
    if (!book)
    {
        printf("createEmptyBook failed \n");
        return NULL;
    }

    return book;
}

Book* book_fromString(const char* str)
{
    Book* book = createEmptyBook();
    int ret = sscanf(str, "%d %d %s %s %s %d %d %d %d %d", 
        &book->recordNo,&book->bookNo,book->name,book->author,book->publishingHouse,
        &book->bookCnt,&book->borrowCnt,&book->p1,&book->p2,&book->p3);
    if (ret <= 0)
    {
        printf("book_fromString failed \n");
        free(book);
        return NULL;
    }

    return book;
}

void book_print(Book* book)
{
    printf("%-8d %-5d %-10s %-10s %-10s %-6d %d", 
        book->recordNo,book->bookNo,book->name,book->author,book->publishingHouse,
        book->bookCnt,book->borrowCnt);
}
