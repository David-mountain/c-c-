// #pragma once 这玩意就是头文件的条件编译 不是所有都支持

#ifndef _MENMU_H_
#define _MENU_H_
/*@菜单*/

// 主菜单
int mainMenu();
// 用户管理菜单
int userMenu();
// 读者管理菜单
int readerMenu();
// 图书管理菜单
int bookMenu();
// 图书查询菜单
int bookSearchMenu();
// 图书流通菜单
int bookCircluateMenu();


#endif // !_MENMU_H_
