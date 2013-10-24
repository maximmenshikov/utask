#include "stdafx.h"

UINT ThemeLoader_GetStatusBarSize()
{
	DWORD dwSize = DRA::SCALEY(18);

	if (dwSize == 27)
		dwSize = 25; //HVGA

	return dwSize;
};

UINT ThemeLoader_GetSoftkeyBarSize()
{
	DWORD dwSize = DRA::SCALEY(34);

	if (dwSize == 51)
		dwSize = 45; //HVGA

	return dwSize;
};

