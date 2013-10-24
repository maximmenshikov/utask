/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  EventWrapper.h:
  -a little wrapper needed to save state of event after its usage
*/
#ifndef EVENTWRAPPER_H
#define EVENTWRAPPER_H

// functions declarations
	int ReadEvent(HANDLE hEvent, DWORD dwTimeout);

// structures
	typedef enum
	{
		APISTATE_UNKNOWN,
		APISTATE_NEVER,
		APISTATE_NOT_READY,
		APISTATE_READY
	}ApiState;

// definitions
	#define GWE_API_EVENT_NAME TEXT("SYSTEM/GweApiSetReady")
	#define BOOTPHASE_EVENT_NAME TEXT("SYSTEM/BootPhase2")
	#define SHELL_API_EVENT_NAME TEXT("SYSTEM/ShellAPIReady")

#endif
