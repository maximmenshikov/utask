#include "stdafx.h"
#include <Tlhelp32.h>
#pragma comment(lib,"Toolhelp.lib")
#include "ProcessHandler.h"

LONG Process_GetID(LPWSTR name)
{
	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPNOHEAPS, NULL);
	
	if(hProcessSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	LONG result = 0;
	PROCESSENTRY32 processentry32;
	memset(&processentry32, 0, sizeof(PROCESSENTRY32));
	processentry32.dwSize = sizeof(processentry32);

	Process32First(hProcessSnapshot, &processentry32);
	do
	{
		wchar_t *sz = wcslwr(processentry32.szExeFile);
		if(wcsicmp(name, sz) == 0)
		{
			result = processentry32.th32ProcessID;
			break;
		}
	} while(Process32Next(hProcessSnapshot, &processentry32));

	CloseToolhelp32Snapshot(hProcessSnapshot);

	return result;
};

//BOOL CanBeKilled(HWND hWnd);

BOOL Process_Kill(DWORD processID)
{
#ifdef FORCEKILL
	HANDLE hProcess = OpenProcess(0, FALSE, processID);
	if (hProcess == NULL || hProcess == INVALID_HANDLE_VALUE)
		return FALSE;
	TerminateProcess(hProcess, 0);
	CloseHandle(hProcess);
#else
	Sleep(2000);
	HWND hWnd = (HWND)processID;
	DWORD ret = NULL;
	if(hWnd && IsWindow(hWnd) == TRUE)
	{
		//DestroyWindow(hWnd);
		PostMessage(hWnd, WM_QUIT, 0, 0);
		DestroyWindow(hWnd);
	}
	//SendMessageTimeout(hWnd, WM_DESTROY, NULL, NULL, SMTO_NORMAL, 500, &ret);
#endif
	return TRUE;
};

ULONG Process_KillThread(LPVOID pParam)
{
	Process_Kill((DWORD) pParam);
	return 0;
};


BOOL Process_ForceKill(DWORD processID, HWND hWnd)
{
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, processID);
    if (hProc)
    {
		BOOL terminated = FALSE;
		//Sleep(100);
		//if (IsWindow(hWnd))
		//{
		if (WaitForSingleObject(hProc, 5000) == WAIT_TIMEOUT)
		{
			//if (IsWindow(hWnd))
			//{
			// App didn't terminate so far. As a last resort, do TerminateProcess
			terminated = TerminateProcess(hProc, (UINT)-1);
			//}
		}
		//}
		if (terminated == FALSE)
			CloseHandle(hProc);
    }
	return TRUE;
};

ULONG Process_ForceKillThread(LPVOID pParam)
{
	PROCESSFKILLPARAM *pfk = (PROCESSFKILLPARAM*)pParam;
	if (pfk)
	{
		Process_ForceKill(pfk->processID, pfk->hWnd);
		delete(pfk);
	}
	return 0;
};

