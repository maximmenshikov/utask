#include "stdafx.h"
#include "UTask.h"
#include "ExclusiveList.h"
#include "Settings.h"
#include "PositionFix.h"
#include "StringUtils.h"
#include "DoubleFix.h"

#include "..\UTaskCommon\headers\SizeCache.h"

#ifdef FEATURE_POSITIONFIX

inline BOOL CheckPosition(int nY)
{
	if (nY == GetSizeCacheItem(SIZE_STATUSBAR_OLD))
	{
		return TRUE;
	}
	else
	{
		DWORD incorrectPos1 = GetSizeCacheItem(SIZE_INCORRECT_POS1);
		if ((incorrectPos1 != SIZE_NOT_DEFINED) && (nY == incorrectPos1))
			return TRUE;

		DWORD incorrectPos2 = GetSizeCacheItem(SIZE_INCORRECT_POS2);
		if ((incorrectPos2 != SIZE_NOT_DEFINED) && (nY == incorrectPos2))
			return TRUE;
	}
	return FALSE;
};

inline DWORD CheckSize(int nCy, int displayHeight)
{
	DWORD statusBarSize = GetSizeCacheItem(SIZE_STATUSBAR_NEW);
	DWORD statusBarOldSize = GetSizeCacheItem(SIZE_STATUSBAR_OLD);

	if ((nCy == (displayHeight - (statusBarSize * 2))) ||
		(nCy == (displayHeight - statusBarSize - statusBarOldSize)))
	{
		return CHECKRESULT_NORMALSIZE;
	}
	else if ((nCy == (displayHeight - statusBarSize)) ||
			 (nCy == (displayHeight - statusBarOldSize)))
	{
		return CHECKRESULT_FULLSCREEN;
	}
	else
	{
		DWORD incorrectSize1 = GetSizeCacheItem(SIZE_INCORRECT_SIZE1);
		if ((incorrectSize1 != SIZE_NOT_DEFINED) && (nCy == incorrectSize1))
		{
			return CHECKRESULT_NORMALSIZE;
		}

	}
	return CHECKRESULT_FALSE;
};

inline BOOL CheckLowestPosition(int lowestPos, int displayHeight)
{
	if ((lowestPos == (displayHeight - GetSizeCacheItem(SIZE_STATUSBAR_OLD))) ||
		(lowestPos == (displayHeight - GetSizeCacheItem(SIZE_STATUSBAR_NEW))))
		return TRUE;
	return FALSE;
};

BOOL FixPos(int *Y)
{
	int nY = *Y;
	if (CheckPosition(nY) == TRUE)
	{
		*Y = sizeStatusBar;
		return TRUE;
	}
	return FALSE;
};

BOOL FixSize(int *cy, int displayHeight)
{
	int nCy = *cy;
	int checkResult = CheckSize(nCy, displayHeight);
	if (checkResult == CHECKRESULT_NORMALSIZE)
	{
		*cy = displayHeight - sizeSoftkeyBar - sizeStatusBar;
		return TRUE;
	}
	else if (checkResult == CHECKRESULT_FULLSCREEN)
	{
		*cy = displayHeight - sizeStatusBar;
		return TRUE;
	}
	return FALSE;
};

BOOL ShouldBeProcessed(wchar_t *className)
{
	BOOL isExclusive = IsExclusiveWindow(className);
	
	if ((isExclusive == FALSE && settingIsAutoFix) || 
		(isExclusive == TRUE && settingIsAutoFix == 0))
		return TRUE;
	return FALSE;
};

BOOL IsSipButtonVisible()
{
	return IsWindowVisible(FindWindow(L"MS_SIPBUTTON", NULL));
};

extern t_SetWindowPos OldSetWndPos;

BOOL IsDialogWindow(wchar_t *className)
{
	if (className)
		return wcscmp(className, L"Dialog") == 0 ? TRUE : FALSE;
	return FALSE;
};

BOOL IsSipWindowVisible()
{
	HWND hWnd = FindWindow(L"MS_SIPBUTTON", NULL);
	if (hWnd && IsWindowVisible(hWnd) == TRUE)
		return TRUE;
	return FALSE;
};

BOOL GetSipInfo(SIPINFO * si)
{
	// Setup the SIPINFO structure.
	memset(si, 0, sizeof(SIPINFO));
	si->cbSize = sizeof(SIPINFO);
	return SHSipInfo(SPI_GETSIPINFO, 0, si, 0);
}

