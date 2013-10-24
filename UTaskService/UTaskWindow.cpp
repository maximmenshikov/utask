#include "stdafx.h"
#include "UTask.h"
#include "UTaskWindow.h"
#include "regext.h"
#include "WindowHandler.h"
#include "MenuWorker.h"
#include "ActionConfiguration.h"
#include "ExceptionList.h"
#include "GlobalSettings.h"
#include "InjectToGwes.h"
#include "EventWrapper.h"
#include "TaskBarHandler.h"
#include "..\UTaskCommon\headers\ThemeLoader.h"
#include "MyMessageBox.h"
#include "SavedState.h"

BOOL ServiceReady = FALSE;
HWND uTaskWindow = NULL;

VOID ZeroString(wchar_t *string, int size);

//#define UTASK_INIT_THREAD_FINISHED L"Global\\UTask\\InitThreadFinished"

HANDLE hInitThreadFinishedEvent = NULL;

BOOL WaitForAPI(wchar_t *apiName)
{
	// Uses an API if it's ready, waits for it if it's not ready
	ApiState state = APISTATE_UNKNOWN;
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, 0, apiName);
	if (hEvent)
	{
		// Wait for the API set to be ready.
		WaitForSingleObject(hEvent, INFINITE);
		CloseHandle(hEvent);
		state = APISTATE_READY;
		return TRUE;
	}
	else
	{
		// The API set will never be ready.
		state = APISTATE_NEVER;
		return FALSE;
	}
};

ULONG InitThread( LPVOID pParam)
{
	ApiState apiState = APISTATE_READY;

	if (WaitForAPI(GWE_API_EVENT_NAME) == FALSE)
		apiState = APISTATE_NEVER;

	if (WaitForAPI(SHELL_API_EVENT_NAME) == FALSE)
		apiState = APISTATE_NEVER;


	SavedState savedState = GetState();

	if (savedState != SAVEDSTATE_INITTHREAD_STARTED_TWICE)
	{
		if (apiState == APISTATE_READY)
		{
			//Sleep(15000);
			int retries = 0;
			while (retries < 10)
			{
				if (FindWindow(L"menu_worker", NULL))
					break;
				Sleep(5000);
				retries++;
			}
			//Sleep(30000);
			
			RECT rect = {0, 0, 0, 0};
			GetWindowRect(FindWindow(L"HHTaskBar", NULL), &rect);

			DWORD size = rect.bottom - rect.top;

			if (size == ThemeLoader_GetStatusBarSize())
			{
				SetState(SAVEDSTATE_CORRECT_OS_DETECTED);

				if (savedState == SAVEDSTATE_INITTHREAD_STARTED)
					SetState(SAVEDSTATE_INITTHREAD_STARTED_TWICE);
				else
					SetState(SAVEDSTATE_INITTHREAD_STARTED);

				// GWE api set is ready to use, so we start uTask initialization
				InjectToGwes(CREATEWNDEXW);
				ServiceReady = TRUE;

				HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, UTASK_GLOBAL_HOOK_UPDATE_EVENT);
				SetEvent(hEvent);
				CloseHandle(hEvent);
			}
			else
			{
				SetState(SAVEDSTATE_INCORRECT_OS_ERROR);
			}
		}
	}

	SetEvent(hInitThreadFinishedEvent);

	return 0;
};

ULONG UTaskThread( LPVOID pParam )
{
	hInitThreadFinishedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	ResetEvent(hInitThreadFinishedEvent);

	CloseHandle(CreateThread(NULL, 0, InitThread, NULL, 0, NULL));

	if (WaitForSingleObject(hInitThreadFinishedEvent, 50000) == WAIT_OBJECT_0)
	{
		if (GetState() != SAVEDSTATE_INCORRECT_OS_ERROR)
		{
			InitInstance();
			SetState(SAVEDSTATE_INITTHREAD_FINISHED);
		}
	}

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
	  TranslateMessage(&msg);
	  DispatchMessage(&msg);
	}
	return 0;
};


