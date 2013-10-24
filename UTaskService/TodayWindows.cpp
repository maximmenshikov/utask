#include "stdafx.h"
#include "UTask.h"
#include "WindowHandler.h"
#include "regext.h"
#include "..\UTaskCommon\headers\MaskedStringCompare.h"

#include <vector>

using namespace std;

typedef vector<wchar_t*> WCHARVECTOR;
WCHARVECTOR TodayWindows;

BOOL IsTodayWindow(HWND hWnd)
{
	HWND MenuWorker = GetMenuWorker(hWnd);
	if (MenuWorker)
	{
		HWND ParentWindow = GetParent(MenuWorker);
		if (ParentWindow)
		{
			if (ParentWindow == GetDesktopWindow())
				return TRUE;

			wchar_t className[50];
			GetClassName(ParentWindow, className, 50);

			for (UINT x = 0; x < TodayWindows.size(); x++)
			{
				wchar_t *todayWindow = TodayWindows[x];
				if (todayWindow)
				{
					if (MaskedStringCompare(className, todayWindow) == TRUE)
						return TRUE;
				}
			}
		}
	}
	return FALSE;
};

VOID TodayWindow_InitializeList()
{
	HKEY hKey;

	if( RegOpenKeyEx( UTASK_REG_BRANCH,
		UTASK_REG_TODAYWINDOWS_KEY,
		0,
		KEY_READ,
		&hKey) == ERROR_SUCCESS)
	{
		wchar_t keyName[50];
		DWORD keyNameSize = 50;

		DWORD dwIndex = 0;

		DWORD dwType = REG_NONE;
		while (RegEnumValue(hKey, 
							dwIndex++, 
							keyName, 
							&keyNameSize, 
							NULL, 
							&dwType, 
							NULL, 
							NULL) == ERROR_SUCCESS)
		{
			if (dwType != REG_NONE)
			{
				wchar_t *keyNamePtr = new wchar_t[keyNameSize + 1];
				if (keyNamePtr)
				{
					wcscpy(keyNamePtr, keyName);
					TodayWindows.push_back(keyNamePtr);
				}
			}
			keyNameSize = 50;
		}
		RegCloseKey(hKey);
	}
};

VOID TodayWindow_DeinitializeList()
{
	while (TodayWindows.size() != 0) 
	{
		if (TodayWindows[0])
			delete(TodayWindows[0]);
		TodayWindows.erase(TodayWindows.begin());
	}
};

