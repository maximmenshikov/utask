/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  ThemeLoader.h:
  -loaders for theme images
  -handles to images' bitmaps
*/
#ifndef THEMELOADER_H
#define THEMELOADER_H

// variables declarations
	extern HBITMAP hBackground;
	extern HBITMAP hBackground_Selected;
	extern HBITMAP hTaskManagerIcon;

	extern BITMAP bmpBackground;
	extern BITMAP bmpBackground_Selected;

// functions declarations
	VOID ThemeLoader_Initialize();
	VOID ThemeLoader_Deinitialize();

	VOID ThemeLoader_LoadNormalImage();
	VOID ThemeLoader_UnloadNormalImage();

	VOID ThemeLoader_LoadSelectedImage();
	VOID ThemeLoader_UnloadSelectedImage();

	VOID ThemeLoader_LoadImages();
	VOID ThemeLoader_UnloadImages();

	UINT ThemeLoader_GetSoftkeyBarSize();
	UINT ThemeLoader_GetStatusBarSize();

#endif
