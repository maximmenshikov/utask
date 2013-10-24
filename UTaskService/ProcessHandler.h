/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  ProcessHandler.h:
  -all process related functions
*/
#ifndef PROCESSHANDLER_H
#define PROCESSHANDLER_H

// functions declarations
	LONG	Process_GetID(LPWSTR name);
	ULONG	Process_KillThread(LPVOID pParam);

	BOOL Process_ForceKill(DWORD processID, HWND hWnd);
	ULONG Process_ForceKillThread(LPVOID pParam);

	typedef struct
	{
		DWORD processID;
		HWND hWnd;
	}PROCESSFKILLPARAM;

#endif