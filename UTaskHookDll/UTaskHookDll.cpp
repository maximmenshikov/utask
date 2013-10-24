#include "stdafx.h"
#include "UTask.h"
#include "StringUtils.h"
#include "Settings.h"
#include "PositionFix.h"
#include "Logger.h"
#include "InfiniteLoops.h"
#include "DoubleFix.h"

t_CreateWindowEx OldCreateWndEx;
t_DestroyWindow OldDestroyWnd;

#ifdef FEATURE_POSITIONFIX

	t_SetWindowPos OldSetWndPos;
	t_MoveWindow OldMoveWindow;
	t_DeferWindowPos OldDeferWindowPos;
	t_ShowWindow OldShowWindow;
	t_CreateDialogIndirectParamW OldCreateDialogIndirectParamW;

#endif

#define FIXPROC_PROP L"{5bf33c5a-9fd3-486a-8b5d-2bdcc8cce88d}"
LRESULT DialogFixProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL _DestroyWindowHook(HWND hWnd)
{
	Log(FUNCTION_DESTROYWINDOW, hWnd, 0, 0);
	KillLoopInfo(hWnd);
	return OldDestroyWnd(hWnd);
};

BOOL IsAglWindow(wchar_t *className)
{
	if (className)
		return wcsstr(className, L"AGL") ? TRUE : FALSE;
	return FALSE;
};

BOOL IsDialogWindow(wchar_t *className);

ULONG AsyncSendMessageThread( LPVOID pParam )
{
	HWND hWnd = (HWND) pParam;
	HWND uTaskWnd = FindWindow(UTS_WND_CLASS,NULL);
	if (uTaskWnd)
		PostMessage(uTaskWnd, WM_UTASK_WINDOW_CREATED, (WPARAM)hWnd, NULL);
	return 0;
};

HWND _CreateWindowExHook(DWORD dwExStyle,
						  LPCTSTR lpClassName,
						  LPCTSTR lpWindowName,
						  DWORD dwStyle,
						  int x,
						  int y,
						  int nWidth,
						  int nHeight,
						  HWND hWndParent,
						  HMENU hMenu,
						  HINSTANCE hInstance,
						  LPVOID lpParam,
						  LPVOID lpUnk)
{
	HWND ret = OldCreateWndEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y,
				nWidth, nHeight, hWndParent, hMenu, 
				hInstance, lpParam, lpUnk);

	if (ret)
	{
		wchar_t className[50];
		ZeroString(className, 50);
		GetClassName(ret, className, 50);

		if (wcslen(className))
		{
			Log(FUNCTION_CREATEWINDOW, ret, y, nHeight);
#ifdef FEATURE_POSITIONFIX
			if (settingPositionFixEnabled && systemIsServiceEnabled && IsWindow(ret) == TRUE)
			{
				if (((hWndParent == NULL) || ((dwStyle & WS_CHILD) == NULL)) && (dwStyle & WS_VISIBLE)) //&& IsAglWindow(ret) == FALSE)
				{
					DWORD isDoubleFix = IsDoubleFixWindow(ret);
					if (isDoubleFix == 1)
					{
						LONG wndProc = GetWindowLong(ret, GWL_WNDPROC);
						SetProp(ret, FIXPROC_PROP, (HANDLE)wndProc);
						SetWindowLong(ret, GWL_WNDPROC, (LONG)DialogFixProcHook);
					}
					if (IsAglWindow(className) == FALSE)
					{
						CloseHandle(CreateThread(0, 0, AsyncFixThread, (LPVOID)ret, 0, 0));
					}
				}
			}

#endif
			if (wcscmp(className, L"menu_worker") == 0)
			{
				CloseHandle(CreateThread(0, 0, AsyncSendMessageThread, (LPVOID)ret, 0, 0));
			}
		}
	}
	return ret;
};

#ifdef FEATURE_POSITIONFIX

