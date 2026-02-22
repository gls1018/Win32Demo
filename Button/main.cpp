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

// Function Declaration
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


// Button 控件
HWND hGroupBox1;
HWND hGroupBox2;
HWND hGroupBox3;
HWND hGroupBox4;

//Radio Button
HWND hBtn1;
HWND hBtn2;
HWND hBtn3; 
HWND hBtn4;
HWND hBtn5;
HWND hBtn6;

HWND hBtn7;
HWND hBtn8;
HWND hBtn9;

HWND hBtn10;
HWND hBtn11;
HWND hBtn12;



int wWinMain(HINSTANCE hIns, HINSTANCE hPre, LPTSTR lpCmdLine, int nShow)
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

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			LPCREATESTRUCT lpSt = (LPCREATESTRUCT)lParam;

			// 2组 Radio Button ; 123一组互斥;  456一组互斥
			hBtn1 = CreateWindow(L"Button", L"Btn1", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
								 5, 5, 110, 30, hWnd, HMENU(0x1000), lpSt->hInstance, NULL);
			hBtn2 = CreateWindow(L"Button", L"Btn2", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
								 5, 55, 110, 30, hWnd, HMENU(0x1001), lpSt->hInstance, NULL);
			hBtn3 = CreateWindow(L"Button", L"Btn3", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
								 5, 105, 110, 30, hWnd, HMENU(0x1002), lpSt->hInstance, NULL);
			hBtn4 = CreateWindow(L"Button", L"Btn4", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
								 155, 5, 110, 30, hWnd, HMENU(0x1003), lpSt->hInstance, NULL);
			hBtn5 = CreateWindow(L"Button", L"Btn5", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
								 155, 55, 110, 30, hWnd, HMENU(0x1004), lpSt->hInstance, NULL);
			hBtn6 = CreateWindow(L"Button", L"Btn6", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
								 155, 105, 110, 30, hWnd, HMENU(0x1005), lpSt->hInstance, NULL);

			// 6个 PushButton
			hBtn7 = CreateWindow(L"Button", L"Btn7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
								 305, 5, 110, 30, hWnd, HMENU(0x1006), lpSt->hInstance, NULL);
			hBtn8 = CreateWindow(L"Button", L"Btn8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
								 305, 55, 110, 30, hWnd, HMENU(0x1007), lpSt->hInstance, NULL);
			hBtn9 = CreateWindow(L"Button", L"Btn9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
								 305, 105, 110, 30, hWnd, HMENU(0x1008), lpSt->hInstance, NULL);
			hBtn10 = CreateWindow(L"Button", L"Btn10", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
								 455, 5, 110, 30, hWnd, HMENU(0x1009), lpSt->hInstance, NULL);
			hBtn11 = CreateWindow(L"Button", L"Btn11", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
								 455, 55, 110, 30, hWnd, HMENU(0x1010), lpSt->hInstance, NULL);
			hBtn12 = CreateWindow(L"Button", L"Btn12", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
								 455, 105, 110, 30, hWnd, HMENU(0x1011), lpSt->hInstance, NULL);
			
		} break;
		case WM_COMMAND:
		{
			WORD id = LOWORD(wParam);
			WORD code = HIWORD(wParam);
			HWND hBtn = HWND(lParam);

			switch (code)
			{
				case BN_CLICKED:
				{
					switch (id)
					{
						//Btn7
						case 0x1006:
						{
							BOOL isChecked1 = SendMessage(hBtn1, BM_GETCHECK, 0, 0) & BST_CHECKED;
							BOOL isChecked2 = SendMessage(hBtn2, BM_GETCHECK, 0, 0) & BST_CHECKED;
							BOOL isChecked3 = SendMessage(hBtn3, BM_GETCHECK, 0, 0) & BST_CHECKED;
							BOOL isChecked4 = SendMessage(hBtn4, BM_GETCHECK, 0, 0) & BST_CHECKED;
							BOOL isChecked5 = SendMessage(hBtn5, BM_GETCHECK, 0, 0) & BST_CHECKED;
							BOOL isChecked6 = SendMessage(hBtn6, BM_GETCHECK, 0, 0) & BST_CHECKED;
																					
							std::wstring str[6]{ };
							str[0] = isChecked1 ? L"Checked" : L"UnChecked";
							str[1] = isChecked2 ? L"Checked" : L"UnChecked";
							str[2] = isChecked3 ? L"Checked" : L"UnChecked";
							str[3] = isChecked4 ? L"Checked" : L"UnChecked";
							str[4] = isChecked5 ? L"Checked" : L"UnChecked";
							str[5] = isChecked6 ? L"Checked" : L"UnChecked";

							for (int i = 0; i < 6; i++)
								std::wcout << "Button " << i+1 << " state: " << str[i] << "\n";
						}break;
						case 0x1007:
						{
							SendMessage(hBtn1, BM_SETCHECK, BST_CHECKED, 0);
							SendMessage(hBtn2, BM_SETCHECK, BST_CHECKED, 0);
							//Button_SetCheck(hBtn1, BST_CHECKED);
						}break;
						case 0x1000:
						case 0x1001:
						case 0x1002:
							CheckRadioButton(hWnd, 0x1000, 0x1002, id);
							break;
						case 0x1003:
						case 0x1004:
						case 0x1005:
							CheckRadioButton(hWnd, 0x1003, 0x1005, id);
							break;
					}
				}break;
			}
		} break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		} break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
