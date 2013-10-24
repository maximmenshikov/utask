#include "stdafx.h"
#include "regext.h"

#include "..\headers\UTaskVariables.h"
#include "..\headers\ImageHandler.h"

HBITMAP hTaskManagerIcon = NULL;
HBITMAP hBackground = NULL;
HBITMAP hBackground_Selected = NULL;
BITMAP bmpBackground;
BITMAP bmpBackground_Selected;
HREGNOTIFY hRegNotify_Normal;
HREGNOTIFY hRegNotify_Selected;

UINT ThemeLoader_GetStatusBarSize()
{
	DWORD dwSize = DRA::SCALEY(18);
	if (dwSize == 24)
		dwSize = 25; //HVGA fix
	return dwSize;
};

UINT ThemeLoader_GetSoftkeyBarSize()
{
	DWORD dwSize = DRA::SCALEY(34);
	if (dwSize == 51)
		dwSize = 45; //HVGA fix
	return dwSize;
};

#ifndef IMAGEHANDLER_UNDEFINE

VOID ThemeLoader_LoadNormalImage()
{
	wchar_t registryPath[512];
	if (RegistryGetString(UTASK_THEMETOOLBAR_REG_BRANCH, 
						UTASK_THEMETOOLBAR_REG_KEY, UTASK_THEMETOOLBAR_REG_NORMAL, 
						registryPath, 512) == S_OK)
	{
		hBackground = LoadTransparentImage(registryPath);
		if (hBackground)
			GetObject(hBackground, sizeof (bmpBackground), &bmpBackground);
	}
	else
		hBackground = NULL;
};

VOID ThemeLoader_UnloadNormalImage()
{
	if (hBackground)
		DeleteObject(hBackground);
	hBackground = NULL;
};

VOID ThemeLoader_LoadSelectedImage()
{
	wchar_t registryPath[512];
	if (RegistryGetString(UTASK_THEMETOOLBAR_REG_BRANCH, 
						UTASK_THEMETOOLBAR_REG_KEY, UTASK_THEMETOOLBAR_REG_SELECTED, 
						registryPath, 512) == S_OK)
	{
		hBackground_Selected = LoadTransparentImage(registryPath);
		if (hBackground_Selected)
			GetObject(hBackground_Selected, sizeof (bmpBackground_Selected), &bmpBackground_Selected);
	}
	else
	{
		hBackground_Selected = NULL;
	}
};

VOID ThemeLoader_UnloadSelectedImage()
{
	if (hBackground_Selected)
		DeleteObject(hBackground_Selected);
	hBackground_Selected = NULL;
};

VOID ThemeLoader_LoadImages()
{
	wchar_t utaskIconPath[512];
	swprintf(utaskIconPath, UTASK_TASKMANAGER_ICON_MASK, ThemeLoader_GetSoftkeyBarSize());
	hTaskManagerIcon = LoadTransparentImage(utaskIconPath);

	ThemeLoader_LoadNormalImage();
	ThemeLoader_LoadSelectedImage();
};

VOID ThemeLoader_UnloadImages()
{
	if (hTaskManagerIcon)
		DeleteObject(hTaskManagerIcon);
	hTaskManagerIcon = NULL;

	ThemeLoader_UnloadNormalImage();
	ThemeLoader_UnloadSelectedImage();
};

void ThemeLoader_NormalImageChangedNotification(HREGNOTIFY hNotify, DWORD dwUserData, const PBYTE pData, const UINT cbData)
{
	HWND MyWindow = FindWindow(UTS_WND_CLASS, NULL);
	if (MyWindow)
		PostMessage(MyWindow, WM_UTASK_NORMAL_IMAGE_CHANGED, NULL, NULL);
};

void ThemeLoader_SelectedImageChangedNotification(HREGNOTIFY hNotify, DWORD dwUserData, const PBYTE pData, const UINT cbData)
{
	HWND MyWindow = FindWindow(UTS_WND_CLASS, NULL);
	if (MyWindow)
		PostMessage(MyWindow, WM_UTASK_SELECTED_IMAGE_CHANGED, NULL, NULL);
};

VOID ThemeLoader_Initialize()
{
	ImageFactory_Initialize();
	ThemeLoader_LoadImages();

	if (hRegNotify_Normal == NULL)
	{
		RegistryNotifyCallback(UTASK_THEMETOOLBAR_REG_BRANCH,
			UTASK_THEMETOOLBAR_REG_KEY,
			UTASK_THEMETOOLBAR_REG_NORMAL,
			ThemeLoader_NormalImageChangedNotification,
			0,
			0,
			&hRegNotify_Normal);
	}
	if (hRegNotify_Selected == NULL)
	{
		RegistryNotifyCallback(UTASK_THEMETOOLBAR_REG_BRANCH,
			UTASK_THEMETOOLBAR_REG_KEY,
			UTASK_THEMETOOLBAR_REG_NORMAL,
			ThemeLoader_SelectedImageChangedNotification,
			0,
			0,
			&hRegNotify_Selected);	
	}
};


VOID ThemeLoader_Deinitialize()
{
	ThemeLoader_UnloadImages();
	ImageFactory_Deinitialize();

	if (hRegNotify_Normal != NULL)
		RegistryCloseNotification(hRegNotify_Normal);
	if (hRegNotify_Selected != NULL)
		RegistryCloseNotification(hRegNotify_Selected);

	hRegNotify_Normal = NULL;
	hRegNotify_Selected = NULL;
};

#endif
