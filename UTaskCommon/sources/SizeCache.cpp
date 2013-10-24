#include "stdafx.h"

#include "..\headers\ThemeLoader.h"
#include "..\headers\SizeCache.h"

BOOL	isInitialized = FALSE;
DWORD	sizes[PREDEFINED_SIZES_COUNT];

DWORD	GetSizeCacheItem(Size size)
{
	if (isInitialized == FALSE)
		InitializeSizeCache();
	if (size >= PREDEFINED_SIZES_COUNT)
		return SIZE_NOT_DEFINED;
	return sizes[size];
};

VOID	SetSizeCacheItem(Size size, DWORD value)
{
	if (size < PREDEFINED_SIZES_COUNT)
		sizes[size] = value;
};

VOID	InitializeSizeCache()
{
	DWORD statusBarNewSize = ThemeLoader_GetStatusBarSize();
	SetSizeCacheItem(SIZE_STATUSBAR_NEW, statusBarNewSize);
	SetSizeCacheItem(SIZE_SOFTKEYBAR_NEW, ThemeLoader_GetSoftkeyBarSize());

	if (statusBarNewSize == 25)							// HVGA
	{
		SetSizeCacheItem(SIZE_STATUSBAR_OLD, 35);
		SetSizeCacheItem(SIZE_INCORRECT_POS1, SIZE_NOT_DEFINED);
		SetSizeCacheItem(SIZE_ICON_POSITION_OFFSET, 52);
		SetSizeCacheItem(SIZE_TASKBAR_CLOCK_WIDTH, 50);
	}
	else												// all other resolutions
	{
		SetSizeCacheItem(SIZE_STATUSBAR_OLD, DRA::SCALEY(26)); 
		SetSizeCacheItem(SIZE_INCORRECT_POS1, DRA::SCALEY(13));
		SetSizeCacheItem(SIZE_ICON_POSITION_OFFSET, DRA::SCALEX(39));
		SetSizeCacheItem(SIZE_TASKBAR_CLOCK_WIDTH, DRA::SCALEX(35));
	}

	if (statusBarNewSize == 36)
	{
		SetSizeCacheItem(SIZE_INCORRECT_SIZE1, 731);	// such an unusual size was detected in htc phonecanvas (SaveToContact window)
		SetSizeCacheItem(SIZE_INCORRECT_POS2, 51);
	}
	else
	{
		SetSizeCacheItem(SIZE_INCORRECT_SIZE1, SIZE_NOT_DEFINED);
		SetSizeCacheItem(SIZE_INCORRECT_POS2, SIZE_NOT_DEFINED);
	}
	isInitialized = TRUE;
};
