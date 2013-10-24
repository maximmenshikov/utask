#include "stdafx.h"
#include "InfiniteLoops.h"

/* 	Function: DetectInfiniteLoop

	Description: Some applications behave incorrectly changing their size to original 
	after receiving WM_WINDOWPOSCHANGED message. If that happens, 
	uTask can be caught in an infinite loop.

	Returned value: TRUE if that's infinite loop, 
					FALSE if not.
*/

BOOL DetectInfiniteLoop(HWND hWnd, int Y, int cy)
{
	__try 
	{
		int currentTicks = GetTickCount();
		LOOPINFO *li = (LOOPINFO*)GetProp(hWnd, propLoopInfo);
		if (li)
		{
			if (Y == li->rect.top && cy == (li->rect.bottom - li->rect.top))	
			{
				if (li->processingDisabled == FALSE)
				{
					if ((currentTicks - li->timeStamp) < 400)
					{
						li->timeStamp = currentTicks;
						if (li->loopsCount >= 20)
						{
							li->processingDisabled = TRUE;
							return TRUE;
						}
						else
						{
							li->loopsCount++;
						}
					}
				}
				else
					return TRUE;
			}
			else
			{
				li->rect.top = Y;
				li->rect.bottom = Y + cy;
				li->loopsCount = 1;
				li->timeStamp = currentTicks;
				li->processingDisabled = FALSE;
			}
		}
		else
		{
			LOOPINFO *loopInfo = new LOOPINFO;
			if (loopInfo)
			{
				loopInfo->rect.top = Y;
				loopInfo->rect.bottom = Y + cy;
				loopInfo->loopsCount = 1;
				loopInfo->timeStamp = currentTicks;
				loopInfo->processingDisabled = FALSE;
				SetProp(hWnd, propLoopInfo, (HANDLE)loopInfo);
			}
		}
	}
	__except (GetExceptionCode())
	{
	}
	return FALSE;
};

BOOL KillLoopInfo(HWND hWnd)
{
	if (IsWindow(hWnd))
	{
		__try
		{
			LOOPINFO *li = (LOOPINFO*)RemoveProp(hWnd, propLoopInfo);
			if (li)
			{
				delete(li);
				return TRUE;
			}
		}
		__except (GetExceptionCode())
		{
		}
	}
	return FALSE;
};
