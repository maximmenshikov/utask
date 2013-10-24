#include "stdafx.h"
#include "UTask.h"
#include "..\UTaskCommon\headers\SizeCache.h"
#include "GlobalSettings.h"
#include "ActionConfiguration.h"
#include "MenuWorker.h"
#include "service.h"
#include "regext.h"

#define LONG2POINT(l, pt)  ((pt).x = (SHORT)LOWORD(l), (pt).y = (SHORT)HIWORD(l))

LONG taskBarOldWndProc = NULL;

inline VOID ProcessVibration(PRECONFIGURED_COMMAND *command);

PROCESSRESULT AlternativeExecuteCommand(PRECONFIGURED_COMMAND *command)
{
	ProcessVibration(command);
	switch (command->ActionID)
	{
		case ACTION_NOACTION:
				break;
		case ACTION_EXECUTE:
			{
				if (command->fPath)
				{
					SHELLEXECUTEINFO sh;
					memset(&sh, 0, sizeof(SHELLEXECUTEINFO));
					sh.cbSize = sizeof(SHELLEXECUTEINFO);
					sh.lpFile = command->fPath;
					sh.lpParameters = command->fArguments;
					ShellExecuteEx(&sh);
				}
				break;
			}
		case ACTION_STARTMENU:
			{
				keybd_event(VK_LWIN, 0, KEYEVENTF_SILENT, 0);
				keybd_event(VK_LWIN, 0, KEYEVENTF_SILENT | KEYEVENTF_KEYUP, 0);
				break;
			}
		default:
			return PROCESSRESULT_UNKNOWN;
	}
	return PROCESSRESULT_DONTCARE;
};

PROCESSRESULT AlternativeExecuteTask(Task task)
{
	PRECONFIGURED_COMMAND command;
	memset(&command, 0, sizeof(PRECONFIGURED_COMMAND));

	command.task = task;

	UpdateActionConfiguration(&command);
	return AlternativeExecuteCommand(&command);
};

extern "C" HRESULT SHIsLocked(LPDWORD pdwState);

BOOL isLockscreenOnTop()
{
	DWORD lockedState = 0;
	SHIsLocked(&lockedState);
	return lockedState ? TRUE : FALSE;
};

LRESULT CALLBACK TaskBarWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		{
			if (settingHookTaskBar && isLockscreenOnTop() == FALSE)
			{
				POINT point;
				LONG2POINT(lParam, point);

				DWORD displayWidth = GetSystemMetrics(SM_CXSCREEN);
				LONG  workAreaStart = displayWidth - GetSizeCacheItem(SIZE_TASKBAR_CLOCK_WIDTH);
				if (point.x >= workAreaStart)
				{
					if (uMsg == WM_LBUTTONDOWN)
					{
						SHRGINFO shrg; 
						shrg.cbSize = sizeof(shrg); 
						shrg.hwndClient = hWnd; 
						shrg.ptDown.x = point.x; 
						shrg.ptDown.y = point.y; 
						shrg.dwFlags = SHRG_RETURNCMD | SHRG_NOANIMATION;

						if (SHRecognizeGesture(&shrg) == GN_CONTEXTMENU)
							AlternativeExecuteTask(TASK_HOME | TASK_LONG);
						else
							AlternativeExecuteTask(TASK_HOME);

					}
					return 0;
				}
			}
			break;
		}
	}
	return CallWindowProc((WNDPROC)taskBarOldWndProc,hWnd,uMsg,wParam,lParam);
};

VOID Taskbar_SetHook()
{
	HWND taskBar = FindWindow(L"HHTaskBar", NULL);
	taskBarOldWndProc = GetWindowLong(taskBar, GWL_WNDPROC);

	SetWindowLong(taskBar, GWL_WNDPROC, (LONG)TaskBarWndProc);
};

ULONG TaskbarSetHookThread( LPVOID pParam )
{
	// If HTC Notification Manager service exists, we start hooking 
	// after 4 minutes delay to ensure htcntf's hook installed.
	Sleep(60000 * 4);
	
	Taskbar_SetHook();
	return 0;
};


VOID Taskbar_Initialize()
{
	CloseHandle(CreateThread(0, 0, TaskbarSetHookThread, NULL, 0, 0));
};

VOID Taskbar_Deinitialize()
{
	if (taskBarOldWndProc)
	{
		HWND taskBar = FindWindow(L"HHTaskBar", NULL);
		SetWindowLong(taskBar, GWL_WNDPROC, (LONG)taskBarOldWndProc);
		taskBarOldWndProc = NULL;
	}
};

