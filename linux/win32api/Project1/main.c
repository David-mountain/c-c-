#include <windows.h>

/*
	��д���Ǻ�
	windows ������������
	�����·� WINAPI ����ʲô��˼ ������չ __stdcall �� С����������
	Windows�Ĵ��������ǻ��ڴ������������ģ�������ͬʱȷ���˴�������Ϣ�Ĵ��ڹ���-�ص�����
	��������Ƿ��ػ�
	����ԭ��
	API����ԭ�ͣ�ע��_In_˵���ò���������ģ�_opt_˵���ò����ǿ�ѡ����


*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	MessageBox(NULL, TEXT("�����ҵ�windows��һ������"), TEXT("���к�"), MB_YESNO | MB_ICONASTERISK | MB_DEFBUTTON2);
	// ������ | ֮ǰ˵������� ��2���Ʊ�ʾѡ���ɶ Ψһ��
	//˫�ַ��ַ��� DBCS
	// Unicode: ͳһ���е��ַ�ʹ�������ֽ������
	// �����й��ҵ����Զ��ŵ�һ���ַ����� ��





	return 0;
}