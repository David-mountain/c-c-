#define _CRT_SECURE_NO_WARNINGS
#include "UserManage.h"
#include "Menu.h"
#include <string.h>

void userManage_init(UserManage* umage)
{
	list_init(&umage->userlist);  // 初始化用户链表
	umage->curUser = NULL;
	userManage_loadData(umage, "./data/user.txt");
}

// data: book cirulate.txt reader.txt user.txt 
void userManage_loadData(UserManage* umage, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		perror("file open failed");
		return;
	}
	// 获取数据
	char buf[BUFSIZ] = { 0 };
	fgets(buf, BUFSIZ, fp);		// 读取表头，并丢弃
	// 获取真正数据
	while (!feof(fp))
	{
		fgets(buf, BUFSIZ, fp);
		// 拆分字符串
		User* user = createEmptyUser();
		int ret = sscanf(buf, "%llu %s %d", &user->number, user->password, &user->type);
		if (ret <= 0)
		{
			printf("sscanf failed \n");
			free(user);
			break;
		}
		list_pushBack(&umage->userlist, user);
	}

	fclose(fp);
}

static bool cmpUser(User* u1, User* u2)
{
	return ((u1->number == u2->number) && (strcmp(u1->password, u2->password) == 0));
}
bool userManage_login(UserManage* umage, unsigned long long number, const char* password)
{
	User u;
	u.number = number;
	strcpy(u.password, password);
	// 查找number和password是否存在
	User * user = list_find(&umage->userlist, cmpUser, &u);	
	if (!user)
	{
		return false;
	}
	umage->curUser = user;
	return true;
}

bool userManage_isLogin(UserManage* umage)
{
	return umage->curUser != NULL;
}

void userManage_operation(UserManage* umage)
{
	bool isDone = false;	// 是否退出
	while (!isDone)
	{
		int op = userMenu();
		switch (op)
		{
		case 1:
			userManage_input(umage);
			break;
		case 2:
			userManage_modify(umage);
			break;
		case 3:
			userManage_remove(umage);
			break;
		case 4:
			userManage_show(umage);
			break;
		case 5:
			userManage_modifyPassword(umage);
			break;
		case 6:			// 是否返回主菜单
			isDone = true;
			break;
		}
	}
	

}

void userManage_input(UserManage* umage)
{
	printf("请输入用户(ID 密码 类型)>");
	User * user = createEmptyUser();
	int ret = scanf("%llu %s %d", &user->number, user->password, &user->type);
	if (ret == 3)
	{
		printf("用户添加成功！\n");
		list_pushBack(&umage->userlist, user);
	}
}

bool user_cmp(variant v1, variant v2)
{
	User * user = v1;
	unsigned long long number = v2;

	return user->number == number;

}
void userManage_modify(UserManage* umage)
{
	printf("请输入您要修改的用户ID> \n");
	unsigned long long number = -1;
	scanf("%llu", &number);
	// 查找ID为number的用户
	User * user = list_find(&umage->userlist, user_cmp, number);
	if (!user)
	{
		printf("对不起，您要修改的用户不存在！\n");
		return;
	}
	printf("请输入需要新的用户类型(1 2 3)>");
	if (scanf("%d", &user->type) == 1)
	{
		printf("用户修改成功！");
	}
}

void userManage_remove(UserManage* umage)
{
	printf("请输入您要删除的用户ID> \n");
	unsigned long long number = -1;
	scanf("%llu", &number);
	// 查找ID为number的用户
	User * user = list_find(&umage->userlist, user_cmp, number);
	if (!user)
	{
		printf("对不起，您要删除的用户不存在！\n");
		return;
	}
	list_removeOne(&umage->userlist, user);
	printf("用户删除成功 \n");
}

void userManage_show(UserManage* umage)
{
	//printf("用户ID\t  用户密码   用户类型 \n");
	printf("%-10s %-10s %s \n", "用户ID","用户密码","用户类型");
	list_transform(&umage->userlist, user_print); 
}

void userManage_modifyPassword(UserManage* umage)
{
	// 登录之后才能修改
	if (!userManage_isLogin(umage))
	{
		printf("您还没有登录，请登录后重试！\n");
		return;
	}

	printf("请输入新密码>");
	gets_s(umage->curUser->password, 10);
	printf("密码修改成功，您的新密码为：%s \n", umage->curUser->password);
}

