#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <stdio.h>

/*
* ��ʾ�û�ѡ����
* �������������ڲ�ʹ�ã�����Ҫ�ⲿʹ�� + static
*/
static int select()
{
    int op = -1;
    printf("select>");
    scanf("%d", &op);
    getchar();  // �������Ļ��иɵ�
    return op;
}

int mainMenu()
{
    printf("******************************* \n");
    printf("*    1���û�����              * \n");
    printf("*    2�����߹���              * \n");
    printf("*    3��ͼ�����              * \n");
    printf("*    4��ͼ����ͨ����          * \n");
    printf("*    5���˳�ϵͳ              * \n");
    printf("******************************* \n");

    return select();
}

int userMenu()
{
    printf("******************************* \n");
    printf("*    1���û���Ϣ����         * \n");
    printf("*    2���û���Ϣ�޸�          * \n");
    printf("*    3���û���Ϣɾ��          * \n");
    printf("*    4���û���Ϣ��ʾ          * \n");
    printf("*    5���û������޸�          * \n");
    printf("*    6���������˵�            * \n");
    printf("******************************* \n");

    return select();
}

int readerMenu()
{
    printf("******************************* \n");
    printf("*    1��������Ϣ����          * \n");
    printf("*    2��������Ϣ�޸�          * \n");
    printf("*    3��������Ϣɾ��          * \n");
    printf("*    4��������Ϣ��ʾ          * \n");
    printf("*    5�����������޸�          * \n");
    printf("*    6���������˵�            * \n");
    printf("******************************* \n");

    return select();
}

int bookMenu()
{
    printf("******************************* \n");
    printf("*    1��ͼ����Ϣ����          * \n");
    printf("*    2��ͼ����Ϣ�޸�          * \n");
    printf("*    3��ͼ����Ϣ��ѯ          * \n");
    printf("*    4������ͳ��              * \n");
    printf("*    5���������˵�            * \n");
    printf("******************************* \n");

    return select();
}

int bookSearchMenu()
{
    printf("******************************* \n");
    printf("*    1������Ų�ѯ            * \n");
    printf("*    2����������ѯ            * \n");
    printf("*    3�������߲�ѯ            * \n");
    printf("*    4�����������ѯ          * \n");
    printf("*    5�������ϼ��˵�          * \n");
    printf("******************************* \n");

    return select();
}

int bookCircluateMenu()
{
    printf("******************************* \n");
    printf("*    1�����鴦��              * \n");
    printf("*    2�����鴦��              * \n");
    printf("*    3���������˵�            * \n");
    printf("******************************* \n");

    return select();
}
