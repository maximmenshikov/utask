/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  ActionConfiguration.h:
  -all action cache and action configuration functions definitions
*/
#ifndef ACTIONCONFIGURATION_H
#define ACTIONCONFIGURATION_H

// includes
	#include "MenuWorker.h"

// functions declarations
	VOID ActionCache_Update();
	VOID ActionCache_Clear();

	VOID UpdateActionConfiguration(PRECONFIGURED_COMMAND *);
	VOID ReadActionConfiguration(PRECONFIGURED_COMMAND *command);

#endif
