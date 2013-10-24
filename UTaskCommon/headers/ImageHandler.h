/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  ImageHandler.h:
  -all imageloader related functions
*/
#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#ifndef IMAGEHANDLER_UNDEFINE
	int		ImageFactory_Initialize();
	VOID	ImageFactory_Deinitialize();
	HBITMAP	LoadTransparentImage(wchar_t *name);
#endif

#endif
