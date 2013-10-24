#include "stdafx.h"
#include "UTask.h"
#include "MenuWorker.h"
#include "ActionConfiguration.h"

// Keys have their own civilic names
wchar_t *keys[]={	L"LKey",
					L"RKey",
					L"HomeKey",
					L"LKeyLong",
					L"RKeyLong",
					L"HomeKeyLong",
					L"Unknown"};

wchar_t *GetKeyName(int key)
{
	int indexCorrection = 0;
	if (key&TASK_LONG)
	{
		indexCorrection = 3;
		key=((key >> 1) << 1);
	}
	switch (key)
	{
	case TASK_LKEY :
		return keys[indexCorrection + 0];
	case TASK_RKEY :
		return keys[indexCorrection + 1];
	case TASK_HOME :
		return keys[indexCorrection + 2];
	default :
		return keys[6];
	}
};

// Cache for commands
PRECONFIGURED_COMMAND cachedcommands[6];

VOID UpdateActionConfiguration(PRECONFIGURED_COMMAND *command)
{
	int index = -1;
	switch (command->task)
	{
	case (TASK_LKEY) :
		index = 0;
		break;
	case (TASK_LKEY|TASK_LONG) :
		index = 1;
		break;
	case (TASK_RKEY) :
		index = 2;
		break;
	case (TASK_RKEY|TASK_LONG) :
		index = 3;
		break;
	case (TASK_HOME) :
		index = 4;
		break;
	case (TASK_HOME|TASK_LONG) :
		index = 5;
		break;
	default :
		index = -1;
		break;
	}
	if (index != -1)
	{
		PRECONFIGURED_COMMAND *cache = &cachedcommands[index];
		command->ActionID = cache->ActionID;
		command->fPath = cache->fPath;
		command->fArguments = cache->fArguments;
		command->bVibraIndication = cache->bVibraIndication;
		command->uVibraTime = cache->uVibraTime;
	}
};

VOID ReadActionConfiguration(PRECONFIGURED_COMMAND *command)
{
	HKEY hKey;
	if( RegOpenKeyEx( UTASK_REG_BRANCH, UTASK_REG_SETTINGS_KEY, 0, 
		KEY_READ, &hKey) == ERROR_SUCCESS )
	{
		DWORD typeDWORD = REG_DWORD;
		DWORD typeRegSz = REG_SZ;

		// Setting action name
		wchar_t *action = GetKeyName(command->task);

		// Copying actionID from registry
		wchar_t key[128];
		swprintf(key, L"%lsActionID", action);
		DWORD bufferSize = 4;
		RegQueryValueEx(hKey, key, NULL, &typeDWORD, 
						(LPBYTE)&command->ActionID, &bufferSize);

		if (command->ActionID == ACTION_EXECUTE)
		{
			// Copying file path from registry
			swprintf(key, L"%lsPath", action);
			wchar_t buffer[512];
			bufferSize = 512;
			if (RegQueryValueEx(hKey, key, NULL, &typeRegSz, 
								(LPBYTE)buffer, &bufferSize) == S_OK)
			{
				command->fPath = new wchar_t[wcslen(buffer) + 1];
				if (command->fPath)
					wcscpy(command->fPath, buffer);
			}

			// Copying file arguments from registry
			swprintf(key, L"%lsArgs", action);
			bufferSize = 512;
			if (RegQueryValueEx(hKey, key, NULL, &typeRegSz, 
								(LPBYTE)buffer, &bufferSize) == S_OK)
			{
				command->fArguments = new wchar_t[wcslen(buffer) + 1];
				if (command->fArguments)
					wcscpy(command->fArguments, buffer);
			}

		}

		// Getting vibration settings from registry
		bufferSize = 4;
		swprintf(key, L"%lsVibra", action);
		RegQueryValueEx(hKey, key, NULL, &typeDWORD, 
						(LPBYTE)&command->bVibraIndication, &bufferSize);

		bufferSize = 4;
		swprintf(key, L"%lsVibraTime", action);
		RegQueryValueEx(hKey, key, NULL, &typeDWORD, 
						(LPBYTE)&command->uVibraTime, &bufferSize);

		// Closing open registry key
		RegCloseKey(hKey);
	}
};

// Clearing certain command
VOID PreconfiguredCommand_Clear(PRECONFIGURED_COMMAND *command)
{
	if (command->fPath)
		delete(command->fPath);
	if (command->fArguments)
		delete(command->fArguments);
	command->fPath = NULL;
	command->fArguments = NULL;
};

// Clearing fPath and fArguments - the only pointers in structure that 
// may lead to memory leaks
VOID ActionCache_Clear()
{
	PRECONFIGURED_COMMAND *command = &cachedcommands[0];
	PreconfiguredCommand_Clear(command);

	command = &cachedcommands[1];
	PreconfiguredCommand_Clear(command);

	command = &cachedcommands[2];
	PreconfiguredCommand_Clear(command);

	command = &cachedcommands[3];
	PreconfiguredCommand_Clear(command);

	command = &cachedcommands[4];
	PreconfiguredCommand_Clear(command);

	command = &cachedcommands[5];
	PreconfiguredCommand_Clear(command);
};

// Reading actions from registry and putting it into the cache
VOID ActionCache_Update()
{
	ActionCache_Clear();

	PRECONFIGURED_COMMAND *command = &cachedcommands[0];
	command->task = TASK_LKEY;
	ReadActionConfiguration(command);

	command = &cachedcommands[1];
	command->task = TASK_LKEY|TASK_LONG;
	ReadActionConfiguration(command);

	command = &cachedcommands[2];
	command->task = TASK_RKEY;
	ReadActionConfiguration(command);

	command = &cachedcommands[3];
	command->task = TASK_RKEY|TASK_LONG;
	ReadActionConfiguration(command);

	command = &cachedcommands[4];
	command->task = TASK_HOME;
	ReadActionConfiguration(command);

	command = &cachedcommands[5];
	command->task = TASK_HOME|TASK_LONG;
	ReadActionConfiguration(command);

};

