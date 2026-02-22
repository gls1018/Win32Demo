#include "./common.h"
#pragma warning(disable: 28251)


int _tWinMain(HINSTANCE hIns, HINSTANCE hPre, LPTSTR lpCMDLine, int nShow)
{
	hInstance = hIns;

	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);

	//定义窗口 && 注册装口
	WNDCLASSEX wc{ 0 };
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = _T("MyWindowClass");
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClassEx(&wc);


	//创建窗口
	DWORD dwExStyle = WS_EX_ACCEPTFILES;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	hMainWindow= CreateWindowEx(dwExStyle, _T("MyWindowClass"), _T("WinApp"), dwStyle, 100, 300, 800, 500, NULL, NULL, hIns, NULL);
	
	ShowWindow(hMainWindow,SW_NORMAL);
	UpdateWindow(hMainWindow);


	//消息循环
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}