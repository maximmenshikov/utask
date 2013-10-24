#include "stdafx.h"

BOOL IsFileExists(wchar_t *path)
{
	HANDLE file = CreateFile(path, GENERIC_READ, 
							FILE_SHARE_READ, NULL, OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE)
		return FALSE;
	CloseHandle(file);
	return TRUE;
};
