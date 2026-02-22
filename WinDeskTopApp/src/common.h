#pragma once






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


//主窗口相关
HWND hMainWindow = NULL;

//当前程序实例句柄
HINSTANCE hInstance = NULL; 

//菜单相关
static HMENU hTopMenu = nullptr;  //顶层菜单句柄

// 按钮相关
HWND hButton1 = NULL;
HWND hButton2 = NULL;
HWND hButton3 = NULL;
HWND hRButton1 = NULL;
HWND hRButton2 = NULL;
HWND hRButton3 = NULL;
HWND hCBox1 = NULL;
HWND hCBox2 = NULL;
HWND hCBox3 = NULL;


//WM_KEYDOWN 消息处理函数
void WMKEYDOWNProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara)
{
	UINT vkCode = (UINT)wPara; //虚拟键码
	switch (vkCode)
	{
		case VK_ESCAPE:
		{
			std::printf("ESC Key Pressed!\n");
		}
	}
}


// WM_DROPFILES 消息处理函数
void WMDROPFILESProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara)
{
	HDROP hDrop = (HDROP)wPara;
	UINT fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
	for (UINT i = 0; i < fileCount; i++)
	{
		TCHAR filePath[MAX_PATH] = { 0 };
		DragQueryFile(hDrop, i, filePath, MAX_PATH);
		_tprintf(_T("Dropped file: %s\n"), filePath);
	}
	DragFinish(hDrop);
}

