#include <Windows.h>
#include <tchar.h>

int WINAPI WinMain(HINSTANCE hin, HINSTANCE prev, PSTR CLine, int CShow) {
	// blAs1N�̶�� ������ ������ Hello, world!�� ����ϰ� Ȯ�� ��ư�� �ִ� �޼��� �ڽ�
	MessageBox(NULL, _T("Hello, world!"), _T("blAs1N"), MB_OK);
	return 0;
}