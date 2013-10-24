//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft
// premium shared source license agreement under which you licensed
// this source code. If you did not accept the terms of the license
// agreement, you are not authorized to use this source code.
// For the terms of the license, please see the license agreement
// signed by you and Microsoft.
// THE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES OR INDEMNITIES.
//

#ifndef _GESTURE_H_
#define _GESTURE_H_

#if (_MSC_VER >= 1000)
#pragma once
#endif

#include <windows.h>

#ifdef __cplusplus
extern "C"  {
#endif

// Touch gesture command
#define WM_GESTURE                      0x0119

/*
 * Gesture flags - GESTUREINFO.dwFlags
 */
#define GF_BEGIN                        0x00000001
#define GF_INERTIA                      0x00000002
#define GF_END                          0x00000004

/*
 * Gesture IDs
 */
#define GID_BEGIN                       1
#define GID_END                         2
#define GID_PAN                         4
#define GID_SCROLL                      8
#define GID_HOLD                        9
#define GID_SELECT                      10
#define GID_DOUBLESELECT                11
#define GID_LAST                        11

// The maximum gesture ID value that can be assigned
// to registered gestures
#define GID_MAX                         63

/* Macro to determine if the Gesture ID is for a builtin gesture, excluding
 * GID_BEGIN and GID_END
 */
#define GID_IS_BUILTIN_GESTURE(x)   (((x)>GID_END)&&((x)<=GID_LAST))

/*
 * Gesture argument helpers
 *   - Angle should be a double in the range of -2pi to +2pi
 *   - Argument should be an unsigned 16-bit value
 */
#define GID_ROTATE_ANGLE_TO_ARGUMENT(_arg_)     ((USHORT)((((_arg_) + 2.0 * 3.14159265) / (4.0 * 3.14159265)) * 65536.0))
#define GID_ROTATE_ANGLE_FROM_ARGUMENT(_arg_)   ((((double)(_arg_) / 65536.0) * 4.0 * 3.14159265) - 2.0 * 3.14159265)

// Scroll directions
#define ARG_SCROLL_NONE                 0
#define ARG_SCROLL_DOWN                 1
#define ARG_SCROLL_LEFT                 2
#define ARG_SCROLL_UP                   3
#define ARG_SCROLL_RIGHT                4

// Macros to extract scroll angles and direction
#define GID_SCROLL_ANGLE(x)              ((LONG)(HIWORD(((ULONGLONG)(x)) >> 32) & 0xFFF0))
#define GID_SCROLL_DIRECTION(x)          ((LONG)(HIWORD(((ULONGLONG)(x)) >> 32) & 0x000F))
#define GID_SCROLL_VELOCITY(x)           ((LONG)((short)(LOWORD(((ULONGLONG)(x)) >> 32))))

// @CESYSGEN IF GWES_MSGQUE

/* Gesture info structure.
 */
typedef struct tagGESTUREINFO
{
    UINT cbSize;                /* Initialised to structure size */
    DWORD dwFlags;              /* Gesture Flags */
    DWORD dwID;                 /* Gesture ID */
    HWND hwndTarget;            /* HWND of target window */
    POINTS ptsLocation;         /* Coordinates of start of gesture */
    DWORD dwInstanceID;         /* Gesture Instance ID */
    DWORD dwSequenceID;         /* Gesture Sequence ID */
    ULONGLONG ullArguments;     /* Arguments specific to gesture */
    UINT cbExtraArguments;      /* Size of extra arguments in bytes */
} GESTUREINFO, * PGESTUREINFO;

typedef struct tagGESTUREMETRICS {
    UINT   cbSize; 
    DWORD  dwID;
    DWORD  dwTimeout; 
    DWORD  dwDistanceTolerance; 
    DWORD  dwAngularTolerance;
    DWORD  dwExtraInfo;
} GESTUREMETRICS, *LPGESTUREMETRICS;

/* Gesture Information Handle
*/
DECLARE_HANDLE(HGESTUREINFO);

WINUSERAPI
BOOL
WINAPI
TKGetGestureInfo(
    __in HGESTUREINFO hGestureInfo,
    __out PGESTUREINFO pGestureInfo);

WINUSERAPI
BOOL
WINAPI
TKGetGestureExtraArguments(
    __in HGESTUREINFO hGestureInfo,
    __in UINT cbExtraArguments,
    __out_bcount(cbExtraArguments) PBYTE pExtraArguments);


WINUSERAPI
BOOL 
WINAPI
TKGetGestureMetrics(
    __inout LPGESTUREMETRICS lpGestureMetricsInfo);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _GESTURE_H_ */