// asynchronous position fix improves stability
ULONG AsyncFixThread( LPVOID pParam )
{
	HWND hWnd = (HWND) pParam;
	
	// little delay is needed to guarantee that window is ready
	for (int x = 0; x < 20; x++)
	{
		Sleep(100);
		if (IsWindow(hWnd) == FALSE)
			return 0;
		if (IsWindowVisible(hWnd) == TRUE)
			break;
	}

	Sleep(100);

	__try
	{
		if (IsWindow(hWnd) == TRUE)
		{
			if ((GetParent(hWnd) == NULL || ((GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD) == NULL)) && IsWindowVisible(hWnd) == TRUE)
			{
				wchar_t className[50];
				ZeroString(className, 50);
				GetClassName(hWnd, className, 50);

				if (wcslen(className))
				{

					RECT rect = {0, 0, 0, 0};
					GetWindowRect(hWnd, &rect);
					int newY = rect.top;
					int newHeight = rect.bottom - rect.top;
					

					if (FixPosition(hWnd, className, 0, &newY, &newHeight) == TRUE)
					{
						SetWindowPos(hWnd, NULL, rect.left, newY, rect.right - rect.left, newHeight, SWP_NOZORDER);
					}

					wchar_t windowName[50];
					ZeroString(windowName, 50);
					GetWindowText(hWnd, windowName, 50);

					DWORD isDoubleFix = IsDoubleFixWindow(hWnd);
					if (isDoubleFix && (IsSipWindowVisible() == TRUE || isDoubleFix == 2) && ShouldBeProcessed(className) == TRUE)
					{
						//RECT rect = {0, 0, 0, 0};
						//GetWindowRect(hWnd, &rect);
						//SetWindowPos(hWnd, NULL, rect.left, rect.top, 
						//	rect.right - rect.left, rect.bottom - rect.top, 
						//	SWP_NOZORDER);
						SIPINFO si;
						GetSipInfo(&si);
						SHSipInfo(SPI_SETSIPINFO, 0, &si, 0);
					}
				}
			}
		}
	}
	__except (GetExceptionCode())
	{
	}
	return 0;
};

BOOL isHalfSize(DWORD displayHeight)
{
	DWORD sizeStatusBar = GetSizeCacheItem(SIZE_STATUSBAR_NEW);

	if (sizeStatusBar == 18) //Q(W)VGA
	{
		if (displayHeight == 120 /*from 240*/ || 
			displayHeight == 160 /*from 320*/ || 
			displayHeight == 200 /*from 400, QVGA*/)
			return TRUE;
	}
	else if (sizeStatusBar == 25) // HVGA
	{
		if (displayHeight == 160 /*from 320*/ || 
			displayHeight == 240 /*from 480*/)
			return TRUE;
	}
	else if (sizeStatusBar == 36) // (W)VGA
	{
		if (displayHeight == 240 /*from 480*/ || 
			displayHeight == 320 /*from 640*/ ||
			displayHeight == 400 /*from 800, WVGA*/)
			return TRUE;
	}
	return FALSE;
};

BOOL IsDialogWindow(wchar_t *className);

BOOL FixPosition(HWND hWnd, wchar_t *className, int flags, int *Y, int *cy)
{
	// as we have full control over position and height, 
	// we try to detect correct position and size
	BOOL result = FALSE;
	__try
	{
		if (settingPositionFixEnabled == TRUE)
		{
			if (IsWindow(hWnd) == TRUE && 
			   (GetParent(hWnd) == NULL || 
			   ((GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD) == NULL)))
			{
				if (ShouldBeProcessed(className))
				{
					int displayHeight = GetSystemMetrics(SM_CYSCREEN);

					// some applications aren't high-res aware
					// example: pocketmusic installer.
					BOOL halfSize = isHalfSize(displayHeight);

					if (halfSize == TRUE)
					{
						displayHeight = displayHeight << 1;
						*Y = *Y << 1;	
						*cy = *cy << 1;
					}

					int oldY = *Y, oldHeight = *cy;

					if (wcscmp(className, L"SipWndClass") == 0)
					{
						// special position fix optimized for SIP
						if (CheckLowestPosition(*Y + *cy, displayHeight) == TRUE)
						{
							int currentPosition = *Y + *cy;
							int neededPosition = displayHeight - sizeSoftkeyBar;
							int difference = currentPosition - neededPosition;
							*Y = *Y - difference;
							result = TRUE;
						}
					}
					else
					{
						// fixing position if needed
						if ((flags & SWP_NOMOVE) == NULL)
						{
							if (FixPos(Y) == TRUE)
								result = TRUE;
						}

						// fixing size if needed
						if ((flags & SWP_NOSIZE) == NULL)
						{
							if (FixSize(cy, displayHeight) == TRUE)
								result = TRUE;
						}
					}

					if (halfSize == TRUE)
					{
						*Y = *Y >> 1;
						*cy = *cy >> 1;
					}
				}
			}
		}
	}
	__except (GetExceptionCode())
	{
	}
	return result;
};


#endif
