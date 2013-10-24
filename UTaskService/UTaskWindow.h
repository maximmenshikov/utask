/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  UTaskWindow.h:
  -provides an access to all internal window's function declarations
*/
#ifndef UTASK_WINDOW_H
#define UTASK_WINDOW_H

// functions declarations
	LRESULT	CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	ULONG	UTaskThread(LPVOID pParam);
	BOOL	InitInstance();

#endif
