/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  GlobalSettings.h:
  -main settings
  -settings cache functions' definitions
*/
#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

// variables declarations
	extern DWORD settingHoldAnimation;
	extern DWORD settingHomeIcon;
	extern DWORD settingEnhanceToolbarWindows;
	extern DWORD settingHookTaskBar;
	extern DWORD systemIsHardwareDoneKey;
	extern DWORD systemLayeredWindows;

// functions declarations
	VOID	GlobalSettings_Read();
	VOID	GlobalSettings_Read(BOOL updateTheme);
	VOID	GlobalSettings_Clear();
	VOID	GlobalSettings_Clear(BOOL clearTheme);
	VOID	GetLocalizedString(wchar_t *text, wchar_t *name, DWORD locale);
	DWORD	GetCurrentLanguage();

#endif