BOOL _ShowWindowHook(HWND hWnd,
					INT nCmdShow)
{
	BOOL result = OldShowWindow(hWnd, nCmdShow);
	
	Log(FUNCTION_SHOWWINDOW, hWnd, 0, 0);
	
	if ((nCmdShow & SW_SHOWNORMAL) && settingPositionFixEnabled && systemIsServiceEnabled && IsWindow(hWnd) == TRUE)
	{
		
		RECT rect = {0, 0, 0, 0};
		GetWindowRect(hWnd, &rect);

		int nY = rect.top, nCY = rect.bottom - rect.top;
		wchar_t className[50];
		className[0] = L'\0';
		GetClassName(hWnd, className, 50);
		if (wcslen(className) && FixPosition(hWnd, className, 0, &nY, &nCY) == TRUE)
			OldSetWndPos(hWnd, NULL, rect.left, nY, rect.right - rect.left, nCY, SWP_NOZORDER);
	}
	return result;
};

BOOL IsSipWindowVisible();
BOOL GetSipInfo(SIPINFO * si);

BOOL IsSizeOk(int x, int size)
{
	if (x == 0 && size == GetSystemMetrics(SM_CXSCREEN))
		return TRUE;
	return FALSE;
};

typedef struct
{
	HWND hWnd;
	DWORD timeStamp;
	DWORD num;
}SIPINFOCHANGE;

SIPINFOCHANGE lastChange;

BOOL SHSipInfo_(HWND hWnd, UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
	DWORD ticks = GetTickCount();
	if (lastChange.hWnd == hWnd)
	{
		if ((ticks - lastChange.timeStamp) < 500)
		{
			lastChange.num++;
		}
		else
		{
			lastChange.num = 0;
		}
		lastChange.timeStamp = ticks;
	}
	else
	{
		lastChange.hWnd = hWnd;
		lastChange.timeStamp = ticks;
		lastChange.num = 0;
	}
	if (lastChange.num == 0)
	{
		return SHSipInfo(uiAction, uiParam, pvParam, fWinIni);
	}
	return FALSE;
};

ULONG DialogFixThread(LPVOID pParam)
{
	Sleep(200);
	HWND hWnd = (HWND)pParam;

	if (IsWindow(hWnd) == TRUE)
	{
		RECT rect = {0, 0, 0, 0};
		GetWindowRect(hWnd, &rect);
		
		int newY = rect.top;
		int newCy = rect.bottom - rect.top;
		
		wchar_t windowName[50];
		ZeroString(windowName, 50);
		GetWindowText(hWnd, windowName, 50);

		wchar_t className[50];
		ZeroString(className, 50);
		GetClassName(hWnd, className, 50);
			
		if (ShouldBeProcessed(className) == TRUE)
		{
			if (IsDoubleFixWindow(hWnd) == TRUE && IsSipWindowVisible() == TRUE && IsSizeOk(rect.left, rect.right - rect.left) == TRUE)
			{
				SIPINFO si;
				GetSipInfo(&si);
				SHSipInfo_(hWnd, SPI_SETSIPINFO, 0, &si, 0);
			}

			if (wcslen(className) && FixPosition(hWnd, className, 0, &newY, &newCy) == TRUE)
				SetWindowPos(hWnd, NULL, rect.left, newY, rect.right - rect.left, newCy, SWP_NOZORDER);
		}
	}
	return 0;
};

BOOL _SetWindowPosHook(HWND hWnd, 
				  HWND hWndInsertAfter, 
				  int X, 
				  int Y, 
				  int cx, 
				  int cy, 
				  UINT uFlags)
{
	int newY = Y;
	int newCy = cy;

	Log(FUNCTION_SETWNDPOS, hWnd, Y, cy);

	BOOL posFix = FALSE;
	if (systemIsServiceEnabled && IsWindow(hWnd) == TRUE)
	{
		wchar_t className[50];
		ZeroString(className, 50);
		GetClassName(hWnd, className, 50);
		if (wcslen(className) && FixPosition(hWnd, className, uFlags, &newY, &newCy) == TRUE)
		{
			if (DetectInfiniteLoop(hWnd, Y, cy) == TRUE)
			{
				return OldSetWndPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
			}
			
			else if (IsDialogWindow(className) == TRUE)
			{
				CloseHandle(CreateThread(0, 0, DialogFixThread, (LPVOID)hWnd, 0, 0));
				return OldSetWndPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
			}
		}
	}
	
	return OldSetWndPos(hWnd, hWndInsertAfter, X, newY, cx, newCy, uFlags);
};


