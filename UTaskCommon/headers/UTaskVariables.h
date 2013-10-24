/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot
*/
#ifndef UTASK_VARIABLES_H
#define UTASK_VARIABLES_H

	#define UTS_WND_CLASS						L"UTaskSrvWndCls"

// Window Messages valid for main window
	#define WM_UTASK_WINDOW_CREATED				WM_USER+0x10000
//	#define WM_UTASK_WINDOWPOS_CHANGED			WM_USER+0x10007					obsolete
	#define WM_UTASK_NORMAL_IMAGE_CHANGED		WM_USER+0x10004
	#define WM_UTASK_SELECTED_IMAGE_CHANGED		WM_USER+0x10005

// Window Messages valid for hooked menu workers
//	#define WM_UTASK_RESTOREDEFAULT				WM_USER+0x10001					obsolete
	#define WM_UTASK_PRIVATE_CLOSE				WM_USER+0x10002
	#define WM_UTASK_PRIVATE_MINIMIZE			WM_USER+0x10003
	#define WM_UTASK_PRIVATE_STARTMENU			WM_USER+0x10006

// Control code valid for service
	#define IOCTL_UTASK_UPDATESETTINGS			0xA00

// Global registry entries
	#define UTASK_REG_BRANCH					HKEY_CURRENT_USER
//	#define UTASK_REG_KEY						L"Software\\ultrashot\\UTask"	obsolete
	#define UTASK_REG_SETTINGS_KEY				L"Software\\ultrashot\\UTask\\Settings"
	#define UTASK_REG_TODAYWINDOWS_KEY			L"Software\\ultrashot\\UTask\\TodayWindows"
	#define UTASK_REG_EXCLUSIVELIST_KEY			L"Software\\ultrashot\\UTask\\ExclusiveList"
	#define UTASK_REG_POSFIX_FIX_KEY			L"Software\\ultrashot\\UTask\\PositionFix\\Fix"
	#define UTASK_REG_POSFIX_NOFIX_KEY			L"Software\\ultrashot\\UTask\\PositionFix\\NoFix"
	#define UTASK_REG_LOCALIZATION_KEY			L"Software\\ultrashot\\UTask\\Localization"
	#define UTASK_REG_SAVEDSTATE_KEY			L"Software\\ultrashot\\UTask\\SavedState"
//	#define UTASK_REG_UPDATEWATCH_VALUE			L"HookUpdateWatch"				obsolete

// Theme registry entries
	#define UTASK_THEMETOOLBAR_REG_BRANCH		HKEY_CURRENT_USER
	#define UTASK_THEMETOOLBAR_REG_KEY			L"Software\\Microsoft\\Today\\Toolbar"
	#define UTASK_THEMETOOLBAR_REG_NORMAL		L"ToolbarIconBubbleButtonThemeImage"
	#define UTASK_THEMETOOLBAR_REG_SELECTED		L"ToolbarIconBubbleButtonSelectedThemeImage"

// System bubble tiles registry entries
	#define UTASK_BUBBLETILES_REG_BRANCH		HKEY_LOCAL_MACHINE
	#define UTASK_BUBBLETILES_REG_KEY			L"Software\\Microsoft\\Shell\\BubbleTiles"
	#define UTASK_BUBBLETILES_REG_DONE_VALUE	L"HardwareDoneKeyEnabled"

// GWE registry entries
	#define UTASK_GWE_REG_BRANCH				HKEY_LOCAL_MACHINE
	#define UTASK_GWE_REG_KEY					L"System\\GWE"
	#define UTASK_GWE_REG_LW_VALUE				L"EnableLayeredWindows"

// Theme masks
	#define UTASK_TASKMANAGER_ICON_MASK			L"\\Windows\\utask_icon_%d.png"

// Global events
	#define UTASK_GLOBAL_HOOK_READY_EVENT		L"Global\\UTask\\HookReadyEvent"
	#define UTASK_GLOBAL_HOOKLIB_READY_EVENT	L"Global\\UTask\\HookLibraryReadyEvent"
	#define UTASK_GLOBAL_HOOK_UPDATE_EVENT		L"Global\\UTask\\HookUpdateEvent"

//	#define SWP_UTASK 0x10000000

#endif
