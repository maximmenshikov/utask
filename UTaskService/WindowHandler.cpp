#include "stdafx.h"
#include "WindowHandler.h"
#include "MenuWorker.h"
#include "ProcessHandler.h"
#include "ExceptionList.h"

#pragma comment (lib, "aygshell.lib")

VOID ZeroString(wchar_t *string, int size)
{
	for (int x = 0; x < size; x++)
		string[x] = L'\0';
};

BOOL Window_HasOK(HWND hWnd)
{
	if (IsWindow(hWnd) == FALSE)
		return 0;

	LONG exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
	LONG style = GetWindowLong(hWnd, GWL_STYLE);

	if (exStyle & WS_EX_CAPTIONOKBTN || style & WS_MINIMIZEBOX)
		return TRUE;

	return FALSE;
};

// Exporting infamous SHTerminateApp function from aygshell.dll.
typedef void (*SHTERMINATEAPP)(HWND hWnd);
SHTERMINATEAPP lShTerminateApp = NULL;
HMODULE hAygShell = NULL;
void SHTerminateApp(HWND hWnd)
{
	if (lShTerminateApp == NULL && hAygShell == NULL)
	{
		hAygShell = LoadLibrary(L"aygshell.dll");
		lShTerminateApp = (SHTERMINATEAPP)GetProcAddress(hAygShell, MAKEINTRESOURCE(438));
	}
	if (lShTerminateApp)
	{
		lShTerminateApp(hWnd);
	}
};

#define WS_EX_EXCLUDEFROMRUNNINGLIST 4

BOOL IsValidWindowToClose(HWND hWnd)
{
	DWORD dwStyleEx = GetWindowLong(hWnd, GWL_EXSTYLE);
	if (IsWindow(hWnd) &&
        IsWindowVisible(hWnd) &&
        !GetWindow(hWnd, GW_OWNER) &&
        (GetParent(hWnd) == NULL) &&
        !(GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD) &&
        !(dwStyleEx & WS_EX_EXCLUDEFROMRUNNINGLIST) &&
        !(dwStyleEx & WS_EX_TOOLWINDOW) &&
        !(dwStyleEx & WS_EX_NOACTIVATE))
	{
		return TRUE;
	}
	return FALSE;
}
UINT Window_Close(HWND hWnd, DWORD forceClose)
{
	DWORD result;

	wchar_t className[50];
	GetClassName(hWnd, className, 50);
	if (wcscmp(className, L"HTCMENUBGWND") == 0)
	{
		// special fix for newest menuenhancements
		SendMessageTimeout(hWnd, WM_COMMAND, 0x138E, NULL, SMTO_NORMAL, 1000, &result);
		return 1;
	}
	if (Window_HasOK(hWnd) == TRUE)
	{
		if (forceClose)
		{
			SendMessageTimeout(hWnd, WM_COMMAND, 0x10000001, NULL, SMTO_NORMAL, 1000, &result);
			return 1;
		}
	}
	else
	{
		DWORD processID;
		GetWindowThreadProcessId(hWnd, &processID);
		if (IsValidWindowToClose(hWnd) == FALSE)
		{
			HWND hWnd_new = GetParent(hWnd);
			if (hWnd_new != NULL)
			{
				DWORD processID2;
				GetWindowThreadProcessId(hWnd_new, &processID2);
				if (processID2 == processID)
					hWnd = hWnd_new;
			}
		}
		if (ExceptionList_isInList(processID) == FALSE)
		{
			DWORD result;
			SendMessageTimeout(hWnd, WM_CLOSE, NULL, NULL, SMTO_NORMAL, 500, &result);
			SHTerminateApp(hWnd);
			PROCESSFKILLPARAM *pfk = new PROCESSFKILLPARAM;
			pfk->hWnd = hWnd;
			pfk->processID = processID;
			CloseHandle(CreateThread(NULL, 0, Process_ForceKillThread, pfk, 0, NULL));
			/*
			SendMessageTimeout(hWnd, WM_CLOSE, NULL, NULL, SMTO_NORMAL, 500, &result);
#ifdef FORCEKILL
			HANDLE hThread = CreateThread(0, 0, Process_KillThread, (LPVOID)processID, 0, 0);
#else
			HANDLE hThread = CreateThread(0, 0, Process_KillThread, (LPVOID)hWnd, 0, 0);
#endif
			CloseHandle(hThread);
			*/
		}
	}
	return 0;
};

RESULT WindowHandler_SetWindowProc(HWND hWnd, LONG lng)
{
	LONG oldLong = GetWindowLong(hWnd, GWL_WNDPROC);
	if (oldLong)
	{
		if (GetProp(hWnd, propLong) == NULL)
		{
			SetProp(hWnd, propLong, (HANDLE) oldLong);
			SetWindowLong(hWnd, GWL_WNDPROC, lng);
			return RESULT_OK;
		}
	}
	return RESULT_ERROR;
};

RESULT WindowHandler_SetDefaultWindowProc(HWND hWnd)
{
	LONG defaultLong = (LONG)GetProp(hWnd, propLong);
	if (defaultLong)
	{
		SetWindowLong(hWnd, GWL_WNDPROC, defaultLong);
		RemoveProp(hWnd, propLong);
		return RESULT_OK;
	}
	return RESULT_ERROR;
};

BOOL CALLBACK WindowHandler_EnumWindows(HWND hWnd, LPARAM lParam)
{
	int mode = (int) lParam;
	wchar_t className[50];
	ZeroString(className, 50);
	if (GetClassName(hWnd, className, 50) && wcscmp(className, L"menu_worker") == 0)
	{
		if (mode == 0)
		{
			if (GetProp(hWnd, propLong) == NULL)
				WindowHandler_SetWindowProc(hWnd, (LONG) MenuWorkerWndProc);
		}
		else
		{
			WindowHandler_SetDefaultWindowProc(hWnd);

			HWND childWindow = GetWindow(hWnd, GW_CHILD | GW_HWNDFIRST);
			
			if (childWindow && IsWindow(childWindow))
			{
				ZeroString(className, 50);
				if (GetClassName(childWindow, className, 50))
				{ 
					if (wcslen(className) && wcscmp(className, TOOLBARCLASSNAME) == 0)
					{
						WindowHandler_SetDefaultWindowProc(childWindow);
					}
				}
			}
		}
	}
	return TRUE;
};

RESULT WindowHandler_PatchAllWindows()
{
	return EnumWindows(WindowHandler_EnumWindows, (LPARAM) 0) 
		? RESULT_OK
		: RESULT_ERROR;
};

RESULT WindowHandler_ReturnAllWindows()
{
	return EnumWindows(WindowHandler_EnumWindows, (LPARAM) 1) 
		? RESULT_OK
		: RESULT_ERROR;
};


HWND GetMenuWorker(HWND hWnd)
{
	wchar_t className[3];
	if (GetClassName(hWnd, className, 3) != 0)
	{
		if (className[0] == L'T')
			return GetParent(hWnd);
		else if (className[0] == L'm')
			return hWnd;
	}
	return NULL;
};

HWND GetToolbarWindow(HWND hWnd)
{
	wchar_t className[3];
	if (GetClassName(hWnd, className, 3) != 0)
	{
		if (className[0] == L'm')
		{
			HWND childWindow = GetWindow(hWnd, GW_CHILD | GW_HWNDFIRST);
			if (childWindow && IsWindow(childWindow))
			{
				wchar_t windowName[20];
				if (GetClassName(childWindow, windowName, 20) && wcscmp(windowName, TOOLBARCLASSNAME) == 0)
				{
					return childWindow;
				}
			}
		}
		else if (className[0] == L'T')
		{
			return hWnd;
		}
	}
	return NULL;
};