BOOL _MoveWindowHook(HWND hWnd,
					 int X,
					 int Y,
					 int nWidth,
					 int nHeight,
					 BOOL bRepaint)
{
	int newY = Y;
	int newCy = nHeight;

	Log(FUNCTION_MOVEWINDOW, hWnd, Y, nHeight);
	
	if (systemIsServiceEnabled && IsWindow(hWnd) == TRUE)
	{
		wchar_t className[50];
		ZeroString(className, 50);
		GetClassName(hWnd, className, 50);
		if (wcslen(className) && FixPosition(hWnd, className, 0, &newY, &newCy) == TRUE)
		{
			if (DetectInfiniteLoop(hWnd, Y, nHeight) == TRUE)
			{
				return OldMoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint);
			}
			
			else if (IsDialogWindow(className) == TRUE)
			{
				CloseHandle(CreateThread( 0, 0, DialogFixThread, (LPVOID)hWnd, 0, 0));
				return OldMoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint);
			}
			
		}
	}

	return OldMoveWindow(hWnd, X, newY, nWidth, newCy, bRepaint);
};


HDWP _DeferWindowPosHook(
		  HDWP hWinPosInfo,
		  HWND hWnd,
		  HWND hWndInsertAfter,
		  int x,
		  int y,
		  int cx,
		  int cy,
		  UINT uFlags)
{
	int newY = y;
	int newCy = cy;

	Log(FUNCTION_DEFERWNDPOS, hWnd, y, cy);

	if (systemIsServiceEnabled && IsWindow(hWnd) == TRUE)
	{
		wchar_t className[50];
		ZeroString(className, 50);
		GetClassName(hWnd, className, 50);

		if (wcslen(className) && FixPosition(hWnd, className, uFlags, &newY, &newCy) == TRUE)
		{
			if (DetectInfiniteLoop(hWnd, y, cy) == TRUE)
				return OldDeferWindowPos(hWinPosInfo, hWnd, hWndInsertAfter, x, y, cx, cy, uFlags);
		}
	}

	return OldDeferWindowPos(hWinPosInfo, hWnd, hWndInsertAfter, x, newY, cx, newCy, uFlags/* | SWP_UTASK*/);
};

LRESULT DialogFixProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LONG WndProc = (LONG)GetProp(hWnd, FIXPROC_PROP);
	__try
	{
		if (uMsg == WM_SETTINGCHANGE)
		{
			
			LRESULT lres = CallWindowProc((WNDPROC)WndProc, hWnd, uMsg, wParam, lParam);
			if (systemIsServiceEnabled && settingPositionFixEnabled)
			{
				RECT rect = {0, 0, 0, 0};
				if (GetWindowRect(hWnd, &rect) == TRUE && IsSizeOk(rect.left, rect.right - rect.left) == TRUE)
				{
					SIPINFO si;
					GetSipInfo(&si);
					SHSipInfo_(hWnd, SPI_SETSIPINFO, 0, &si, 0);
				}
			}
			return lres;
		}
		else if (uMsg == WM_DESTROY)
		{
			SetWindowLong(hWnd, GWL_WNDPROC, WndProc);
			RemoveProp(hWnd, FIXPROC_PROP);
		}
	}
	__except (GetExceptionCode())
	{
	}
	if (WndProc)
		return CallWindowProc((WNDPROC)WndProc, hWnd, uMsg, wParam, lParam);
	return 0;
}
HWND _CreateDialogIndirectParamW(
								 HINSTANCE hInstance,
								 LPCDLGTEMPLATEW lpTemplate,
								 HWND hWndParent,
								 DLGPROC lpDialogFunc,
								 LPARAM dwInitParam,
								 LPVOID unk
								 )
{
	HWND hWnd = OldCreateDialogIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, dwInitParam, unk);

	if (hWnd && systemIsServiceEnabled && IsWindow(hWnd) == TRUE && IsDoubleFixWindow(hWnd) == TRUE)
	{
		CloseHandle(CreateThread(0, 0, DialogFixThread, (LPVOID)hWnd, 0, 0));
	}

	return hWnd;
};

#endif 


