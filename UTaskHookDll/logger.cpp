#include "stdafx.h"
#include "UTask.h"
#include "logger.h"
#include "InfiniteLoops.h"

#ifdef FEATURE_ADVANCEDLOGGING

char *FunctionName(int function)
{
	if (function == FUNCTION_CREATEWINDOW)
		return "CreateWnd";
	else if (function == FUNCTION_MOVEWINDOW)
		return "MoveWindow";
	else if (function == FUNCTION_SETWNDPOS)
		return "SetWndPos";
	else if (function == FUNCTION_DEFERWNDPOS)
		return "DeferWndPos";
	else if (function == FUNCTION_DESTROYWINDOW)
		return "DestroyWindow";
	else if (function == FUNCTION_SHOWWINDOW)
		return "ShowWindow";
	return "unknown";
};

VOID Log(int function, HWND hWnd, int y, int cy)
{
	wchar_t className[50];
	GetClassName(hWnd, className, 50);

	int retries = -1;
	int prc = 0;
	LOOPINFO *li = (LOOPINFO*)GetProp(hWnd, propLoopInfo);
	if (li)
	{
		retries = li->loopsCount;
		prc = li->processingDisabled;
	}
	FILE *f = fopen("\\log.txt", "at");
	fprintf(f, "[%d : %s : %ls] y=%d height=%d (loops = %d, %d)\n", GetTickCount(), FunctionName(function), className, y, cy, retries, prc);
	fflush(f);
	fclose(f);
};

#else

#define Log(...)

#endif
