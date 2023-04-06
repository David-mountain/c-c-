#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <stdio.h>

/*
* 提示用户选择函数
* 描述：仅仅是内部使用，不想要外部使用 + static
*/
static int select()
{
    int op = -1;
    printf("select>");
    scanf("%d", &op);
    getchar();  // 缓冲区的换行干掉
    return op;
}

int mainMenu()
{
    printf("******************************* \n");
    printf("*    1、用户管理              * \n");
    printf("*    2、读者管理              * \n");
    printf("*    3、图书管理              * \n");
    printf("*    4、图书流通管理          * \n");
    printf("*    5、退出系统              * \n");
    printf("******************************* \n");

    return select();
}

int userMenu()
{
    printf("******************************* \n");
    printf("*    1、用户信息输入         * \n");
    printf("*    2、用户信息修改          * \n");
    printf("*    3、用户信息删除          * \n");
    printf("*    4、用户信息显示          * \n");
    printf("*    5、用户密码修改          * \n");
    printf("*    6、返回主菜单            * \n");
    printf("******************************* \n");

    return select();
}

int readerMenu()
{
    printf("******************************* \n");
    printf("*    1、读者信息输入          * \n");
    printf("*    2、读者信息修改          * \n");
    printf("*    3、读者信息删除          * \n");
    printf("*    4、读者信息显示          * \n");
    printf("*    5、读者密码修改          * \n");
    printf("*    6、返回主菜单            * \n");
    printf("******************************* \n");

    return select();
}

int bookMenu()
{
    printf("******************************* \n");
    printf("*    1、图书信息输入          * \n");
    printf("*    2、图书信息修改          * \n");
    printf("*    3、图书信息查询          * \n");
    printf("*    4、汇总统计              * \n");
    printf("*    5、返回主菜单            * \n");
    printf("******************************* \n");

    return select();
}

int bookSearchMenu()
{
    printf("******************************* \n");
    printf("*    1、按书号查询            * \n");
    printf("*    2、按书名查询            * \n");
    printf("*    3、按作者查询            * \n");
    printf("*    4、按出版社查询          * \n");
    printf("*    5、返回上级菜单          * \n");
    printf("******************************* \n");

    return select();
}

int bookCircluateMenu()
{
    printf("******************************* \n");
    printf("*    1、借书处理              * \n");
    printf("*    2、还书处理              * \n");
    printf("*    3、返回主菜单            * \n");
    printf("******************************* \n");

    return select();
}
