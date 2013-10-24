#include "stdafx.h"
#include "service.h"

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hService = GetServiceHandle(L"UTS0:", NULL, 0);
	if (hService != NULL)
		DeregisterService(hService);
	RegisterService(L"UTS",0,L"\\Windows\\UTaskSrv.dll", 0);
	return 0;
};

