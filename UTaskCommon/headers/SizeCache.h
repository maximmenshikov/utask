/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  SizeCache.h:
  -provides an access to size constants for every resolution
*/
#ifndef SIZECACHE_H
#define SIZECACHE_H

// definitions
	#define PREDEFINED_SIZES_COUNT	8
	#define SIZE_NOT_DEFINED -5

// enumerations
	enum Size
	{
		SIZE_STATUSBAR_OLD			=	0x00000000,
		SIZE_SOFTKEYBAR_OLD			=	0x00000000,
		SIZE_STATUSBAR_NEW			=	0x00000001,
		SIZE_SOFTKEYBAR_NEW			=	0x00000002,
		SIZE_INCORRECT_POS1			=	0x00000003,
		SIZE_INCORRECT_SIZE1		=	0x00000004,
		SIZE_ICON_POSITION_OFFSET	=	0x00000005,
		SIZE_TASKBAR_CLOCK_WIDTH	=	0x00000006,
		SIZE_INCORRECT_POS2			=	0x00000007,
	};

// functions definitions
	DWORD	GetSizeCacheItem(Size size);
	VOID	InitializeSizeCache();

#endif