// WM_CHAR 消息处理函数
void WMCHARProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara)
{

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara)
{
	switch (msg)
	{
		case WM_CREATE:
		{

			//菜单创建
			hTopMenu = CreateMenu();
			HMENU hPop111 = CreatePopupMenu();
			//将弹出菜单作为子菜单添加到顶层菜单上
			AppendMenu(hTopMenu, MF_POPUP, UINT_PTR(hPop111), _T("File"));
			AppendMenu(hPop111, MF_STRING, 0x111, _T("New Tab"));
			AppendMenu(hPop111, MF_STRING, 0x112, _T("New Window"));
			AppendMenu(hPop111, MF_STRING, 0x113, _T("New MarkDown Tab"));
			AppendMenu(hPop111, MF_STRING, 0x114, _T("Open"));
			AppendMenu(hPop111, MF_STRING, 0x115, _T("Recent"));
			AppendMenu(hPop111, MF_STRING, 0x116, _T("Save"));
			AppendMenu(hPop111, MF_STRING, 0x117, _T("Save as"));
			AppendMenu(hPop111, MF_STRING, 0x118, _T("Save All"));
			//添加分隔符
			AppendMenu(hPop111, MF_SEPARATOR, NULL, NULL);
			AppendMenu(hPop111, MF_STRING, 0x119, _T("Page Setup"));
			AppendMenu(hPop111, MF_STRING, 0x11a, _T("Print"));
			AppendMenu(hPop111, MF_SEPARATOR, NULL, NULL);
			AppendMenu(hPop111, MF_STRING, 0x11b, _T("Close Tab"));
			AppendMenu(hPop111, MF_STRING, 0x11c, _T("Close Window"));
			AppendMenu(hPop111, MF_SEPARATOR, NULL, NULL);
			AppendMenu(hPop111, MF_STRING, 0x11d, _T("Exit"));
			

			HMENU hPop112 = CreatePopupMenu();
			AppendMenu(hTopMenu, MF_POPUP, UINT_PTR(hPop112), _T("Edit"));
			AppendMenu(hPop112, MF_STRING, 0x221, _T("Undo"));
			AppendMenu(hPop112, MF_STRING, 0x222, _T("Cut"));
			AppendMenu(hPop112, MF_STRING, 0x223, _T("Copy"));
			AppendMenu(hPop112, MF_STRING, 0x224, _T("Paste"));
			
			SetMenu(hWnd, hTopMenu);
			DestroyMenu(hTopMenu);
			DestroyMenu(hPop111);
			DestroyMenu(hPop112);


			//创建按钮
			hButton1 = CreateWindow(L"Button", L"click1", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 5, 5,
									50, 30, hWnd, HMENU(0xaa1), ((LPCREATESTRUCT)lPara)->hInstance, NULL);

			// 0xabc12 是控件的ID, 不是菜单句柄
			hButton2 = CreateWindow(L"Button", L"click2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 85, 5,
									50, 30, hWnd, HMENU(0xaa2), ((LPCREATESTRUCT)lPara)->hInstance, NULL);

			hButton3 = CreateWindow(L"Button", L"click3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 165, 5,
									50, 30, hWnd, HMENU(0xaa3), ((LPCREATESTRUCT)lPara)->hInstance, NULL);

			hRButton1 = CreateWindow(L"Button", L"RdButton1", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 5, 55,
									100, 30, hWnd, HMENU(0xaa4), ((LPCREATESTRUCT)lPara)->hInstance, NULL);

			hRButton2 = CreateWindow(L"Button", L"RdButton2", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 125, 55,
									 100, 30, hWnd, HMENU(0xaa5), ((LPCREATESTRUCT)lPara)->hInstance, NULL);

			hRButton3 = CreateWindow(L"Button", L"RdButton3", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 245, 55,
									 100, 30, hWnd, HMENU(0xaa6), ((LPCREATESTRUCT)lPara)->hInstance, NULL);

			hCBox1 = CreateWindow(L"Button", L"CheckBox1", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 5, 105,
									 100, 30, hWnd, HMENU(0xaa7), ((LPCREATESTRUCT)lPara)->hInstance, NULL);

			hCBox2 = CreateWindow(L"Button", L"CheckBox2", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 125, 105,
									 100, 30, hWnd, HMENU(0xaa8), ((LPCREATESTRUCT)lPara)->hInstance, NULL);

			hCBox3 = CreateWindow(L"Button", L"CheckBox3", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 245, 105,
									 100, 30, hWnd, HMENU(0xaa9), ((LPCREATESTRUCT)lPara)->hInstance, NULL);
			// 按钮美化
			// 自绘制按钮
			BS_COMMANDLINK;
			BM_GETCHECK;
			BM_GETSTATE;
			BS_DEFPUSHBUTTON;

		}break;
		case WM_COMMAND:
		{	
			// 按钮控件消息处理
			WORD id = LOWORD(wPara);
			WORD code = HIWORD(wPara);
			HWND hBtn = (HWND)lPara;
			if (id == 0xaa1)
			{
				if (code == BN_CLICKED)
				{
					MessageBox(NULL, L"按钮1 被单击 ", NULL, MB_OK);
				}
			}
			if (id == 0xaa2)
			{

			}
			if (id == 0xaa3)
			{
					
			}
			if (id == 0xaa4)
			{
				if (SendMessage(hBtn, BM_GETCHECK, 0, 0) == BST_CHECKED)
				{
					MessageBox(NULL, L"按钮被选中", L"Test", MB_OK);
				}
			}

			if (id == 0xaa5)
			{

			}

			if (id == 0xaa6)
			{

			}

			
			//手动模式下的复选框处理逻辑
			//BS_CHECKBOX为手动模式
			//BS_AUTOCHECKBOX为自动模式
			if (id == 0xaa7)
			{
				//获取当前复选框状态
				BOOL isChecked = SendMessage(hBtn, BM_GETCHECK, 0, 0) == BST_CHECKED;

				if (isChecked == TRUE)
				{
					SendMessage(hBtn, BM_SETCHECK, BST_UNCHECKED, 0);
				}
				else
				{
					if (MessageBox(hWnd, L"确定勾选CheckBox1?", L"提示", MB_YESNO) == IDYES)
					{
						SendMessage(hBtn, BM_SETCHECK, BST_CHECKED, 0);
					}
				}				
			}

			if (id == 0xaa8)
			{
				//使用Button_GetCheck宏来获取复选框状态.
				if (Button_GetCheck(hBtn) == BST_CHECKED)
				{
					MessageBox(NULL, L"CheckBox2 被选中", L"测试", MB_OK);
				}
			}
			if (id == 0xaa9)
			{
				//使用SendMessage 函数来获取复选框状态
				if (SendMessage(hBtn, BM_GETCHECK, 0, 0) == BST_CHECKED)
				{
					MessageBox(NULL, L"CheckBox3 被选中", L"test", MB_OK);
				}
			}
		}break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;
		case WM_KEYDOWN:
		{
			WMKEYDOWNProc(hWnd, msg, wPara, lPara);
			return 0;
		}
		default:
			return DefWindowProc(hWnd, msg, wPara, lPara);
	}
}