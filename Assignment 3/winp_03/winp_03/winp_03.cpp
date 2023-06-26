#include <windows.h>
#include <TCHAR.H>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
	// UNICODE 사용시 wWinMain() 형태 	
	// hPrevInstance 이전 인스턴스 항상 0값
	// lpszCmdLine > 외부에서 (내부로) 입력받는 변수
	// nCmdShow 윈도우 출력 형태에 관련한 값
{
	HWND     hwnd;
	MSG		 msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	//height, vertical redraw
	WndClass.lpfnWndProc = WndProc;		// Proc 설정
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 형변환
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);		// WndClass 등록
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("2017253041_홍성우"),		// 타이틀바, 학번이름 체크
		WS_OVERLAPPEDWINDOW,		// 윈도우 스타일
		600, 400,					// 창출력좌표 x, y 
		600, 400,					// 창크기 x, y축
		NULL,						// 부모 윈도우
		NULL,						// 메뉴바 핸들
		hInstance,					// 인스턴스
		NULL						// 여분, NULL
	);
	ShowWindow(hwnd, nCmdShow);		// 윈도우 출력, WM_PAINT 출력내용 가져옴
	UpdateWindow(hwnd);				// WM_PAINT 출력내용 발생해서 출력하도록
									// hwnd 핸들을 통해 보여주고 갱신

	//ShowWindow(hwnd, SW_SHOW);	// 위와 같음
	//UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))	// 메시지 큐의 메시지를 가져옴
	{
		TranslateMessage(&msg);		// 키입력에 반응하는 메시지 변환, WM_KEYDOWN (키가 눌릴때) WM_CHAR 메시지 발생
		DispatchMessage(&msg);		// WndProc() 함수 호출과 WndProc()으로 메세지 전달
	}								// 종료는 WM_QUIT 발생할때 FALSE 리턴하면서 종료
	return (int)msg.wParam;			// wParam, lParam 윈도우 크기가 어떻게 변했는지, 변경된 클라이언트, 키보드, 마우스 값

}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
	//	WinDef.h 에서 정의
	//	wPram > unsigned ptr, lParam > long ptr 
{
    HDC hdc;
    PAINTSTRUCT ps;
    static int  mX, mY;
    static int circleX[4][8], circleY[4][8];
    static int circleColor[4][8];
    static int circleCount = 0;
    switch (iMsg)
    {
    case WM_CREATE:
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 8; j++)
            {
                circleX[i][j] = -100;
                circleY[i][j] = -100;
            }

        InvalidateRgn(hwnd, NULL, TRUE);
        break;
    case WM_LBUTTONDOWN:
        hdc = GetDC(hwnd);
        for (int i = 0; i < 5; i++)            
        {
            MoveToEx(hdc, 0, i * 100, NULL);
            LineTo(hdc, 800, i * 100);
        }
        for (int i = 0; i < 9; i++)
        {
            MoveToEx(hdc, i * 100, 0, NULL);
            LineTo(hdc, i * 100, 400);
        }                                 
        mX = LOWORD(lParam);
        mY = HIWORD(lParam);
        circleX[mY / 100][mX / 100] = (mX / 100) * 100;
        circleY[mY / 100][mX / 100] = (mY / 100) * 100;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 8; j++)
            {
                Ellipse(hdc, circleX[i][j], circleY[i][j], circleX[i][j] + 100, circleY[i][j] + 100);
            }
        ReleaseDC(hwnd, hdc);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        for (int i = 0; i < 5; i++)           
        {
            MoveToEx(hdc, 0, i * 100, NULL);
            LineTo(hdc, 800, i * 100);
        }
        for (int i = 0; i < 9; i++)
        {
            MoveToEx(hdc, i * 100, 0, NULL);
            LineTo(hdc, i * 100, 400);
        }                                  
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}