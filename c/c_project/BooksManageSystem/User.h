// #pragma once
#ifndef _USER_H_
#define _USER_H_

/*@枚举用户类型*/
enum UserType
{
	UT_SysAdminUser = 1, // 系统管理员
	UT_BookAdminUser,	 // 图书管理员
	UT_CommentUser		 // 普通用户
};
/*@用户*/
typedef struct User
{
	unsigned long long number;  // 编号
	char password[10];			// 密码
	char type;					// 类型
}User;

// 创建一个空的User
User* createEmptyUser();
// 输出用户信息
void user_print(User* user);

#endif // !_USER_H_