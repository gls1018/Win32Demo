#include <Windows.h>
#include <shellscalingapi.h>
#pragma comment(lib, "Shcore.lib")
#include <string>
#include <vector>
#pragma warning(disable : 28251)

#define IDM_FILE_NEW_TAB        1001
#define IDM_FILE_NEW_WINDOW     1002
#define IDM_FILE_NEW_MD_TAB     1003
#define IDM_FILE_OPEN           1004
#define IDM_FILE_RECENT1        1005
#define IDM_FILE_SAVE           1006
#define IDM_FILE_SAVE_AS        1007
#define IDM_FILE_SAVE_ALL       1008
#define IDM_FILE_PAGE_SETUP     1009
#define IDM_FILE_PRINT          1010
#define IDM_FILE_CLOSE_TAB      1011
#define IDM_FILE_CLOSE_WINDOW   1012
#define IDM_FILE_EXIT           1013
#define IDM_FILE_STARTWINDOW    1024

void AddMenuItem(HMENU hMenu, UINT id, LPCWSTR text, UINT pos, UINT fType = MFT_STRING)
{
	MENUITEMINFO mii = { 0 };
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
	mii.fType = fType;
	mii.dwTypeData = (LPWSTR)text;
	mii.fState = MFS_ENABLED;

	InsertMenuItemW(hMenu, pos, TRUE, &mii);
}

void AddSeparator(HMENU hMenu, UINT pos)
{
	MENUITEMINFO mii{ 0 };
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_FTYPE;
	mii.fType = MFT_SEPARATOR;

	InsertMenuItemW(hMenu, pos, TRUE, &mii);
}

HMENU CreateMainMenu()
{
	HMENU hMenuBar = CreateMenu();
	HMENU hFileMenu = CreatePopupMenu();
	HMENU hEditMenu = CreatePopupMenu();
	HMENU hViewMenu = CreatePopupMenu();

	// ---- 把 File 加到菜单栏 -----
	MENUITEMINFOW miiFile{ 0 };
	miiFile.cbSize = sizeof(miiFile);
	miiFile.fMask = MIIM_SUBMENU | MIIM_STATE | MIIM_STRING;
	miiFile.dwTypeData = (LPWSTR)L"File";
	miiFile.hSubMenu = hFileMenu;
	miiFile.fState = MFS_ENABLED;
	InsertMenuItemW(hMenuBar, -1, TRUE, &miiFile);

	// --- 把 Edit 加到菜单栏 ----
	MENUITEMINFOW miiEdit{ 0 };
	miiEdit.cbSize = sizeof(miiEdit);
	miiEdit.fMask = MIIM_SUBMENU | MIIM_STATE | MIIM_STRING;
	miiEdit.dwTypeData = (LPWSTR)L"Edit";
	miiEdit.hSubMenu = hEditMenu;
	miiEdit.fState = MFS_ENABLED;
	InsertMenuItemW(hMenuBar, -1, TRUE, &miiEdit);

	// --- 把 View 加到菜单栏----
	MENUITEMINFO miiView{ 0 };
	miiView.cbSize = sizeof(miiView);
	miiView.fMask = MIIM_SUBMENU | MIIM_STATE | MIIM_STRING;
	miiView.dwTypeData = (LPWSTR)L"View";
	miiView.fState = MFS_ENABLED;
	miiView.hSubMenu = hViewMenu;
	InsertMenuItemW(hMenuBar, -1, TRUE, &miiView);

	// ---- File/New -----
	MENUITEMINFO miiNew;
	miiNew.cbSize = sizeof(miiNew);
	miiNew.fMask = MIIM_STATE | MIIM_STRING | MIIM_ID;


	// ---- File/Open ----


	//---  File/StartWindow -----
	MENUITEMINFO miiStartWindow{ 0 };
	miiStartWindow.cbSize = sizeof(miiStartWindow);
	miiStartWindow.fMask = MIIM_ID | MIIM_STRING | MIIM_STATE;
	miiStartWindow.wID = IDM_FILE_STARTWINDOW;
	miiStartWindow.dwTypeData = (LPWSTR)L"Start Window";
	miiStartWindow.fState = MFS_ENABLED;
	InsertMenuItemW(hFileMenu, -1, TRUE, &miiStartWindow);



	// ---- File/Save  && SaveAs---
	MENUITEMINFO miiSave{ 0 };
	miiSave.cbSize = sizeof(miiSave);
	miiSave.fMask = MIIM_ID | MIIM_STRING | MIIM_STATE;
	miiSave.dwTypeData = (LPWSTR)L"Save";
	miiSave.wID = IDM_FILE_SAVE;
	miiSave.fState = MFS_ENABLED;
	InsertMenuItemW(hFileMenu, -1, TRUE, &miiSave);
	
	miiSave.dwTypeData = (LPWSTR)L"Save as";
	miiSave.wID = IDM_FILE_SAVE_AS;
	InsertMenuItemW(hFileMenu, -1, TRUE, &miiSave);
	
	return hMenuBar;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara);

// Add SAL and calling convention to match platform headers and avoid annotation mismatch
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPre, _In_ PWSTR lpCommandLine, _In_ int nShowCmd)
{
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
	WNDCLASSEX wc{ 0 };
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClassEx(&wc);


	DWORD dwExStyle = WS_EX_ACCEPTFILES;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	HWND hMainWindow = CreateWindowEx(dwExStyle, L"MyWindowClass", L"WinApp", dwStyle,
									  100, 300, 800, 500, NULL, NULL, hInstance, NULL);

	ShowWindow(hMainWindow, SW_NORMAL);
	UpdateWindow(hMainWindow);

	ACCEL accel[] = {
		{FCONTROL | FVIRTKEY, 'S',  IDM_FILE_SAVE },
		{FCONTROL | FSHIFT | FVIRTKEY, 'P', IDM_FILE_SAVE_AS }
	};

	HACCEL hAccel = CreateAcceleratorTableW(accel, 2);

	MSG msg;
	while (GetMessageW(&msg, hMainWindow, 0, 0))
	{
		if (!TranslateAcceleratorW(hMainWindow, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	DestroyAcceleratorTable(hAccel);
	return 0;

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wPara, LPARAM lPara)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			// 主菜单栏
			HMENU hMenuBar = CreateMainMenu();
			SetMenu(hWnd, hMenuBar);
		} break;
		case WM_COMMAND:
		{
			WORD id = LOWORD(wPara);
			switch (id)
			{
				case IDM_FILE_STARTWINDOW:
				{
					MessageBoxW(hWnd, L"Start Window", L"Menu", MB_OK);

				} break;

				case IDM_FILE_SAVE:
				{
					MessageBoxW(hWnd, L"Save", L"Demo", MB_OK);
				} break;

				case IDM_FILE_SAVE_AS:
				{
					MessageBoxW(hWnd, L"Save as", L"Demo", MB_OK);
				} break;

				default:
					break;
			}

		} break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		} break;

		default:
			return DefWindowProcW(hWnd, msg, wPara, lPara);
	}

	return DefWindowProcW(hWnd, msg, wPara, lPara);
}

