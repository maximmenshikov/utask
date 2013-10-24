#include "stdafx.h"
#include "UTaskHook_local.h"
#include "UTask.h"
#include "EventWrapper.h"

int InjectDLL(HANDLE Proc, wchar_t *LibraryName)
{
	// Trying to get current HookLibraryReady event state
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, UTASK_GLOBAL_HOOKLIB_READY_EVENT);
	if (ReadEvent(hEvent, 0) == 0)
		return 1;
	
	HMODULE coredll = GetModuleHandle(L"coredll.dll");

	DWORD result = 1;
	if (coredll)
	{
		// Loading our library to gwes.exe memory space
		CALLBACKINFO ci;
		ci.hProc = Proc;
		ci.pfn = (FARPROC)MapPtrToProcess(GetProcAddress(coredll, L"LoadLibraryW"), 
			Proc);
		ci.pvArg0 = MapPtrToProcess(LibraryName, GetCurrentProcess());
		PerformCallBack4(&ci);

		Sleep(2000);
		// Waiting for HookLibraryReady event pulsation for 3000 ms
		result = ReadEvent(hEvent, 3000);
	}
	CloseHandle(hEvent);
	return result;
};
