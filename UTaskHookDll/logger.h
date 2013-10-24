/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  Logger.h:
  -logger constants and functions declarations
*/
#ifndef LOGGER_H
#define LOGGER_H

// additional includes
	#include "UTask.h"

// constant definitions
	#define FUNCTION_CREATEWINDOW 0
	#define FUNCTION_MOVEWINDOW	1
	#define FUNCTION_SETWNDPOS 2
	#define FUNCTION_DEFERWNDPOS 3
	#define FUNCTION_SHOWWINDOW 4
	#define FUNCTION_DESTROYWINDOW 5

// function declarations
	#ifdef FEATURE_ADVANCEDLOGGING
		VOID Log(int function, HWND hWnd, int y, int cy);
	#else
		#define Log(...)
	#endif

#endif