/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  SavedState.h:
  -provides a control interface used to take a decision about user experience
*/
#ifndef SAVEDSTATE_H
#define SAVEDSTATE_H


enum SavedState
{
	SAVEDSTATE_UNKNOWN = 0,
	SAVEDSTATE_INITTHREAD_STARTED = 1,
	SAVEDSTATE_INITTHREAD_STARTED_TWICE = 2,
	SAVEDSTATE_INITTHREAD_FINISHED = 0xFFFFFFFF,
	SAVEDSTATE_INCORRECT_OS_ERROR = 0xFFFFFFFE,
	SAVEDSTATE_CORRECT_OS_DETECTED = 0xFFFFFFFD
};

VOID SetState(SavedState savedState);
SavedState GetState();

#endif
