#pragma once

//Windows
#include <windows.h>
#include <shellapi.h>
#include <tchar.h>
#include <shellscalingapi.h>
#pragma comment(lib, "Shcore.lib")

//C++
#include <print>
#include <vector>
#include <string>
#include <memory>

// C
#include <stdio.h>
#include <stdlib.h>

//菜单相关
static HMENU hTopMenu = nullptr;  //顶层菜单句柄




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



// 创建菜单函数
void BuildMenu()
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
			return 0;

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







