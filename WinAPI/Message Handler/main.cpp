#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

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
	switch (iMsg) {
	case WM_LBUTTONDOWN: {
		// DC�� �����´�
		HDC hDC = GetDC(hWnd);
		int nX = 0, nY = 0;

		// ���콺�� ��ġ�� lParam���� �����´�
		nX = LOWORD(lParam);
		nY = HIWORD(lParam);

		TextOut(hDC, nX-60, nY, TEXT("���콺 ���� Ŭ��!"), 10);
		ReleaseDC(hWnd, hDC);
		break;
	}
	case WM_MOUSEMOVE: {
		// DC�� �����´�
		HDC hDC = GetDC(hWnd);
		int nX = 0, nY = 0;

		// ���콺�� ��ġ�� lParam���� �����´�
		nX = LOWORD(lParam);
		nY = HIWORD(lParam);

		TextOut(hDC, nX - 20, nY, TEXT("����"), 2);
		ReleaseDC(hWnd, hDC);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}