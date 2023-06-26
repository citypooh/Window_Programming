#include <windows.h>
#include <TCHAR.H>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG		 msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("홍성우_2017253041"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

#define LEFT 0
#define TOP 500
#define RIGHT 300
#define BOTTOM TOP+20
#define LINE 1
#define ELLIPSE 2
#define RECTANGLE 3
int ObjectKind;
int x1, y1, x2, y2;
void Parsing(LPTSTR str)
{
	TCHAR cmd[20];
	int i;
	i = 0;
	while (*str != ' ' && *str != '(')
		cmd[i++] = *str++;
	cmd[i] = NULL;
	_stscanf_s(str, _T("(%d, %d, %d, %d)"), &x1, &y1, &x2, &y2);
	if (!_tcscmp(cmd, _T("Line")))
		ObjectKind = LINE;
	else if (!_tcscmp(cmd, _T("Ellipse")))
		ObjectKind = ELLIPSE;
	else if (!_tcscmp(cmd, _T("Rectangle")))
		ObjectKind = RECTANGLE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[100];
	static int count;
	static SIZE size;

	switch (iMsg)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 5, 15);
		ShowCaret(hwnd);
		count = 0;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Rectangle(hdc, 0, 500, 300, 520);
		GetTextExtentPoint(hdc, str, _tcslen(str), &size);
		TextOut(hdc, 0, 500, str, _tcslen(str));
		switch (ObjectKind) {
		case LINE:
			MoveToEx(hdc, x1, y1, NULL);
			LineTo(hdc, x2, y2);
			break;
		case ELLIPSE:
			Ellipse(hdc, x1, y1, x2, y2);
			break;
		case RECTANGLE:
			Rectangle(hdc, x1, y1, x2, y2);
			break;
		}
		SetCaretPos(size.cx, 500);
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		str[count++] = wParam;
		str[count] = NULL;
		if (wParam == VK_RETURN) {
			Parsing(str);
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		HideCaret(hwnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
