#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	switch (iMsg) {
	case WM_LBUTTONDOWN: {
		const unsigned int Width = 100;
		const unsigned int Height = 100;

		HDC hDC = nullptr;
		HBRUSH hMyBrush = nullptr;
		HBRUSH hOldBrush = nullptr;
		RECT rcOutput = {};

		// DC�� �� hDC�� ����
		hDC = GetDC(hWnd);

		// HS�� �� ���� ���ؼ� �� 6�� ����
		for (unsigned int i = 0; i < 6; i++) {
			// �귯���� �����ϰ�, ���� �귯���� �����Ѵ�
			hMyBrush = CreateHatchBrush(i, RGB(150, 255, 0));
			hOldBrush = reinterpret_cast<HBRUSH>(SelectObject(hDC, hMyBrush));

			// �簢���� ��, ��, ��, �� �� ��ġ�� �����Ѵ�
			rcOutput.left = 10 + ((i % 3) * (Width + 10));
			rcOutput.top = 10 + ((i / 3) * (Height + 10));
			rcOutput.right = rcOutput.left + Width;
			rcOutput.bottom = rcOutput.top + Height;

			// rcOutput�� �̿��� �簢���� �׸���
			Rectangle(hDC, rcOutput.left, rcOutput.top, rcOutput.right, rcOutput.bottom);

			// �귯���� ���� �귯���� �ٲ� ��, �귯���� �����Ѵ�.
			SelectObject(hDC, hOldBrush);
			DeleteObject(hMyBrush);
		}

		// DC�� ��ȯ�ϰ�, ����
		ReleaseDC(hWnd, hDC);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hin, HINSTANCE hPrev, PSTR cmd, int Cshow) {
	HWND hWnd;
	WNDCLASS wnd;
	MSG msg;

	// ����ü wnd�� ����� �ʱ�ȭ
	wnd.style = CS_OWNDC;
	wnd.lpfnWndProc = WndProc;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hInstance = hin;
	wnd.hIcon = LoadIcon(NULL, IDC_ICON);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = TEXT("MyWindow");

	RegisterClass(&wnd);

	// �����츦 �����Ͽ� HWND�� hWnd�� ����
	hWnd = CreateWindow(TEXT("MyWindow"), TEXT("Sample App"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, NULL, hin, NULL);

	// ��� ������ �����츦 ������
	ShowWindow(hWnd, SW_SHOW);

	// â�� �ٷ� ���� ���� �ʵ��� While�� �ݺ�
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}