#include "stdafx.h"
#include "StringUtils.h"

VOID ZeroString(wchar_t *string, int size)
{
	for (int x = 0; x < size; x++)
		string[x] = L'\0';
};