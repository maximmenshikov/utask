#include "stdafx.h"
#include "nled.h"
#include "nled_device.h"

extern "C" 
{
	BOOL WINAPI NLedGetDeviceInfo( UINT nInfoId, void *pOutput );
	BOOL WINAPI NLedSetDevice( UINT nDeviceId, void *pInput );
};

NledDevice GetVibratorLedNum()
{ 
    NLED_COUNT_INFO countInfo;  
    NLED_SUPPORTS_INFO supportInfo;  
	
	UINT devicesCount = 0;
    if(NLedGetDeviceInfo(0, (PVOID) &countInfo))  
        devicesCount = countInfo.cLeds;   

    for (UINT i = devicesCount - 1; i >= 0; i--) 
    {  
        supportInfo.LedNum = i;   
        NLedGetDeviceInfo(1, &supportInfo);  
        if (supportInfo.lCycleAdjust == -1)  
			return i;
    } 
    return -1;
};

void Vibrate(NledDevice nledDevice, State state)
{
	NLED_SETTINGS_INFO settings;
	settings.LedNum = nledDevice;
	settings.OffOnBlink = state;
	NLedSetDevice(NLED_SETTINGS_INFO_ID, &settings);
};

unsigned long VibrateThread( LPVOID pParam )
{
	NledDevice vibratorNum = GetVibratorLedNum();
	
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	if (vibratorNum != -1)
	{
		Vibrate(vibratorNum, STATE_ON);
		Sleep((int) pParam);
		Vibrate(vibratorNum, STATE_OFF);
	}
	return 0;
};
