#include "stdafx.h"
#include "MyMessageBox.h"

HTCMESSAGEBOX htcMessageBox = NULL;

HMODULE htcAfe = NULL;

typedef enum
{
	LIBRARYSTATE_READY,
	LIBRARYSTATE_ERROR
}LibraryState;

LibraryState MyMessageBox_GetLibraryState()
{
	if (htcAfe && htcMessageBox)
		return LIBRARYSTATE_READY;
	else 
		return LIBRARYSTATE_ERROR;
};
void MyMessageBox_Initialize()
{
	if (htcAfe == NULL)
	{
		htcAfe = LoadLibrary(L"htcAfe.dll");
		if (htcAfe != NULL)
			htcMessageBox = (HTCMESSAGEBOX)GetProcAddress(htcAfe, L"htcMessageBox");
		else
			htcMessageBox = NULL;
	}
};

void MyMessageBox_Deinitialize()
{
	if (htcAfe)
		FreeLibrary(htcAfe);
	htcAfe = NULL;
	htcMessageBox = NULL;
};

int MyMessageBox(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
	if (MyMessageBox_GetLibraryState() == LIBRARYSTATE_READY)
		return htcMessageBox(hWnd, lpText, lpCaption, uType, NULL);
	else
		return MessageBox(hWnd, lpText, lpCaption, uType);
};
