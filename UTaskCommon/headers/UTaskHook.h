/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot
*/
#ifndef UTASK_HOOK_H
#define UTASK_HOOK_H

#include "..\..\UTask\UTaskCommon\headers\undocWM5.h"
#include "..\..\UTask\UTaskCommon\headers\kernel.h"

typedef struct _CALLBACKINFO {
    HANDLE		hProc;      /* destination process */
    FARPROC		pfn;        /* function to call in dest. process */
    PVOID		pvArg0;     /* arg0 data */
} CALLBACKINFO;
typedef CALLBACKINFO *PCALLBACKINFO;

extern "C"
{
	DWORD	PerformCallBack4(CALLBACKINFO *pcbi, ...);
	LPVOID	MapPtrToProcess(LPVOID lpv, HANDLE hProcess);
	BOOL	SetKMode(BOOL bFlag);
	DWORD	SetProcPermissions(DWORD dwPerms);
}

#define KINX_APISETS	24

#define FIRST_METHOD    0xF0010000
#define APICALL_SCALE   0x00000004
#define HANDLE_SHIFT 	0x00000008
#define METHOD_MASK		0x000000FF
#define HANDLE_MASK		0x0000003F

// 
#define CREATEWNDEXW					0xF000BBF0 //CreateWindowExW
#define SETWNDPOS						0xF000BBC8 //SetWindowPos
#define MOVEWINDOW						0xF000BAF8 //MoveWindow
#define DEFERWNDPOS						0xF000B830 //DeferWindowPos
#define DESTROYWND						0xF000BB4C //DestroyWindow
#define SHOWWINDOW						0xF000BB48 //ShowWindow
#define CREATEDIALOGINDIRECTPARAMW		0xF000BA44 //CreateDialogIndirectParamW

typedef HWND (*t_CreateWindowEx)(
	DWORD dwExStyle,
    LPCWSTR lpClassName,
    LPCWSTR lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    HWND hWndParent,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam,
	LPVOID lpUnk
);

typedef BOOL (*t_SetWindowPos)(
	HWND hWnd, 
	HWND hWndInsertAfter, 
	int X, 
	int Y, 
	int cx, 
	int cy, 
	UINT uFlags
);

typedef BOOL (*t_MoveWindow)(
	HWND hWnd,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	BOOL bRepaint
);

typedef HDWP (*t_DeferWindowPos)(
  HDWP hWinPosInfo,
  HWND hWnd,
  HWND hWndInsertAfter,
  int x,
  int y,
  int cx,
  int cy,
  UINT uFlags
);

typedef BOOL (*t_ShowWindow)(
  HWND hWnd,
  INT nCmdShow
);

typedef BOOL (*t_DestroyWindow)(
  HWND hWnd
);

typedef HWND (*t_CreateDialogIndirectParamW)( 
	HINSTANCE hInstance,
	LPCDLGTEMPLATEW lpTemplate,
	HWND hWndParent,
	DLGPROC lpDialogFunc,
	LPARAM dwInitParam,
	LPVOID unk
);

#endif
