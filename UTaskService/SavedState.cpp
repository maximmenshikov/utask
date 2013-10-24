#include "stdafx.h"
#include "UTask.h"
#include "regext.h"
#include "SavedState.h"

VOID SetState(SavedState savedState)
{
	if (savedState == SAVEDSTATE_INCORRECT_OS_ERROR)
	{
		RegistrySetDWORD(HKEY_CURRENT_USER, UTASK_REG_SAVEDSTATE_KEY, L"IsOSSupported", 0);
	}
	else if (savedState == SAVEDSTATE_CORRECT_OS_DETECTED)
	{
		RegistrySetDWORD(HKEY_CURRENT_USER, UTASK_REG_SAVEDSTATE_KEY, L"IsOSSupported", 1);
	}
	else
	{
		RegistrySetDWORD(HKEY_CURRENT_USER, UTASK_REG_SAVEDSTATE_KEY, L"CurrentState", savedState);
	}
};

SavedState GetState()
{
	SavedState result = SAVEDSTATE_UNKNOWN;
	RegistryGetDWORD(HKEY_CURRENT_USER, UTASK_REG_SAVEDSTATE_KEY, L"CurrentState", (DWORD*)&result);
	return result;
};
