#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include "List.h"
#include <stdbool.h>
#include <stdlib.h>
#include "SeqList.h"
#include "UserManage.h"
#include "BookManage.h" // 这里没有导入 导致bug

/*@管理系统*/
typedef struct ManageMent
{
	UserManage userManage;	// 用户管理模块
	BookManage bookManage;	// 图书管理模块
}ManageMent;
// 初始化
void management_init(ManageMent* m)
{
	userManage_init(&m->userManage);
	bookManage_init(&m->userManage);
}
/*
* 退出
* 描述：之所以封装函数，因为退出时需要做额外的事
*/
void management_quit()
{
	exit(0);
}
// 登录
void management_login(ManageMent* m)
{
	//登录模块
	unsigned long long number;
	char password[10] = { 0 };
	bool ret = false;  // 是否登录成功
	int loginCnt = 0;  // 尝试登录的次数 最多3次
	do
	{
		printf("账户名>");
		scanf("%llu", &number); // 123\n bug:输入账号即可登录 缓冲区遗留有个\n
		getchar();
		printf("密码>");
		gets_s(password, 10);
		// 验证登录是否成功
		ret = userManage_login(&m->userManage, number, password);
		if (ret)
		{
			printf("login sucessful \n");
			break;
		}
		else
		{
			++loginCnt;
			if (loginCnt == 3)
			{
				printf("登录失败以及三次了，程序已退出！ \n");
				exit(0);
			}
			printf("login failed, retry %d! \n", loginCnt);
		}
	} while (!ret);
}
// 操作菜单
void management_run(ManageMent* m)
{
	management_login(m);
	while (true) // 支持true 需要#include <stdbool.h>
	{
		int op = mainMenu();
		switch (op)
		{
		case 1:			// 用户管理
			userManage_operation(&m->userManage);
			break;
		case 2:			// 读者管理
			readerMenu();
			break;
		case 3:			// 图书管理
			//bookMenu();
			bookManage_operation(&m->bookManage);
			break;
		case 4:			// 图书流通管理
			bookCircluateMenu();
			break;
		case 5:			// 退出系统
			management_quit();
			break;
		}	
	}
}


//void print(variant val)
//{
//	printf("%d ", val);
//}

int main()
{
	ManageMent m;
	management_init(&m);
	management_run(&m);


	// ***********************
	/*UserManage userManage;*/
	/*userManage_init(&userManage);*/
	// ***********************

	//bookSearchMenu();
	
	// **********SeqList test*************
	//SeqList list;
	// 报错 因为 &list->size; ->优先级很高的 这里加括号 (&list)->size
	//SeqList_init(&list);
	//SeqList_pushBack(&list, 1);
	//SeqList_pushBack(&list, 2);
	//SeqList_pushBack(&list, 3);

	// foreach (int a, &list) 第一次写中间有个空格 报错 无法使用
	//foreach(int a, &list)
	//{
	//	printf("%d ", a);
	//}
	// ***********************


	// **********List test*************
	//List list;
	//list_init(&list);
	//list_pushBack(&list, 1);  // void* int
	//list_pushBack(&list, 2);
	//list_pushBack(&list, 3); 

	//list_transform(&list, print);

	//list_destory(&list);
	// ***********************

	return 0;
}