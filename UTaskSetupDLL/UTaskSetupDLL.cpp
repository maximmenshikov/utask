// UTaskSetupDLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "service.h"
#include "ce_setup.h"
#include "MyMessageBox.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}


UINT GetStatusBarSize()
{
	DWORD dwSize = DRA::SCALEY(18);
	if (dwSize == 24)
		dwSize = 25; //HVGA fix
	return dwSize;
};

codeINSTALL_INIT Install_Init(
    HWND        hwndParent,
    BOOL        fFirstCall,
    BOOL        fPreviouslyInstalled,
    LPCTSTR     pszInstallDir)
{
	RECT rect = {0, 0, 0, 0};
	GetWindowRect(FindWindow(L"HHTaskBar", NULL), &rect);
	
	DWORD size = rect.bottom - rect.top;

	if (size != GetStatusBarSize() && fFirstCall == TRUE)
	{
		if (MessageBox(hwndParent, L"Looks like you are trying to install uTask on unsupported OS version. It may lead to Hard-Reset. Do you want to continue?", L"uTask", MB_YESNO) == IDNO)
		{
			return codeINSTALL_INIT_CANCEL;
		}
	}

	HANDLE hService = GetServiceHandle(L"UTS0:", NULL, 0);
	if (hService != INVALID_HANDLE_VALUE)
		DeregisterService(hService);

    return codeINSTALL_INIT_CONTINUE;
};

codeINSTALL_EXIT Install_Exit(
    HWND    hwndParent,
    LPCTSTR pszInstallDir,
    WORD    cFailedDirs,
    WORD    cFailedFiles,
    WORD    cFailedRegKeys,
    WORD    cFailedRegVals,
    WORD    cFailedShortcuts)
{
	MessageBox(hwndParent, L"Installation completed. Make a Soft-Reset to start uTask", L"uTask", MB_OK);
    return codeINSTALL_EXIT_DONE;
};

codeUNINSTALL_INIT Uninstall_Init(
    HWND        hwndParent,
    LPCTSTR     pszInstallDir)
{
	HANDLE hService = GetServiceHandle(L"UTS0:", NULL, 0);
	if (hService != INVALID_HANDLE_VALUE)
		DeregisterService(hService);

    return codeUNINSTALL_INIT_CONTINUE;
};

codeUNINSTALL_EXIT Uninstall_Exit(
    HWND    hwndParent)
{

    return codeUNINSTALL_EXIT_DONE;
};
