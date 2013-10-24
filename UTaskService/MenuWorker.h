/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  MenuWorker.h:
  -all menu_worker related structures and definitions
*/
#ifndef MENUWORKER_H
#define MENUWORKER_H

// structures, types and enumerations
	typedef unsigned int Task;
	#define TASK_SHORT					0x00000000
	#define TASK_LONG					0x00000001
	#define TASK_LKEY					0x00000002
	#define TASK_RKEY					0x00000004
	#define TASK_HOME					0x00000008

	enum Action {
		ACTION_NOACTION = 1,
		ACTION_EXECUTE,
		ACTION_CLOSE,
		ACTION_MINIMIZE,
		ACTION_STARTMENU
	};

	typedef struct
	{
		HWND	ParentWindow;
		HWND	MenuWorker;
		Task	task;
		Action	ActionID;
		LPWSTR	fPath;
		LPWSTR	fArguments;
		DWORD	bVibraIndication;
		DWORD	uVibraTime;
	}PRECONFIGURED_COMMAND;

	typedef unsigned int PROCESSRESULT;

	enum ProcessResult {
		PROCESSRESULT_STOPEXECUTION	= 1,
		PROCESSRESULT_DOSTANDARD,
		PROCESSRESULT_DONTCARE,
		PROCESSRESULT_UNKNOWN=-1
	};

	enum Command {
		COMMAND_CLOSEKEY = 0x0000000D,
		COMMAND_WINKEY = 0x0000000E
	};

// functions declarations
	LRESULT MenuWorkerWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT ToolbarWindow32WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif