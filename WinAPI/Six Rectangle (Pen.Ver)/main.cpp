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
	wnd.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(DKGRAY_BRUSH));
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = TEXT("MyWindow");

	RegisterClass(&wnd);

	// ������ ���� -> hWnd�� ����
	hWnd = CreateWindow(TEXT("MyWindow"), TEXT("Six Rectangle (Pen.Ver)"),
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
		// ���̿� ���̸� ����� ����
		const unsigned int Width = 100;
		const unsigned int Height = 100;

		// DC, HPEN 2��, HBRUSH 2��, HFON 2��, �簢�� ����
		HDC hDC = nullptr;
		HPEN hMyPen = nullptr;
		HPEN hOldPen = nullptr;
		HBRUSH hMyBrush = nullptr;
		HBRUSH hOldBrush = nullptr;
		HFONT hMyFont = nullptr;
		HFONT hOldFont = nullptr;
		RECT rcOutput = {};

		// DC�� �� hDC�� ����
		hDC = GetDC(hWnd);

		for (unsigned int i = 0; i < 6; i++) {
			// ��� �귯�ø� ���ʴ�� ����, ���� ���� ����
			hMyPen = CreatePen(i, 1, RGB(0, 255, 0));
			hOldPen = reinterpret_cast<HPEN>(SelectObject(hDC, hMyPen));

			hMyBrush = CreateSolidBrush(RGB(30, 170, 255));
			hOldBrush = reinterpret_cast<HBRUSH>(SelectObject(hDC, hMyBrush));

			hMyFont = CreateFont(100, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, TEXT("Hack"));
			hOldFont = reinterpret_cast<HFONT>(SelectObject(hDC, hMyFont));

			// �簢���� ��, ��, ��, �� �� ��ġ�� �����Ѵ�
			rcOutput.left = 10 + ((i % 3) * (Width + 10));
			rcOutput.top = 120 + ((i / 3) * (Height + 10));
			rcOutput.right = rcOutput.left + Width;
			rcOutput.bottom = rcOutput.top + Height;

			// �簢���� �׸�
			Rectangle(hDC, rcOutput.left, rcOutput.top, rcOutput.right, rcOutput.bottom);
			TextOut(hDC, 10, 10, TEXT("blAs1N"), 6);

			// GDI ���� (�������� ���� �� ����)
			SelectObject(hDC, hOldPen);
			DeleteObject(hMyPen);

			SelectObject(hDC, hOldBrush);
			DeleteObject(hMyBrush);

			SelectObject(hDC, hOldFont);
			DeleteObject(hMyFont);
		}

		// hDC�� ��ȯ
		ReleaseDC(hWnd, hDC);

		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}