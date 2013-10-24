#include "stdafx.h"

#define NAMES_COUNT 1
#define CLASSES_COUNT 2
static wchar_t *predefinedNames[]={L"BugMe!"};
static wchar_t *predefinedClasses[]={L"Dialog", L"CECMD"};

DWORD IsDoubleFixWindow(HWND hWnd)
{
	wchar_t className[50];
	className[0] = L'\0';
	GetClassName(hWnd, className, 50);
	for (int x = 0; x < CLASSES_COUNT; x++)
	{
		if (wcscmp(className, predefinedClasses[x]) == 0)
			return 1;
	}

	wchar_t name[50];
	GetWindowText(hWnd, name, 50);
	for (int x = 0; x < NAMES_COUNT; x++)
	{
		if (wcscmp(name, predefinedNames[x]) == 0)
			return 2;
	}
	return 0;
};
