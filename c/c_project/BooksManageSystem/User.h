// #pragma once
#ifndef _USER_H_
#define _USER_H_

/*@ö���û�����*/
enum UserType
{
	UT_SysAdminUser = 1, // ϵͳ����Ա
	UT_BookAdminUser,	 // ͼ�����Ա
	UT_CommentUser		 // ��ͨ�û�
};
/*@�û�*/
typedef struct User
{
	unsigned long long number;  // ���
	char password[10];			// ����
	char type;					// ����
}User;

// ����һ���յ�User
User* createEmptyUser();
// ����û���Ϣ
void user_print(User* user);

#endif // !_USER_H_