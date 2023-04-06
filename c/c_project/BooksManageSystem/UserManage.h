// #pragma once
#ifndef _USERMANAGE_H_
#define _USERMANAGE_H_
#include "User.h"
#include "List.h"

/*@用户管理*/
typedef struct UserManage
{
	List userlist;		// 存储所有用户的链表
	User* curUser;		// 记录当前登录的用户
}UserManage;

// 初始化管理结构
void userManage_init (UserManage* umage);

// 用户管理处理
void userManage_operation(UserManage* umage);
// 加载用户数据
void userManage_loadData(UserManage* umage, const char* filename);
// 验证登录
bool userManage_login(UserManage* umage, unsigned long long number, const char* password);
// 判断用户是否登录
bool userManage_isLogin(UserManage* umage);

//用户信息输入
void userManage_input(UserManage* umage);
//用户信息修改 
void userManage_modify(UserManage* umage);
//用户信息删除 
void userManage_remove(UserManage* umage);
//用户信息显示 
void userManage_show(UserManage* umage);
//用户密码修改
void userManage_modifyPassword(UserManage* umage);

#endif // !_USERMANAGE_H_