/* 
  UTask Project - Free TaskManager for Windows Mobile
  This code is provided "AS IS" without any warranties.
  (C) UltraShot

  nled_device.h:
  -vibration wrapper
*/
#ifndef NLED_DEVICE_H
#define NLED_DEVICE_H

// enumerations and types
	enum State {
		STATE_OFF,
		STATE_ON
	};

	typedef UINT NledDevice;


// functions declarations
	void Vibrate(NledDevice nledDevice, State state);
	unsigned long VibrateThread( LPVOID pParam );

#endif
