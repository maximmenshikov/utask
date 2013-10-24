#include "stdafx.h"
#include "Settings.h"

volatile BOOL isOnReading = FALSE;

ULONG SettingsReaderThread( LPVOID pParam )
{
	MODE mode = (MODE)pParam;

	if (isOnReading == FALSE)
	{
		isOnReading = TRUE;

		if (mode & MODE_DEINITIALIZE)
			Settings_Deinitialize();

		if (mode & MODE_DISPOSE)
			Settings_Dispose();

		if (mode & MODE_INITIALIZE)
			Settings_Initialize();

		if (mode & MODE_READ)
			Settings_Read();
	}

	isOnReading = FALSE;
	return 0;
};

VOID SettingsReader_Start(MODE mode)
{
	CloseHandle(CreateThread(0, 0, SettingsReaderThread, (LPVOID)mode, 0, 0));
};

