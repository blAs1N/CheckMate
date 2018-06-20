#include <Windows.h>
#include <tchar.h>
#include <string>

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
	hWnd = CreateWindow(TEXT("MyWindow"), TEXT("�׸���"),
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
	// ���콺�� Ŭ�� ������ Ȯ���ϴ� ����
	static bool bMouseDown = false;
	// ���� ���⸦ ������ ����
	static int thickness = 3;
	// ���� ���� ������ ����
	static COLORREF color = RGB(0, 0, 0);

	switch (iMsg) {
	// ���콺�� ������ ���� �׸��� ���� �׸��� �ʴ´�
	case WM_LBUTTONDOWN: {
		HDC hDC = GetDC(hWnd);

		bMouseDown = true;
		MoveToEx(hDC, LOWORD(lParam), HIWORD(lParam), nullptr);
		ReleaseDC(hWnd, hDC);
		break;
	}
	case WM_LBUTTONUP:
		bMouseDown = false;
		break;
	case WM_MOUSEMOVE: {
		if (bMouseDown) {
			HDC hDC = GetDC(hWnd);
			HPEN hMyPen = nullptr;
			HPEN hOldPen = nullptr;

			hMyPen = CreatePen(PS_SOLID, thickness, color);
			hOldPen = reinterpret_cast<HPEN>(SelectObject(hDC, hMyPen));

			LineTo(hDC, LOWORD(lParam), HIWORD(lParam));
			ReleaseDC(hWnd, hDC);
		}
		break;
	}
	// ���콺 ���� �����̸� ���� ���⸦ �����Ѵ�
	case WM_MOUSEWHEEL: {
		// ���� ������ ���� ��´�
		int wheelMove = GET_WHEEL_DELTA_WPARAM(wParam);

		// ���� �����̸� ���⸦ �����Ѵ�
		thickness += wheelMove > 0 ? 1 : -1;

		// ������ ������ �д�
		if (thickness > 40) { thickness = 40; }
		else if (thickness < 1) { thickness = 1; }
		break;
	}
	// ������ �����ϴ� Ű
	case WM_KEYDOWN: {
		HDC hDC = GetDC(hWnd);
		TCHAR key = wParam;

		// q�� ���� ��, w�� ���� ��, e�� �Ķ� ��,  r�� �ʷϻ�
		switch (key)
		{
		case 'Q':
			color = RGB(0, 0, 0);
			break;
		case 'W':
			color = RGB(255, 0, 0);
			break;
		case 'E':
			color = RGB(0, 0, 255);
			break;
		case 'R':
			color = RGB(0, 255, 0);
			break;
		}
		
		break;
	}
	// X Ű�� ������ �����Ѵ�
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}