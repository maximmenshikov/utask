#include "stdafx.h"
#include "UTask.h"
#include "UTaskHook_local.h"
#include "InjectDLL.h"
#include "EventWrapper.h"

UINT InjectToGwes(int addr)
{
	DWORD result = 1;

	// Check if global hook is already initialized
	HANDLE hEventPreCheck = OpenEvent(EVENT_ALL_ACCESS, FALSE, UTASK_GLOBAL_HOOK_READY_EVENT);
	if (hEventPreCheck)
	{
		DWORD preCheckResult = ReadEvent(hEventPreCheck, 0);
		CloseHandle(hEventPreCheck);
		if (preCheckResult == 0)
		{
			RETAILMSG(1, (L"Injection unneeded\n"));
			return 0;
		}
	}
	
	BOOL bMode = SetKMode(TRUE);
    DWORD dwPerm = SetProcPermissions(0xFFFFFFFF);

	CINFO **SystemAPISets = (CINFO **)KData.aInfo[KINX_APISETS];
	DWORD Tmp = (FIRST_METHOD - addr) / APICALL_SCALE;  
	DWORD ApiSet = (Tmp >> HANDLE_SHIFT) & HANDLE_MASK;
    DWORD Method = Tmp & METHOD_MASK;

	// check if our method is correct
	if(ApiSet > NUM_SYSTEM_SETS)
	{
		RETAILMSG(1, (L"Invalid ApiSet\n"));
		goto L_Error;
	}
	if(SystemAPISets[ApiSet] == 0)
	{
		RETAILMSG(1, (L"Invalid ApiSet\n"));
		goto L_Error;
	}
	if(SystemAPISets[ApiSet]->cMethods <= Method)
	{
		RETAILMSG(1, (L"Invalid method number\n"));
		goto L_Error;
	}

	if(SystemAPISets[ApiSet]->pServer == 0)
	{
		RETAILMSG(1, (L"Incorrect pServer\n"));
		goto L_Error;
	}

	// get server process and inject DLL there
	HANDLE Proc = SystemAPISets[ApiSet]->pServer->hProc;

	if (InjectDLL(Proc, L"UTaskHook.dll") == 1)
	{
		RETAILMSG(1, (L"UTaskHook.dll fails to load into gwes memory space\n"));
		goto L_Error;
	}

	// Installing hook on our function...
	HMODULE library = LoadLibrary(L"UTaskHook.dll");
	void *PerformHookFunc = library ? GetProcAddress(library, L"PerformHook") : NULL;

	if(library == NULL || PerformHookFunc == NULL)
	{
		RETAILMSG(1,(L"Unable to load library!\n"));
		goto L_Error;
	}

	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, UTASK_GLOBAL_HOOK_READY_EVENT);

	CALLBACKINFO callbackInfo;
	callbackInfo.hProc = Proc;
	callbackInfo.pfn = (FARPROC)MapPtrToProcess(PerformHookFunc, Proc);
	callbackInfo.pvArg0 = Proc;			// pass the hooked process ID as parameter to be sure that we are called from the context of hooked process
	PerformCallBack4(&callbackInfo);	// so we call function ourselves, fortunately DLLs are loaded at the same address in all processes
	
	result = ReadEvent(hEvent, 5000);
	CloseHandle(hEvent);

	FreeLibrary(library);

	RETAILMSG(1, (L"Injection completed\n"));
L_Error:
	SetKMode(bMode);
    SetProcPermissions(dwPerm);

	return result;
};
