#include <windows.h>

/*
	大写都是宏
	windows 匈牙利命名法
	点入下方 WINAPI 代表什么意思 逆向扩展 __stdcall 等 小甲鱼有文章
	Windows的窗口类总是基于窗口类来创建的，窗口类同时确定了处理窗口消息的窗口过程-回调函数
	调整宽高是否重绘
	开闭原则
	API函数原型：注：_In_说明该参数是输入的，_opt_说明该参数是可选参数


*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	MessageBox(NULL, TEXT("这是我的windows第一个程序！"), TEXT("打招呼"), MB_YESNO | MB_ICONASTERISK | MB_DEFBUTTON2);
	// 这里用 | 之前说过的这个 用2进制表示选择的啥 唯一的
	//双字符字符集 DBCS
	// Unicode: 统一所有的字符使用两个字节来存放
	// 将所有国家的语言都放到一个字符集里 跳





	return 0;
}