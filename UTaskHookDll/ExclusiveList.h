/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  ExclusiveList.h:
  -positionfix's exclusivelist definitions
*/
#ifndef EXCLUSIVELIST_H
#define EXCLUSIVELIST_H

#include "List.h"
/*
// includes
	#include <vector>

// name spaces
	using namespace std;

// type definitions
	typedef vector<wchar_t*> WCHARVECTOR;


// variables declarations
	extern WCHARVECTOR *ExclusiveList_ToFix;
	extern WCHARVECTOR *ExclusiveList_NoFix;
*/
	extern List ExclusiveList_ToFix;
	extern List ExclusiveList_NoFix;
// function declarations
	VOID ExclusiveList_InitializeList();
	VOID ExclusiveList_DeinitializeList();
	BOOL IsExclusiveWindow(wchar_t *className);

#endif
