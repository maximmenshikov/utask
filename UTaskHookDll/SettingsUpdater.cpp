#include "stdafx.h"
#include "UTask.h"
#include "Settings.h"

BOOL isUpdaterThreadStarted = FALSE;

ULONG SettingsUpdaterThread( LPVOID pParam )
{
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, UTASK_GLOBAL_HOOK_UPDATE_EVENT);
	while (true)
	{
		if (WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
			SettingsReader_Start(MODE_DISPOSE | MODE_READ);
	}
	return 0;
};

VOID SettingsUpdater_Start()
{
	if (isUpdaterThreadStarted == FALSE)
	{
		isUpdaterThreadStarted = TRUE;
		CloseHandle(CreateThread(0, 0, SettingsUpdaterThread, NULL, 0, 0));
		//CloseHandle(CreateThread(0, 0, SettingsUpdaterThread, hEvent, 0, 0));
	}
};
