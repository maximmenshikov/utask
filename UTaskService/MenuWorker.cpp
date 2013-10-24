#include "stdafx.h"
#include "UTask.h"
#include "MenuWorker.h"
#include "regext.h"
#include "nled_device.h"
#include "WindowHandler.h"
#include "ActionConfiguration.h"
#include "GlobalSettings.h"
#include "TodayWindows.h"
#include "DrawRoutines.h"
#include "gesture.h"
#pragma comment (lib, "TouchGestureCore.lib")

#include "..\UTaskCommon\headers\ThemeLoader.h"
#include "..\UTaskCommon\headers\SizeCache.h"

inline LONG GetOldWindowProc(HWND hWnd)
{
	if (hWnd)
		return (LONG)GetProp(hWnd, propLong);
	return NULL;
};

VOID OpenStartMenu()
{				
	keybd_event(VK_LWIN, 0, KEYEVENTF_SILENT, 0);
	keybd_event(VK_LWIN, 0, KEYEVENTF_SILENT | KEYEVENTF_KEYUP, 0);
};

inline VOID ProcessVibration(PRECONFIGURED_COMMAND *command)
{
	if (command->bVibraIndication)
	{
		CloseHandle(CreateThread( 0, 1024, VibrateThread, (LPVOID) command->uVibraTime, STACK_SIZE_PARAM_IS_A_RESERVATION, 0));
	}
};

PROCESSRESULT ExecuteCommand(PRECONFIGURED_COMMAND *command)
{
	if (command == NULL)
		return PROCESSRESULT_STOPEXECUTION;

	ProcessVibration(command);
	switch (command->ActionID)
	{
		case ACTION_NOACTION:
			{
				return command->task & TASK_LONG ? PROCESSRESULT_DONTCARE : 
					PROCESSRESULT_DOSTANDARD;
			}
		case ACTION_EXECUTE:
			{
				__try
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
				}
				__except (GetExceptionCode())
				{
				}
				break;
			}
		case ACTION_CLOSE:
			{
				if (command->ParentWindow != GetDesktopWindow())
					PostMessage(command->MenuWorker, WM_UTASK_PRIVATE_CLOSE, NULL, NULL);

				break;
			}
		case ACTION_MINIMIZE:
			{
				PostMessage(command->MenuWorker, WM_UTASK_PRIVATE_MINIMIZE, NULL, NULL);
				break;
			}
		case ACTION_STARTMENU:
			{
				PostMessage(command->MenuWorker, WM_UTASK_PRIVATE_STARTMENU, NULL, NULL);
				break;
			}
		default:
			return PROCESSRESULT_UNKNOWN;
	}
	return command->task & TASK_LONG ? PROCESSRESULT_DONTCARE : 
		PROCESSRESULT_STOPEXECUTION;
};

PROCESSRESULT ExecuteTask(HWND MenuWorker, Task task)
{
	PRECONFIGURED_COMMAND command;
	memset(&command, 0, sizeof(PRECONFIGURED_COMMAND));

	command.MenuWorker = GetMenuWorker(MenuWorker);
	if (command.MenuWorker)
	{
		command.ParentWindow = GetParent(command.MenuWorker);
		if (command.ParentWindow && IsWindow(command.ParentWindow))
		{
			command.task = task;

			if (command.MenuWorker && command.ParentWindow)
			{
				UpdateActionConfiguration(&command);
				return ExecuteCommand(&command);
			}
		}
	}
	return PROCESSRESULT_DONTCARE;
};


VOID InstallToolbarWindowHook(HWND hWnd)
{
	HWND ToolbarWindow = GetToolbarWindow(hWnd);
	if (ToolbarWindow && IsWindow(ToolbarWindow) == TRUE)
	{
		LONG oldProp = (LONG)GetProp(ToolbarWindow, propLong);
		if (oldProp == NULL)
		{
			LONG oldWndProc = GetWindowLong(ToolbarWindow, GWL_WNDPROC);
			SetProp(ToolbarWindow, propLong, (HANDLE)oldWndProc);
			SetWindowLong(ToolbarWindow, GWL_WNDPROC, (LONG)ToolbarWindow32WndProc); 
		}
	}
};

