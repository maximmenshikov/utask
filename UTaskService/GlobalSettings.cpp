#include "stdafx.h"
#include "UTask.h"
#include "regext.h"
#include "ExceptionList.h"
#include "TodayWindows.h"
#include "ActionConfiguration.h"

#include "..\UTaskCommon\headers\ThemeLoader.h"

DWORD settingHoldAnimation =1;
DWORD settingHomeIcon = 1;
DWORD settingEnhanceToolbarWindows = 1;
DWORD settingHookTaskBar = 0;

DWORD systemIsHardwareDoneKey = 0;
DWORD systemLayeredWindows = 0;

VOID GlobalSettings_Read(BOOL updateTheme)
{
	ExceptionList_InitializeList();
	TodayWindow_InitializeList();
	ActionCache_Update();
	if (updateTheme == TRUE)
		ThemeLoader_Initialize();

	if (RegistryGetDWORD(UTASK_REG_BRANCH, UTASK_REG_SETTINGS_KEY, 
		L"ShowHoldAnimation", &settingHoldAnimation) != S_OK)
	{
		settingHoldAnimation = 1;
	}
	if (RegistryGetDWORD(UTASK_REG_BRANCH, UTASK_REG_SETTINGS_KEY, 
		L"ShowHomeIcon", &settingHomeIcon) != S_OK)
	{
		settingHomeIcon = 1;
	}
	if (RegistryGetDWORD(UTASK_REG_BRANCH, UTASK_REG_SETTINGS_KEY, 
		L"EnhanceToolbarWindows", &settingEnhanceToolbarWindows) != S_OK)
	{
		settingEnhanceToolbarWindows = 1;
	}
	if (RegistryGetDWORD(UTASK_REG_BRANCH, UTASK_REG_SETTINGS_KEY, 
		L"HookTaskBar", (DWORD*) &settingHookTaskBar) != S_OK)
	{
		settingHookTaskBar = 0;
	}

	if (RegistryGetDWORD(UTASK_BUBBLETILES_REG_BRANCH, UTASK_BUBBLETILES_REG_KEY,
		UTASK_BUBBLETILES_REG_DONE_VALUE, &systemIsHardwareDoneKey) != S_OK)
	{
		systemIsHardwareDoneKey = 0;
	}

	if (RegistryGetDWORD(UTASK_GWE_REG_BRANCH, UTASK_GWE_REG_KEY,
		UTASK_GWE_REG_LW_VALUE, &systemLayeredWindows) != S_OK)
	{
		systemLayeredWindows = 0;
	}
};

VOID GlobalSettings_Read()
{
	GlobalSettings_Read(TRUE);
};

VOID GlobalSettings_Clear(BOOL clearTheme)
{
	ExceptionList_DeinitializeList();
	TodayWindow_DeinitializeList();
	ActionCache_Clear();
	if (clearTheme == TRUE)
		ThemeLoader_Deinitialize();
};

VOID GlobalSettings_Clear()
{
	GlobalSettings_Clear(TRUE);
};

VOID GetLocalizedString(wchar_t *text, wchar_t *name, DWORD locale)
{
	wchar_t branch[512];
	swprintf(branch, L"%ls\\%04x", UTASK_REG_LOCALIZATION_KEY, locale);
	RegistryGetString(HKEY_CURRENT_USER, branch, name, text, 250);
};

DWORD GetCurrentLanguage()
{
	DWORD LangID = 0x409;
	RegistryGetDWORD(HKEY_CURRENT_USER, L"MUI", L"CurLang", &LangID);
	return LangID;
};
