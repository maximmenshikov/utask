/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  InjectDLL.h:
  -header for injectdll module used to inject libraries to system processes
*/
#ifndef INJECTDLL_H
#define INJECTDLL_H

int InjectDLL(HANDLE hProc, wchar_t *LibraryName);

#endif