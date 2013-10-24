#include "stdafx.h"
#include "UTask.h"
#include "regext.h"
#include "ExclusiveList.h"
#include "Settings.h"
#include "ThemeLoader.h"
#include "service.h"

volatile DWORD settingIsAutoFix	= 1;
volatile DWORD settingPositionFixEnabled = 1;
volatile DWORD systemIsServiceEnabled = 0;

DWORD sizeStatusBar = 36;
DWORD sizeSoftkeyBar = 68;

VOID Settings_Read()
{
	if (RegistryGetDWORD(UTASK_REG_BRANCH, UTASK_REG_SETTINGS_KEY, 
		L"PositionFix_AutoMode", (DWORD*) &settingIsAutoFix) != S_OK)
	{
		settingIsAutoFix = 1;
	}
	if (RegistryGetDWORD(UTASK_REG_BRANCH, UTASK_REG_SETTINGS_KEY, 
		L"PositionFix", (DWORD*) &settingPositionFixEnabled) != S_OK)
	{
		settingPositionFixEnabled = 1;
	}
	ExclusiveList_InitializeList();

	sizeStatusBar = ThemeLoader_GetStatusBarSize();
	sizeSoftkeyBar = ThemeLoader_GetSoftkeyBarSize();

	HANDLE hService = GetServiceHandle(L"UTS0:", NULL, 0);
	systemIsServiceEnabled = (hService == INVALID_HANDLE_VALUE || hService == NULL) ? FALSE : TRUE;
};

void Settings_Dispose()
{
	__try
	{
		ExclusiveList_DeinitializeList();
	}
	__except (GetExceptionCode())
	{
	}
};

void Settings_Initialize()
{
	Settings_Read();
};

void Settings_Deinitialize()
{
	Settings_Dispose();
};

