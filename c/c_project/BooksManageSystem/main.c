#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include "List.h"
#include <stdbool.h>
#include <stdlib.h>
#include "SeqList.h"
#include "UserManage.h"
#include "BookManage.h" // ����û�е��� ����bug

/*@����ϵͳ*/
typedef struct ManageMent
{
	UserManage userManage;	// �û�����ģ��
	BookManage bookManage;	// ͼ�����ģ��
}ManageMent;
// ��ʼ��
void management_init(ManageMent* m)
{
	userManage_init(&m->userManage);
	bookManage_init(&m->userManage);
}
/*
* �˳�
* ������֮���Է�װ��������Ϊ�˳�ʱ��Ҫ���������
*/
void management_quit()
{
	exit(0);
}
// ��¼
void management_login(ManageMent* m)
{
	//��¼ģ��
	unsigned long long number;
	char password[10] = { 0 };
	bool ret = false;  // �Ƿ��¼�ɹ�
	int loginCnt = 0;  // ���Ե�¼�Ĵ��� ���3��
	do
	{
		printf("�˻���>");
		scanf("%llu", &number); // 123\n bug:�����˺ż��ɵ�¼ �����������и�\n
		getchar();
		printf("����>");
		gets_s(password, 10);
		// ��֤��¼�Ƿ�ɹ�
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
				printf("��¼ʧ���Լ������ˣ��������˳��� \n");
				exit(0);
			}
			printf("login failed, retry %d! \n", loginCnt);
		}
	} while (!ret);
}
// �����˵�
void management_run(ManageMent* m)
{
	management_login(m);
	while (true) // ֧��true ��Ҫ#include <stdbool.h>
	{
		int op = mainMenu();
		switch (op)
		{
		case 1:			// �û�����
			userManage_operation(&m->userManage);
			break;
		case 2:			// ���߹���
			readerMenu();
			break;
		case 3:			// ͼ�����
			//bookMenu();
			bookManage_operation(&m->bookManage);
			break;
		case 4:			// ͼ����ͨ����
			bookCircluateMenu();
			break;
		case 5:			// �˳�ϵͳ
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
	// ���� ��Ϊ &list->size; ->���ȼ��ܸߵ� ��������� (&list)->size
	//SeqList_init(&list);
	//SeqList_pushBack(&list, 1);
	//SeqList_pushBack(&list, 2);
	//SeqList_pushBack(&list, 3);

	// foreach (int a, &list) ��һ��д�м��и��ո� ���� �޷�ʹ��
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