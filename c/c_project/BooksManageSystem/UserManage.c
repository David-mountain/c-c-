#define _CRT_SECURE_NO_WARNINGS
#include "UserManage.h"
#include "Menu.h"
#include <string.h>

void userManage_init(UserManage* umage)
{
	list_init(&umage->userlist);  // ��ʼ���û�����
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
	// ��ȡ����
	char buf[BUFSIZ] = { 0 };
	fgets(buf, BUFSIZ, fp);		// ��ȡ��ͷ��������
	// ��ȡ��������
	while (!feof(fp))
	{
		fgets(buf, BUFSIZ, fp);
		// ����ַ���
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
	// ����number��password�Ƿ����
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
	bool isDone = false;	// �Ƿ��˳�
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
		case 6:			// �Ƿ񷵻����˵�
			isDone = true;
			break;
		}
	}
	

}

void userManage_input(UserManage* umage)
{
	printf("�������û�(ID ���� ����)>");
	User * user = createEmptyUser();
	int ret = scanf("%llu %s %d", &user->number, user->password, &user->type);
	if (ret == 3)
	{
		printf("�û���ӳɹ���\n");
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
	printf("��������Ҫ�޸ĵ��û�ID> \n");
	unsigned long long number = -1;
	scanf("%llu", &number);
	// ����IDΪnumber���û�
	User * user = list_find(&umage->userlist, user_cmp, number);
	if (!user)
	{
		printf("�Բ�����Ҫ�޸ĵ��û������ڣ�\n");
		return;
	}
	printf("��������Ҫ�µ��û�����(1 2 3)>");
	if (scanf("%d", &user->type) == 1)
	{
		printf("�û��޸ĳɹ���");
	}
}

void userManage_remove(UserManage* umage)
{
	printf("��������Ҫɾ�����û�ID> \n");
	unsigned long long number = -1;
	scanf("%llu", &number);
	// ����IDΪnumber���û�
	User * user = list_find(&umage->userlist, user_cmp, number);
	if (!user)
	{
		printf("�Բ�����Ҫɾ�����û������ڣ�\n");
		return;
	}
	list_removeOne(&umage->userlist, user);
	printf("�û�ɾ���ɹ� \n");
}

void userManage_show(UserManage* umage)
{
	//printf("�û�ID\t  �û�����   �û����� \n");
	printf("%-10s %-10s %s \n", "�û�ID","�û�����","�û�����");
	list_transform(&umage->userlist, user_print); 
}

void userManage_modifyPassword(UserManage* umage)
{
	// ��¼֮������޸�
	if (!userManage_isLogin(umage))
	{
		printf("����û�е�¼�����¼�����ԣ�\n");
		return;
	}

	printf("������������>");
	gets_s(umage->curUser->password, 10);
	printf("�����޸ĳɹ�������������Ϊ��%s \n", umage->curUser->password);
}

