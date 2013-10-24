/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  InfiniteLoops.h:
  -infinite loop detector functions
*/
#ifndef INFINITELOOPS_H
#define INFINITELOOPS_H

// constant definitions
	#define propLoopInfo	L"{db4a3f89-de68-4a02-a8ff-d012eee02178}"

// structures
	typedef struct
	{
		RECT	rect;
		int		loopsCount;
		int		timeStamp;
		BOOL	processingDisabled;
	}LOOPINFO;

// function declarations
	BOOL DetectInfiniteLoop(HWND hWnd, int Y, int cy);
	BOOL KillLoopInfo(HWND hWnd);

#endif