VOID RemoveToolbarWindowHook(HWND hWnd)
{
	HWND ToolbarWindow = GetToolbarWindow(hWnd);
	if (ToolbarWindow && IsWindow(ToolbarWindow) == TRUE)
	{
		LONG oldProp = (LONG)GetProp(ToolbarWindow, propLong);
		if (oldProp != NULL)
		{
			SetWindowLong(hWnd, GWL_WNDPROC, oldProp);
			RemoveProp(ToolbarWindow, propLong);
		}
	}
};

LONG RemoveHookDirect(HWND hWnd)
{
	if (hWnd && IsWindow(hWnd) == TRUE)
	{
		LONG oldWndProc = (LONG) GetProp(hWnd, propLong);
		if (oldWndProc)
		{
			SetWindowLong(hWnd, GWL_WNDPROC, oldWndProc);
			RemoveProp(hWnd, propLong);
			return oldWndProc;
		}
	}
	return NULL;
};

volatile DWORD todaySelectState = 0;
volatile DWORD todayLongPress = 0;
volatile DWORD todayGestureBeginPress = 0;

LRESULT ToolbarWindow32WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	__try //guarded body
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			{
				LONG oldWndProc = RemoveHookDirect(hWnd);
				if (oldWndProc)
					return CallWindowProc((WNDPROC) oldWndProc, hWnd, uMsg, wParam, lParam);
				return 0;
			}
		case WM_LBUTTONDOWN:
			{
				BOOL isToday = IsTodayWindow(hWnd);
				if (isToday == TRUE && settingHomeIcon)
				{
					int screenWidth = GetSystemMetrics(SM_CXSCREEN);
					int scaledButtonWidth = GetSizeCacheItem(SIZE_ICON_POSITION_OFFSET);
					if (LOWORD(lParam) > (screenWidth - scaledButtonWidth))
					{
						
						todaySelectState = 1;
						RedrawWindow(hWnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
						HWND MenuWorker = GetMenuWorker(hWnd);
						if (MenuWorker)
							RedrawWindow(MenuWorker, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);

						SHRGINFO shrg; 
						shrg.cbSize = sizeof(shrg); 
						shrg.hwndClient = hWnd; 
						shrg.ptDown.x = LOWORD(lParam); 
						shrg.ptDown.y = HIWORD(lParam); 
						shrg.dwFlags = SHRG_RETURNCMD | (settingHoldAnimation ? 0 : SHRG_NOANIMATION);

						if (SHRecognizeGesture(&shrg) == GN_CONTEXTMENU)
						{
							ExecuteTask(hWnd, TASK_HOME | TASK_LONG);

							todaySelectState = 0;
							RedrawWindow(hWnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
							if (MenuWorker)
								RedrawWindow(MenuWorker, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
						}
						return 0;
					}
				}
				break;
			}
		case WM_GESTURE:
			{
				BOOL isToday = IsTodayWindow(hWnd);
				if (isToday == TRUE && settingHomeIcon)
				{
					int screenWidth = GetSystemMetrics(SM_CXSCREEN);
					int scaledButtonWidth = GetSizeCacheItem(SIZE_ICON_POSITION_OFFSET);
					GESTUREINFO gi;
					ZeroMemory(&gi, sizeof(GESTUREINFO));

					gi.cbSize = sizeof(GESTUREINFO);

					if (TKGetGestureInfo((HGESTUREINFO)lParam, &gi))
					{
						if (wParam == GID_SELECT)
						{
							if (gi.ptsLocation.x > (screenWidth - scaledButtonWidth))
							{
								HWND MenuWorker = GetMenuWorker(hWnd);
								ExecuteTask(hWnd, TASK_HOME);
								todaySelectState = 0;
								RedrawWindow(hWnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
								if (MenuWorker)
									RedrawWindow(MenuWorker, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
							}
						}
						else if (wParam == GID_PAN)
						{
							POINT topOfWindow = {0, 0};
							ClientToScreen(hWnd, &topOfWindow);
							DWORD testState = -1;
							HWND MenuWorker = GetMenuWorker(hWnd);
							if (gi.ptsLocation.x > (screenWidth - scaledButtonWidth) && gi.ptsLocation.y > topOfWindow.y && todayGestureBeginPress)
								testState = 1;
							else
								testState = 0;

							if (testState != todaySelectState)
							{
								todaySelectState = testState;
								RedrawWindow(hWnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
								if (MenuWorker)
									RedrawWindow(MenuWorker, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
							}
						}
						else if (wParam == GID_BEGIN)
						{
							POINT topOfWindow = {0, 0};
							ClientToScreen(hWnd, &topOfWindow);
							DWORD testState = -1;
							HWND MenuWorker = GetMenuWorker(hWnd);
							if (gi.ptsLocation.x > (screenWidth - scaledButtonWidth) && gi.ptsLocation.y > topOfWindow.y)
								todayGestureBeginPress = 1;
							else
								todayGestureBeginPress = 0;
						}
						else if (wParam == GID_END)
						{
							todayGestureBeginPress = 0;
							HWND MenuWorker = GetMenuWorker(hWnd);
							todaySelectState = 0;
							RedrawWindow(hWnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
							if (MenuWorker)
								RedrawWindow(MenuWorker, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
						}
					}
				}
				break;
			}
		case WM_LBUTTONUP:
			{
				BOOL isToday = IsTodayWindow(hWnd);
				if (isToday == TRUE && settingHomeIcon)
				{
					if (todaySelectState == 1)
					{
						todaySelectState = 0;
						
						RedrawWindow(hWnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);

						if (HWND MenuWorker = GetMenuWorker(hWnd))
							RedrawWindow(MenuWorker, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
					}
					int screenWidth = GetSystemMetrics(SM_CXSCREEN);
					int scaledButtonWidth = GetSizeCacheItem(SIZE_ICON_POSITION_OFFSET);
					if (LOWORD(lParam) > (screenWidth - scaledButtonWidth))
						return 0;
				}
			}
			break;
		}

		LONG old=(LONG)GetProp(hWnd, propLong);
		if (old)
			return CallWindowProc((WNDPROC)old, hWnd, uMsg, wParam, lParam);
	}
	__except (GetExceptionCode())
	{

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
};

ULONG MenuWorker_MessageBoxThread(LPVOID pParam)
{
	HWND hWnd = (HWND)pParam;
	if (hWnd == NULL)
		return 0;

	DWORD currentLocale = GetCurrentLanguage();

	wchar_t minimizeText[250], closeText[250], todayText[250];
	wcscpy(minimizeText, L"Minimize");
	wcscpy(closeText, L"Close");
	wcscpy(todayText, L"Go to Today screen");

	GetLocalizedString(minimizeText, L"MinimizeText", currentLocale);
	GetLocalizedString(closeText, L"CloseText", currentLocale);
	GetLocalizedString(todayText, L"GoToTodayText", currentLocale);

	HMENU hMenu = CreatePopupMenu();

	if (hMenu)
	{
		AppendMenu(hMenu, MF_STRING, 1, minimizeText);
		AppendMenu(hMenu, MF_STRING, 2, closeText);
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hMenu, MF_STRING, 3, todayText);

		int result = TrackPopupMenuEx(hMenu, TPM_CENTERALIGN | TPM_VCENTERALIGN | TPM_RETURNCMD, 0, 0, NULL, NULL);
		DestroyMenu(hMenu);

		if (result)
		{
			if (IsWindow(hWnd) == TRUE)
			{
				HWND menuBar = SHFindMenuBar(hWnd);
				if (result == 1)
				{
					ShowWindow(hWnd, SW_MINIMIZE);
				}
				else if (result == 2)
				{
					if (menuBar && IsWindow(menuBar) == TRUE)
						PostMessage(menuBar, WM_UTASK_PRIVATE_CLOSE, (WPARAM) 1, NULL);
				}
				else if (result == 3)
				{
					SetForegroundWindow(GetDesktopWindow());
				}
			}
		}
	}
	return 0;
};

LRESULT MenuWorkerWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	__try //guarded body used to improve stability (just in case)
	{
		switch(uMsg)
		{
			
		case WM_GESTURE:
			{
				if (wParam == GID_HOLD && settingEnhanceToolbarWindows)
				{
					HWND MenuWorker = GetMenuWorker(hWnd);
					if (MenuWorker == NULL)
						break;

					HWND Toolbar = GetToolbarWindow(MenuWorker);
					if (Toolbar == NULL)
						break;

					if ((GetWindowLong(Toolbar, GWL_EXSTYLE) & 2 ) == NULL)
						CloseHandle(CreateThread(NULL, 0, MenuWorker_MessageBoxThread, (LPVOID)GetForegroundWindow(), 0, 0));
				}
				break;
			}
		case WM_NOTIFY:
			{
				NMTOOLBAR *pnmtb=(NMTOOLBAR*)lParam;
				if (pnmtb && pnmtb->hdr.code==TBN_BEGINDRAG)
				{
					if (pnmtb->iItem==COMMAND_WINKEY || pnmtb->iItem==COMMAND_CLOSEKEY)
					{
						BOOL isToday = IsTodayWindow(hWnd);

						HWND captureWindow = GetCapture();
						if (captureWindow)
						{
							POINT point;
							GetCursorPos(&point);
							ScreenToClient(captureWindow,&point);

							SHRGINFO shrg; 
							shrg.cbSize = sizeof(shrg); 
							shrg.hwndClient = captureWindow; 
							shrg.ptDown.x = point.x; 
							shrg.ptDown.y = point.y; 
							shrg.dwFlags = SHRG_RETURNCMD | (settingHoldAnimation ? 0 : SHRG_NOANIMATION);

							if (SHRecognizeGesture(&shrg) == GN_CONTEXTMENU)
							{
								todayLongPress = 1;
								if (pnmtb->iItem == COMMAND_WINKEY)
								{
									ExecuteTask(hWnd, TASK_LKEY | TASK_LONG);
								}
								else
								{
									if (isToday == FALSE)
										ExecuteTask(hWnd, TASK_RKEY | TASK_LONG);
									else
									{
										ExecuteTask(hWnd, TASK_HOME | TASK_LONG);
										return 0;
									}
								}
								DWORD res = SendMessage(captureWindow, 0x412, pnmtb->iItem, NULL);
								DWORD lParam = 0xFFFD & ((res << 16 ) >> 16);
								SendMessage(captureWindow, 0x411, pnmtb->iItem, lParam);
							}
							else
							{
								todayLongPress = 0;
								if (isToday == TRUE && pnmtb->iItem == COMMAND_CLOSEKEY)
								{
									ExecuteTask(hWnd, TASK_HOME);
									return 0;
								}
							}
						}
					}
				}
				break;
			}
		case WM_DESTROY:
			{
				LONG oldWndProc = RemoveHookDirect(hWnd);
				if (oldWndProc)
					return CallWindowProc((WNDPROC) oldWndProc, hWnd, uMsg, wParam, lParam);
				return 0;
			}
		case WM_COMMAND:
			if (todayLongPress == 1)
			{
				todayLongPress = 0;
				return 0;
			}
			if(LOWORD(wParam) == COMMAND_WINKEY)
			{
				UINT res = ExecuteTask(hWnd, TASK_LKEY);
				if (res == PROCESSRESULT_STOPEXECUTION)
					return 0;
			}
			else if(LOWORD(wParam) == COMMAND_CLOSEKEY)
			{
				UINT res = ExecuteTask(hWnd, TASK_RKEY);
				if (res == PROCESSRESULT_STOPEXECUTION)
					return 0;
			}
			break;
		case WM_ERASEBKGND:
			{
				if (settingHomeIcon == 0 || systemIsHardwareDoneKey == 1)
					break;
				
				BOOL isToday = IsTodayWindow(hWnd);
				if (isToday == TRUE)
				{
					InstallToolbarWindowHook(hWnd);

					LONG old = (LONG) GetProp(hWnd, propLong);
					CallWindowProc((WNDPROC)old, hWnd, uMsg, wParam, lParam);
					HDC hdc = (HDC)wParam;

					int width = GetSystemMetrics(SM_CXSCREEN);

					int iconSizeWidth = ThemeLoader_GetSoftkeyBarSize();
					int iconSizeHeight = iconSizeWidth;
					int iconOffset = GetSizeCacheItem(SIZE_ICON_POSITION_OFFSET);

					HBITMAP hbm = todaySelectState ? hBackground_Selected : hBackground;
					BITMAP *bm = todaySelectState ? &bmpBackground_Selected : &bmpBackground;
					if (hbm && systemLayeredWindows)
					{
						DrawImage(hdc, hbm, width - iconOffset, 0, iconSizeWidth, iconSizeHeight, bm->bmWidth, bm->bmHeight);
					}
					else if (systemLayeredWindows == 0 && todaySelectState)
					{
						RECT rect = {width - iconOffset, 0, width - iconOffset + iconSizeWidth, 0 + iconSizeHeight};
						FillRect(hdc, &rect, (HBRUSH)GetStockObject(LTGRAY_BRUSH));
					}
					if (hTaskManagerIcon)
						DrawImage(hdc, hTaskManagerIcon, width - iconOffset, 0, iconSizeWidth, iconSizeHeight);
					
					return TRUE;
				}
				else
				{
					RemoveToolbarWindowHook(hWnd);
					todaySelectState = 0;
				}
				break;
			}
		case WM_UTASK_PRIVATE_MINIMIZE:
			{
				HWND MenuWorker = GetMenuWorker(hWnd);
				if (MenuWorker && IsWindow(MenuWorker) == TRUE)
				{
					HWND parentWindow = GetParent(MenuWorker);


					if (parentWindow && IsWindow(parentWindow) == TRUE)
					{
						wchar_t className[50];
						GetClassName(parentWindow, className, 50);
						if (wcscmp(className, L"HTCMENUBGWND") == 0)
						{
							// special fix for newest menuenhancements
							DWORD result;
							SendMessageTimeout(parentWindow, WM_COMMAND, 0x138E, NULL, SMTO_NORMAL, 1000, &result);
						}
						else
						{
							LONG exStyle = GetWindowLong(parentWindow, GWL_EXSTYLE);
							if (exStyle & WS_EX_CAPTIONOKBTN)
							{
								LONG oldWndProc = GetOldWindowProc(hWnd);
								if (oldWndProc)
									return CallWindowProc((WNDPROC) oldWndProc, hWnd, WM_COMMAND, 
									(WPARAM) COMMAND_CLOSEKEY, 
									(LPARAM) GetToolbarWindow(MenuWorker));
							}
							else
							{
								ShowWindow(parentWindow, SW_MINIMIZE);
							}
						}
					}
				}
				break;
			}
		case WM_UTASK_PRIVATE_CLOSE:
			{
				HWND MenuWorker = GetMenuWorker(hWnd);
				if (MenuWorker && IsWindow(MenuWorker) == TRUE)
				{
					HWND parentWindow = GetParent(MenuWorker);

					DWORD forceClose = (DWORD)wParam;
					if (parentWindow && 
						IsWindow(parentWindow) == TRUE && 
						Window_Close(parentWindow, forceClose) == 0)
					{
						LONG oldWndProc = GetOldWindowProc(hWnd);
						if (oldWndProc)
							return CallWindowProc((WNDPROC) oldWndProc, hWnd, WM_COMMAND, 
							(WPARAM) COMMAND_CLOSEKEY, 
							(LPARAM) GetToolbarWindow(MenuWorker));
					}
				}
				break;
			}
		case WM_UTASK_PRIVATE_STARTMENU:
			{
				HWND MenuWorker = GetMenuWorker(hWnd);
				if (MenuWorker)
				{
					LONG oldWndProc = (LONG) GetProp(hWnd, propLong);
					return CallWindowProc((WNDPROC) oldWndProc, hWnd, WM_COMMAND, 
						(WPARAM) COMMAND_WINKEY, 
						(LPARAM) GetToolbarWindow(MenuWorker));
				}
				break;
			}
		}

		LONG old = GetOldWindowProc(hWnd);
		if (old)
			return CallWindowProc((WNDPROC)old, hWnd, uMsg, wParam, lParam);
	}
	__except (GetExceptionCode())
	{

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
};
