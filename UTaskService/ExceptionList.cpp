#include "stdafx.h"
#include "UTask.h"
#include "ProcessHandler.h"
#include "regext.h"
#include <vector>
using namespace std;

DWORD				Shell32ID;
DWORD				CprogID;
DWORD				GwesID;

typedef vector<wchar_t*> WCHARVECTOR;

WCHARVECTOR ExceptionList;

// Check if process is in exceptions list
BOOL ExceptionList_isInList(DWORD processID)
{
	if (processID == Shell32ID || processID == CprogID || processID == GwesID)
		return TRUE;
	
	HANDLE hProcess = OpenProcess(0, FALSE, processID); 
	if (hProcess != NULL) 
	{
		wchar_t path[256];
		wchar_t *temppath = path;
		GetModuleFileName((HMODULE)hProcess, path, 256);

		if (wcsrchr(temppath, L'\\'))
			temppath = wcsrchr(temppath, L'\\') + 1;

		for (UINT x = 0; x < ExceptionList.size(); x++) 
		{
			wchar_t *name = ExceptionList[x];

			if (wcsicmp(temppath, name) == 0) 
			{
				CloseHandle(hProcess);
				return TRUE;
			}
		}
		CloseHandle(hProcess);
	}
	return FALSE;
};

// Reset exceptions list
VOID ExceptionList_DeinitializeList()
{
	while (ExceptionList.size() != 0) 
	{
		if (ExceptionList[0])
			delete(ExceptionList[0]);
		ExceptionList.erase(ExceptionList.begin());
	}
};

// Fill in exception list
VOID ExceptionList_InitializeList()
{
	Shell32ID = Process_GetID(L"shell32.exe");
	CprogID = Process_GetID(L"cprog.exe");
	GwesID = Process_GetID(L"gwes.exe");

	// TODO: Reading exceptions table from registry
	HKEY hKey;

	if( RegOpenKeyEx( UTASK_REG_BRANCH,
		UTASK_REG_EXCLUSIVELIST_KEY,
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
					ExceptionList.push_back(keyNamePtr);
				}
			}
			keyNameSize = 50;
		}
		RegCloseKey(hKey);
	}
};

