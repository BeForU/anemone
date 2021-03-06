/**
* This file is part of Anemone.
*
* Anemone is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* The Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Anemone is distributed in the hope that it will be useful,
*
* But WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Anemone.
*
*   If not, see <http://www.gnu.org/licenses/>.
*
**/

#pragma region [ Includes ]
#include "stdafx.h"
#include "Anemone.h"
#include "MainDlg.h"
#include "LayeredWnd.h"
#include "SettingDlg.h"
#include "Graphics.h"
#pragma endregion

#pragma region [ Application Extern Variables ]
#define MAX_LOADSTRING 100
HINSTANCE g_hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
ConfigManager CfgMgr;
#pragma endregion

#pragma region [ Initialize Function Declarations ]
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                CreateLayeredWnd(int);

#pragma endregion

int guide_opacity = 0;
double guide_opacity2 = 0;
bool mouse_evt = false;

std::wstring strBuff;
std::vector<std::wstring> vecBuff;
int n_selLine = 0;

#pragma region -- WinAPI Skeleton Functions --
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ANEMONE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
	
	Graphics::Init();

	g_hInst = hInstance;
	while (1)
	{
		int nMode = DialogBox(g_hInst, MAKEINTRESOURCE(IDD_MAIN), 0, MainDlg::DlgProc);
		switch (nMode)
		{
		case ID_CLIPMODE:
		case ID_CAPTIONMODE:
		case ID_TRANSMODE:
		{
			if (!CreateLayeredWnd(nMode))
			{
				MessageBox(0, L"CreateLayeredWnd Failed", 0, 0);
				return FALSE;
			}

			HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ANEMONE));
			MSG msg;
			while (GetMessage(&msg, nullptr, 0, 0))
			{
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
		break;
		case ID_SETTING:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_SETTING), 0, SettingDlg::DlgProc);
			break;

		default:
			return 0;
		}
	}

	return 0;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = LayeredWnd::DlgProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ANEMONE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
void render(HWND hWnd);
unsigned WINAPI ThreadFunction(void *args);
BOOL CreateLayeredWnd(int nMode)
{
	CfgMgr.Load();
	CfgMgr["TEST"];

	CfgMgr.data["asdf"] = "zxcv";
	OutputDebugStringA(CfgMgr.data["asdf"].c_str());

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	int width = 650;
	int height = 200;

	int x = (cx - width) / 2;
	int y = (cy - height) / 2;

   HWND hWnd = CreateWindowExW(WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_NOACTIVATE | WS_EX_APPWINDOW, szWindowClass, szTitle, WS_POPUP,
      x, y, width, height, nullptr, nullptr, g_hInst, (LPVOID)nMode);
   SetWindowLong(hWnd, GWL_STYLE, 0);

   RECT rect;
   GetWindowRect(hWnd, &rect);
   Graphics::CreateContext(hWnd, rect.right - rect.left, rect.bottom - rect.top);

   if (!hWnd)
   {
	   return FALSE;
   }

   ShowWindow(hWnd, true);
   UpdateWindow(hWnd);

   return TRUE;
}
unsigned WINAPI ThreadFunction(void *args)
{
	
	return 0;
}
#pragma endregion