/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  HookSettings.h:
  -settingsreader, reading mode, settings declarations. 
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include "UTask.h"

// settings' declarations
	extern volatile DWORD settingIsAutoFix;
	extern volatile DWORD settingPositionFixEnabled;
	extern volatile DWORD systemIsServiceEnabled;

	extern DWORD sizeStatusBar;
	extern DWORD sizeSoftkeyBar;

// enums
	typedef unsigned int MODE;

	enum Mode {
		MODE_READ =			0x00000001,
		MODE_DISPOSE =		0x00000002,
		MODE_INITIALIZE =	0x00000004,
		MODE_DEINITIALIZE = 0x00000008
	};

// functions declarations
		VOID SettingsReader_Start(MODE mode);
		VOID SettingsUpdater_Start();

		VOID Settings_Initialize();
		VOID Settings_Deinitialize();
		VOID Settings_Read();
		VOID Settings_Dispose();


#endif