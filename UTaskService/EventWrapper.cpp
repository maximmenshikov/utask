#include "stdafx.h"

int ReadEvent(HANDLE hEvent, DWORD dwTimeout)
{
	if (WaitForSingleObject(hEvent, dwTimeout) == WAIT_OBJECT_0)
	{
		SetEvent(hEvent);
		return 0;
	}
	return 1;
};
