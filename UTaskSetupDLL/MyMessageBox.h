/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  MyMessageBox.h:
  -message box wrapper for better htc devices user experience
*/
#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

// functions prototypes
	typedef int (*HTCMESSAGEBOX)(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType, LPVOID null);

// functions declarations
	int MyMessageBox(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);

	void MyMessageBox_Initialize();
	void MyMessageBox_Deinitialize();

#endif