/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  ExceptionList.h:
  -all declarations related to exclusive processes' list
*/
#ifndef EXCEPTIONLIST_H
#define EXCEPTIONLIST_H

// variables declarations
	extern DWORD				Shell32ID;
	extern DWORD				CprogID;
	extern DWORD				GwesID;

// functions declarations
	BOOL ExceptionList_isInList(DWORD processID);
	VOID ExceptionList_DeinitializeList();
	VOID ExceptionList_InitializeList();

#endif