ATOM MyRegisterClass(LPTSTR szWindowClass)
{
	WNDCLASS wc;
	
	wc.style         = CS_DBLCLKS;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = GetModuleHandle(NULL);
	wc.hIcon         = 0;
	wc.hCursor       = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = szWindowClass;

	return RegisterClass(&wc);
};

BOOL InitInstance()
{
	HWND foregroundWindow = GetForegroundWindow();
	
	// If our window already exists, exit
    if (FindWindow(UTS_WND_CLASS, NULL)) 
        return FALSE;

	// If class registration failed, exit
    if (MyRegisterClass(UTS_WND_CLASS) == NULL)
    	return FALSE;

    HWND hWnd = CreateWindow(UTS_WND_CLASS, 
						NULL, 
						WS_DISABLED,
						CW_USEDEFAULT, 
						CW_USEDEFAULT, 
						CW_USEDEFAULT, 
						CW_USEDEFAULT, 
						NULL, 
						NULL, 
						GetModuleHandle(NULL), 
						NULL);

    if (hWnd == NULL)
        return FALSE;

	// If window creation was successful, hide our new window from user's eyes
	uTaskWindow = hWnd;
    ShowWindow(hWnd, SW_HIDE);
	SetForegroundWindow(foregroundWindow);

    return TRUE;
};

BOOL IsAglWindow(HWND hWnd)
{
	wchar_t str[50];
	ZeroString(str, 50);

	GetClassName(hWnd, str, 50);

	if (wcslen(str) && wcsstr(str, L"AGL"))
		return TRUE;
	return FALSE;
};


ULONG HookBeginThread( LPVOID pParam )
{
	HWND NewHwnd = (HWND) pParam;

	BOOL isNetAgl = FALSE;
	HWND ownerWindow = GetParent(NewHwnd);
	if (ownerWindow)
		isNetAgl = IsAglWindow(ownerWindow);
	
	if (isNetAgl == FALSE)
	{
		// little delay is needed to guarantee that window is ready
		for (int x = 0; x < 20; x++)
		{
			Sleep(100);
			if (IsWindow(NewHwnd) == FALSE)
				return 0;
			if (IsWindowVisible(NewHwnd) == TRUE && IsWindowEnabled(NewHwnd) == TRUE)
				break;
		}

		Sleep(100);
	}
	else
	{
		Sleep(2000);
	}
	// system has just made a menu_worker and we try to hook it
	if (IsWindow(NewHwnd) == TRUE)
		WindowHandler_SetWindowProc(NewHwnd, (LONG)MenuWorkerWndProc);

	return 0;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) 
	{
	case WM_UTASK_WINDOW_CREATED:
		{
			// We've got a message from hook part. Let's take a look at it...
			HWND NewHwnd = (HWND) wParam;

			if (NewHwnd == NULL)
				break;
			if (IsWindow(NewHwnd) == FALSE)
				break;

			wchar_t className[50];
			ZeroString(className, 50);
			GetClassName(NewHwnd, className, 50);

			if (wcslen(className) && wcscmp(className, L"menu_worker") == 0)
			{
				CloseHandle(CreateThread(0, 0, HookBeginThread, (LPVOID)NewHwnd, 0, 0));
			}

			break;
		}
	case WM_UTASK_NORMAL_IMAGE_CHANGED:
		{
			ThemeLoader_UnloadNormalImage();
			ThemeLoader_LoadNormalImage();
			break;
		}
	case WM_UTASK_SELECTED_IMAGE_CHANGED:
		{
			ThemeLoader_UnloadSelectedImage();
			ThemeLoader_LoadSelectedImage();
			break;
		}
	case WM_DESTROY:
		{
			WindowHandler_ReturnAllWindows();
			GlobalSettings_Clear();
			Taskbar_Deinitialize();
			MyMessageBox_Deinitialize();
			break;
		}
	case WM_CREATE:
		{
			WindowHandler_PatchAllWindows();
			GlobalSettings_Read();
			Taskbar_Initialize();
			MyMessageBox_Initialize();
			break;
		}
	}
    return 0;
};

