#include <windows.h>
#include <iostream>
#include <print>
#pragma warning(disable: 28251)
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")

/*
这个 Demo 演示了操作 INI 文件

该 INI 配置文件保存了程序的下列信息:

(x, y): 窗口坐标
(Heght, Width): 窗口高度和宽度.

CloseBehavor: 点击x号时的行为, 最小化到系统托盘，还是关闭程序

*/



LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara)
{
	switch (msg)
	{
		case WM_SYSCOMMAND:
		{
			switch (wPara & 0xFFF0)
			{
				case SC_CLOSE:
				{
					std::cout << "SC_CLOSE\n";
				}break;

				case SC_MAXIMIZE:
				{
					std::cout << "SC_MAXIMIZE\n";
				}break;

				case SC_MINIMIZE:
				{
					std::cout << "SC_MINIMIZE\n";
				}break;

				case SC_RESTORE:
				{
					std::cout << "SC_RESTORE\n";
				}break;

				case SC_SIZE:
				{
					std::cout << "SC_SIZE\n";
				}break;

				case SC_MOVE:
				{
					std::cout << "SC_MOVE\n";
				}break;

				default:
					return DefWindowProcW(hWnd, msg, wPara, lPara);
			}
		}break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;

		case WM_MOUSEMOVE:
		{
			static DWORD dwCount = 0;
			std::cout << "WM_MOVE: " << ++dwCount << "\n";
		}break;

		default:
			return DefWindowProcW(hWnd, msg, wPara, lPara);
	}
	return DefWindowProcW(hWnd, msg, wPara, lPara);
}

int main()
{

	HINSTANCE hInstance = GetModuleHandleW(NULL);


	WNDCLASSEX wc{ 0 };
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = MainWindowProc;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClassEx(&wc);

	//创建窗口
	DWORD dwExStyle = WS_EX_ACCEPTFILES;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	HWND hWnd = CreateWindowExW(dwExStyle, L"MyWindowClass", L"WinApp", dwStyle, 100, 300, 800, 500, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	//消息循环
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
