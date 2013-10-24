// UTaskService.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "UTask.h"
#include "Regext.h"
#include "service.h"
#include "UTaskWindow.h"
#include "WindowHandler.h"
#include "ActionConfiguration.h"
#include "GlobalSettings.h"

extern HWND uTaskWindow;
extern BOOL ServiceReady;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls((HINSTANCE)hModule);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
};

DWORD UTS_Close(DWORD dwData)
{
	return 0;
};

extern HANDLE hInitThreadFinishedEvent;

DWORD UTS_Deinit(DWORD dwData)
{
	if (ServiceReady)
	{
		DestroyWindow(uTaskWindow);
		UnregisterClassW(UTS_WND_CLASS, GetModuleHandle(NULL));
		HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, UTASK_GLOBAL_HOOK_UPDATE_EVENT);
		SetEvent(hEvent);
		CloseHandle(hInitThreadFinishedEvent);
	}
	return 1;
};

DWORD UTS_Init(DWORD dwData)
{
	HANDLE hThread = CreateThread(0, 0, UTaskThread, 0, 0, 0);
	CloseHandle(hThread);
	return 1;
};

BOOL UTS_IOControl(DWORD AData, DWORD ACode, void *ABufIn, 
				   DWORD ASzIn, void *ABufOut, DWORD ASzOut, 
				   DWORD *ARealSzOut) 
{
	switch (ACode) 
	{
	case IOCTL_SERVICE_START:
		return TRUE;
	case IOCTL_SERVICE_STOP:
		return TRUE;
	case IOCTL_SERVICE_STARTED:
		return TRUE;
	case IOCTL_SERVICE_INSTALL: 
		{
			// Registering our service in the OS
			HKEY hKey;
			DWORD dwValue;

			if (RegCreateKeyExW(HKEY_LOCAL_MACHINE, L"Services\\UTaskSrv", 0, 
								NULL, 0, 0, NULL, &hKey, &dwValue)) 
				return FALSE;

			// DLL name
			WCHAR dllname[] = L"UTaskSrv.dll";
			RegSetValueExW(hKey, L"Dll", 0, REG_SZ, 
				(const BYTE *)dllname, wcslen(dllname) << 1);

			// Setting prefix used to control our service
			RegSetValueExW(hKey, L"Prefix", 0, REG_SZ, (const BYTE *)L"UTS",6);

			// Flags, Index, Context
			dwValue = 0;
			RegSetValueExW(hKey, L"Flags", 0, REG_DWORD, (const BYTE *) &dwValue, 4);
			RegSetValueExW(hKey, L"Index", 0, REG_DWORD, (const BYTE *) &dwValue, 4);
			RegSetValueExW(hKey, L"Context", 0, REG_DWORD, (const BYTE *) &dwValue, 4);

			// Should system keep service alive after initialization?
			dwValue = 1;
			RegSetValueExW(hKey, L"Keep", 0, REG_DWORD, (const BYTE *) &dwValue, 4);

			// Setting load order
			dwValue = 9999;
			RegSetValueExW(hKey, L"Order", 0, REG_DWORD, (const BYTE *) &dwValue, 4);

			RegCloseKey(hKey);
			return TRUE;
		}
	case IOCTL_SERVICE_UNINSTALL: 
		{
			// Uninstalling service from the OS
			HKEY rk;
			if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"Services", 0, NULL, &rk)) 
				return FALSE;

			RegDeleteKeyW(rk, L"UTaskSrv");
			RegCloseKey(rk);

			return TRUE;
		}

	case IOCTL_SERVICE_QUERY_CAN_DEINIT:
		{
			memset(ABufOut, 1, ASzOut);
			return TRUE;
		}
	case IOCTL_SERVICE_CONTROL:
		{
			if (ASzIn != 4)
				return FALSE;

			int command=((int*) ABufIn)[0];
			switch (command) 
			{
			case IOCTL_UTASK_UPDATESETTINGS:
				{
					// Reconfiguration
					GlobalSettings_Clear(FALSE);
					GlobalSettings_Read(FALSE);
					return TRUE;
				}
			}
			return TRUE;
		}
	default:
		// Unknown control code received
		return FALSE;
	}

	return TRUE;
};


DWORD UTS_Open(DWORD dwData,
			   DWORD dwAccess,
			   DWORD dwShareMode)
{
	return 0;
};

DWORD UTS_Read(DWORD dwData,
			   LPVOID pBuf,
			   DWORD dwLen)
{

	return 0;
};

DWORD UTS_Seek(DWORD dwData,
			   long pos,
			   DWORD type)
{

	return 0;
};

DWORD UTS_Write(DWORD dwData,
				LPCVOID pInBuf,
				DWORD dwInLen)
{

	return 0;
};