BOOL HookApiFunction(int addr, LPVOID HookFunction, LONG *Old)
{
	__try
	{
		BOOL bMode = SetKMode(TRUE);
		DWORD dwPerm = SetProcPermissions(0xFFFFFFFF);
		CINFO **SystemAPISets= (CINFO **)KData.aInfo[KINX_APISETS];

		DWORD Tmp = (FIRST_METHOD - addr) / APICALL_SCALE;  
		DWORD ApiSet = (Tmp >> HANDLE_SHIFT) & HANDLE_MASK;
		DWORD Method = Tmp & METHOD_MASK;

		// validating api sets table
		if(ApiSet > NUM_SYSTEM_SETS || SystemAPISets[ApiSet] == NULL)
		{
			// Invalid Api Set
			return FALSE;
		}
		if(SystemAPISets[ApiSet]->cMethods <= Method)
		{
			// Invalid method number
			return FALSE;
		}

		if(SystemAPISets[ApiSet]->pServer == NULL)
		{
			// pServer is NULL
			return FALSE; 
		}

		// ppfnMethods sometimes is located in ROM, relocate to RAM to make it writeable
		void **NewMethods = (void**)malloc(SystemAPISets[ApiSet]->cMethods * 4);
		memcpy(NewMethods, SystemAPISets[ApiSet]->ppfnMethods, SystemAPISets[ApiSet]->cMethods * 4);

		SystemAPISets[ApiSet]->ppfnMethods = (PFNVOID*)MapPtrToProcess(NewMethods, GetCurrentProcess());

		Old[0] = (LONG)SystemAPISets[ApiSet]->ppfnMethods[Method];
		SystemAPISets[ApiSet]->ppfnMethods[Method] = (PFNVOID)HookFunction;

		SetKMode(bMode);
		SetProcPermissions(dwPerm);
	}
	__except (GetExceptionCode())
	{
	}
	return TRUE;
};

extern "C" __declspec(dllexport) BOOL PerformHook(HMODULE hModule)
{
	static bool hooked=false;

	if((DWORD)hModule != (DWORD)GetCurrentProcessId())	// to be sure that we are called from correct process
		return FALSE;
	if(hooked) 
		return TRUE;

	hooked = true;

	// That's a bit strange that we hook different API functions using one library... 
	// Fortunately all functions are located in gwes.exe, so we don't care
	HookApiFunction(CREATEWNDEXW, _CreateWindowExHook, (LONG*)&OldCreateWndEx);
	HookApiFunction(DESTROYWND, _DestroyWindowHook, (LONG*)&OldDestroyWnd);

#ifdef FEATURE_POSITIONFIX

	HookApiFunction(SETWNDPOS, _SetWindowPosHook, (LONG*)&OldSetWndPos);
	HookApiFunction(MOVEWINDOW, _MoveWindowHook, (LONG*)&OldMoveWindow);
	HookApiFunction(DEFERWNDPOS, _DeferWindowPosHook, (LONG*)&OldDeferWindowPos);
	HookApiFunction(SHOWWINDOW, _ShowWindowHook, (LONG*)&OldShowWindow);
	HookApiFunction(CREATEDIALOGINDIRECTPARAMW, _CreateDialogIndirectParamW, (LONG*)&OldCreateDialogIndirectParamW);

#endif
	// API function hooked, now we should inform service part about it.
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, UTASK_GLOBAL_HOOK_READY_EVENT);
	SetEvent(hEvent);

	SettingsReader_Start(MODE_INITIALIZE);
	SettingsUpdater_Start();

	return TRUE;
};

BOOL initializationDone = FALSE;

ULONG AttachThread(LPVOID pParam)
{
	if (initializationDone == FALSE)
	{
		HANDLE hGlobalHookLibraryReadyEvent = CreateEvent(NULL, TRUE, FALSE,  UTASK_GLOBAL_HOOKLIB_READY_EVENT);
		SetEvent(hGlobalHookLibraryReadyEvent);
	}
	initializationDone = TRUE;
	return 0;
};

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls((HINSTANCE)hModule);
		if (initializationDone == FALSE)
			CreateThread(NULL, 0, AttachThread, NULL, 0, NULL);
		break;
	}
	return TRUE;
};


