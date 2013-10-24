/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  PositionFix.h:
  -position fix related functions
*/
#ifndef POSITIONFIX_H
#define POSITIONFIX_H

// includes
	#include "UTask.h"

// funcions declarations

	#ifdef FEATURE_POSITIONFIX
		ULONG AsyncFixThread( LPVOID pParam );
		inline BOOL		CheckPosition(int nY);
		inline DWORD		CheckSize(int nCy, int displayHeight);
		BOOL	IsPositionBad(HWND hWnd, int flags, int y, int cy);
		BOOL	FixPosition(HWND hWnd, wchar_t *className, int flags, int *Y, int *cy);
		int		FixPos(int *Y);
		int		FixSize(int *cy, int displayHeight);
		BOOL	ShouldBeProcessed(wchar_t *className);
	#else
		#define AsyncFixThread(...) NULL
		#define CheckPosition(...) FALSE
		#define CheckSize(...) FALSE
		#define IsPositionBad(...) FALSE
		#define FixPosition(...)
		#define FixPos(...)
		#define FixSize(...)
		#define ShouldBeProcessed(...) FALSE
	#endif

	#define CHECKRESULT_FALSE 0
	#define CHECKRESULT_NORMALSIZE 1
	#define CHECKRESULT_FULLSCREEN 2

#endif