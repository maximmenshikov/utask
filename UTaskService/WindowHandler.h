/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  WindowHandler.h:
  -all window-related functions and enums
*/
#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

// definitions
	#define propLong		L"{9094e6a3-8e65-4561-bb0c-8d34f555d702}"

// enumerations and types
	typedef unsigned int RESULT;

	enum Result {
		RESULT_OK,
		RESULT_ERROR
	};

// functions declarations
	RESULT WindowHandler_SetWindowProc(HWND hWnd, LONG newLng);
	RESULT WindowHandler_SetDefaultWindowProc(HWND hWnd);
	RESULT WindowHandler_PatchAllWindows();
	RESULT WindowHandler_ReturnAllWindows();
	UINT Window_Close(HWND hWnd, DWORD forceClose);
	HWND GetMenuWorker(HWND hWnd);
	HWND GetToolbarWindow(HWND hWnd);

#endif
