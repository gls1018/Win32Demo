//Windows
#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <tchar.h>
#include <Uxtheme.h>
#include <shellscalingapi.h>
#include <CommCtrl.h>
#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "Comctl32.lib")

//C++
#include <print>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <chrono>
#include <thread>
#include <iostream>

// C
#include <stdio.h>
#include <stdlib.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara);

int wWinMain(HINSTANCE hIns, HINSTANCE hPre, LPWSTR lpCmdLine, int nShow)
{
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);

	WNDCLASSEX wc{ 0 };
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = _T("MyWindowClass");
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClassEx(&wc);

	//创建窗口
	DWORD dwExStyle = WS_EX_ACCEPTFILES;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	HWND hWnd = CreateWindowEx(dwExStyle, _T("MyWindowClass"), _T("WinApp"), dwStyle, 100, 300, 800, 500, NULL, NULL, hIns, NULL);

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


HWND hEdit1;
HWND hEdit2;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			LPCREATESTRUCT lpst = (LPCREATESTRUCT)lPara;
			hEdit1 = CreateWindow(L"Edit", NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | ES_MULTILINE, 
								  30, 30, 200, 50, hWnd, (HMENU)0x1001, (lpst)->hInstance, 0);


		}break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, msg, wPara, lPara);
	}
}

