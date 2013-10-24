#include "stdafx.h"
#include "UTask.h"
#include "ExclusiveList.h"
#include "settings.h"
#include "..\UTaskCommon\headers\MaskedStringCompare.h"

List ExclusiveList_ToFix;
List ExclusiveList_NoFix;

BOOL IsExclusiveWindow(wchar_t *className)
{
	List *ExclusiveList = settingIsAutoFix ? &ExclusiveList_NoFix : &ExclusiveList_ToFix;

	for (int x = 0; x < ExclusiveList->Count(); x++)
	{
		wchar_t *excludedWindowClass = (wchar_t*)ExclusiveList->Get(x);
		if (MaskedStringCompare((wchar_t*)className, excludedWindowClass) == TRUE)
			return TRUE;
	}
	return FALSE;
};

VOID FillList(List *list, wchar_t *subkey)
{
	HKEY hKey;
	if( RegOpenKeyEx( UTASK_REG_BRANCH,
		subkey,
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
					list->Add(keyNamePtr);
				}
			}
			keyNameSize = 50;
		}
		RegCloseKey(hKey);
	}
};

VOID ExclusiveList_InitializeList()
{
	__try
	{
		FillList(&ExclusiveList_ToFix, UTASK_REG_POSFIX_FIX_KEY);
		FillList(&ExclusiveList_NoFix, UTASK_REG_POSFIX_NOFIX_KEY);
	}
	__except (GetExceptionCode())
	{
	}
};

VOID ExclusiveList_DeinitializeList()
{
	__try 
	{
		while (ExclusiveList_ToFix.Count()) 
		{
			wchar_t *str = NULL;
			if (str = (wchar_t*)ExclusiveList_ToFix.RemoveAt(0))
				delete(str);
		}
		while (ExclusiveList_NoFix.Count()) 
		{
			wchar_t *str = NULL;
			if (str = (wchar_t*)ExclusiveList_NoFix.RemoveAt(0))
				delete(str);
		}
	}
	__except (GetExceptionCode())
	{
	}
};
