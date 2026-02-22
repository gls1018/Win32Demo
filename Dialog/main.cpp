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

int wWinMain(HINSTANCE hIns, HINSTANCE hPre, LPWSTR lpCmdLine, int nShowCmd)
{
	CreateDialog(hIns, L"QQ", NULL, WindowProc);

	return 0;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara)
{
	
}