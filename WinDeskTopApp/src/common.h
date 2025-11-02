#pragma once

//Windows
#include <windows.h>
#include <shellapi.h>
#include <tchar.h>
#include <shellscalingapi.h>
#pragma comment(lib, "Shcore.lib")


//菜单相关
static HMENU hTopMenu = nullptr;  //顶层菜单句柄

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
		default:
			return DefWindowProc(hWnd, msg, wPara, lPara);
	}
}