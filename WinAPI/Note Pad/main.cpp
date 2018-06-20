#include <Windows.h>
#include <tchar.h>
#include <string>

typedef std::basic_string<TCHAR> string;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void Print(HWND hWnd, string tstr, int fontSize);

int APIENTRY _tWinMain(HINSTANCE hin, HINSTANCE hPrev, LPTSTR cmd, int Cshow) {
	HWND hWnd;
	WNDCLASS wnd;
	MSG msg;

	// wnd�� ��� �ʱ�ȭ
	wnd.style = CS_OWNDC;
	wnd.lpfnWndProc = WndProc;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hInstance = hin;
	wnd.hIcon = LoadIcon(NULL, IDC_ICON);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = TEXT("MyWindow");

	RegisterClass(&wnd);

	// ������ ���� -> hWnd�� ����
	hWnd = CreateWindow(TEXT("MyWindow"), TEXT("Message Handler"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, NULL, hin, NULL);

	// �����츦 ���̰� ��
	ShowWindow(hWnd, SW_SHOW);

	// â�� �ٷ� ���� ���� �ʵ��� While�� �ݺ�
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static int fontSize = 100;
	static std::basic_string<TCHAR> tstr;

	switch (iMsg) {
	case WM_CHAR: {
		if (wParam != VK_BACK)
			tstr += static_cast<TCHAR>(wParam);
		else
			if (!(tstr.empty()))
				tstr.erase(tstr.end() - 1, tstr.end());
		Print(hWnd, tstr, fontSize);
		break;
	}
	case WM_MOUSEWHEEL: {
		// ���� ������ ���� ��´�
		int wheelMove = GET_WHEEL_DELTA_WPARAM(wParam);

		// ���� �����̸� ���⸦ �����Ѵ�
		fontSize += wheelMove > 0 ? 1 : -1;

		// ������ ������ �д�
		if (fontSize > 200) { fontSize = 200; }
		else if (fontSize < 1) { fontSize = 1; }

		// �ٲ� ���⸦ �����Ѵ�
		Print(hWnd, tstr, fontSize);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

// �޸��忡 ���
void Print(HWND hWnd, string tstr, int fontSize) {
	HDC hDC = GetDC(hWnd);
	HFONT hMyFont = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, TEXT("consolas"));
	HFONT hOldFont = reinterpret_cast<HFONT>(SelectObject(hDC, hMyFont));

	TextOut(hDC, 10, 10, tstr.c_str(), tstr.length());

	ReleaseDC(hWnd, hDC);
}