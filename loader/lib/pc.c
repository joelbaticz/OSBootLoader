/*
  - Date: 2018-03-10
  - Author: Joel
  - Purpose: Machine and Arch init implementation:
			 Based on the build script the loader chooses architecture/machine
			 specific initialization routines. MachPC and MachXBox contain
			 machine specific functions.
*/

/* INCLUDES */
#include <kldr.h>

/* FUNCTIONS */
VOID PcInit()
{
	TRACE("PcInit() called.");
	
	MachineVtbl.IoWritePortUint8 = (PVOID) PcIoWritePortUint8;
	MachineVtbl.IoReadPortUint8 = (PVOID) PcIoReadPortUint8;
	MachineVtbl.IoWritePortUint16 = (PVOID) PcIoWritePortUint16;
	MachineVtbl.IoReadPortUint16 = (PVOID) PcIoReadPortUint16;
	
	MachineVtbl.ConsolePutChar = (PVOID) PcConsolePutChar;
	MachineVtbl.ConsoleWaitForKeyPress = (PVOID) PcConsoleWaitForKeyPress;
	MachineVtbl.ConsoleGetChar = (PVOID) PcConsoleGetChar;
	MachineVtbl.ConsolePutChar = (PVOID) PcConsolePutChar;
	MachineVtbl.ConsoleDetectBestDisplayMode = (PVOID) PcConsoleDetectBestDisplayMode;
	MachineVtbl.ConsoleSetDisplayMode = (PVOID) PcConsoleSetDisplayMode;
	MachineVtbl.ConsoleShowCursor = (PVOID) PcConsoleShowCursor;
	MachineVtbl.ConsoleSetCursorPosition = (PVOID) PcConsoleSetCursorPosition;
	
	
	MachineVtbl.UtilityBeep = (PVOID) PcUtilityBeep;
	MachineVtbl.UtilityGetTime = (PVOID) PcUtilityGetTime;
	MachineVtbl.UtilitySetTime = (PVOID) PcUtilitySetTime;
	MachineVtbl.UtilitySetStatusLed = (PVOID) PcUtilitySetStatusLed;
	MachineVtbl.UtilityGetBiosDate = (PVOID) PcUtilityGetBiosDate;
	MachineVtbl.UtilityCheckProcessorCompatibility = (PVOID) PcUtilityCheckProcessorCompatibility;
	MachineVtbl.UtilityDelay = (PVOID) PcUtilityDelay;
	MachineVtbl.UtilityPause = (PVOID) PcUtilityPause;
	MachineVtbl.UtilityHalt = (PVOID) PcUtilityHalt;

	MachineVtbl.MemoryGetMemoryMap = (PVOID) PcMemoryGetMemoryMap;
	
}

