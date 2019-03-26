/*
  - Date: 2018-03-10
  - Author: Joel
  - Purpose: Machine and Arch init definitions
*/

/* INCLUDES */
#include <kldr.h>
/* We don't need to specify mem.h here, if mem.h is before machine.h in the kldr.h */
//#include <mem.h>

typedef struct _DATETIME
{
	UINT16 Year;
	UINT8 Month;
	UINT8 Day;
	
	UINT8 Hour;
	UINT8 Minute;
	UINT8 Second;
	UINT16 MilliSecond;
} DATETIME, *PDATETIME;


/* GLOBAL DEFINITIONS */
typedef struct tagMACHINE_VTBL
{
	
	VOID		(*IoWritePortUint8)(UINT8 data);
	UINT8		(*IoReadPortUint8)();
	VOID		(*IoWritePortUint16)(UINT16 data);
	UINT16		(*IoReadPortUint16)();
	
	VOID		(*ConsolePutChar)(CHAR ch);
	VOID		(*ConsoleWaitForKeyPress)();
	CHAR		(*ConsoleGetChar)();
	UINT8		(*ConsoleDetectBestDisplayMode)();
	VOID		(*ConsoleSetDisplayMode)(UINT8 requestedDisplayMode);
	VOID		(*ConsoleShowCursor)(BOOL doShowCursor);
	VOID		(*ConsoleGetCursorPosition)(PUINT8 pX, PUINT8 pY);
	VOID		(*ConsoleSetCursorPosition)(UINT8 x, UINT8 y);
		
	VOID		(*UtilityBeep)();
	PDATETIME	(*UtilityGetTime)(); // Maybe we need a TIME.C to convert time to str
	VOID		(*UtilitySetTime)(PDATETIME pDateTime);
	VOID		(*UtilitySetStatusLed)(UINT8 ledId);
	VOID		(*UtilityGetBiosDate)();
	BOOL        (*UtilityCheckProcessorCompatibility)();
	VOID		(*UtilityDelay)(UINT32 milliSecs);
	VOID		(*UtilityPause)();
	VOID		(*UtilityHalt)();
	VOID		(*UtilityReboot)();
	
	BOOL		(*MemoryGetMemoryMap)(OUT PMEMORY_DESCRIPTOR pMemoryMap, OUT PUINT32 pMemoryMapEntryCount);
	
	
} MACHINE_VTBL, *PMACHINE_VTBL;

/* GLOBAL VARIABLES */
MACHINE_VTBL MachineVtbl;

/* GLOBAL FUNCTIONS */
BOOL MachineInit();

/*
	These functions will call the machine specific versions which are
	implemented in *io.c, *console.c, *utility.c, *disk.c files respectively
*/

#define MachineIoWritePortUint8(data)									MachineVtbl.IoWritePortUint8(data);
#define MachineIoReadPortUint8()										MachineVtbl.IoReadPortUint8();
#define MachineIoWritePortUint16(data)									MachineVtbl.IoWritePortUint16(data);
#define MachineIoReadPortUint16()										MachineVtbl.IoReadPortUint16();

#define MachineConsolePutChar(ch)										MachineVtbl.ConsolePutChar(ch)
#define MachineConsoleWaitForKeyPress()									MachineVtbl.ConsoleWaitForKeyPress()
#define MachineConsoleGetChar()											MachineVtbl.ConsoleGetChar()
#define MachineConsoleDetectBestDisplayMode()							MachineVtbl.ConsoleDetectBestDisplayMode()
#define MachineConsoleSetDisplayMode(requestedDisplayMode)				MachineVtbl.ConsoleSetDisplayMode(requestedDisplayMode)
#define MachineConsoleShowCursor(doShowCursor)							MachineVtbl.ConsoleShowCursor(doShowCursor)
#define MachineConsoleGetCursorPosition(pX, pY)							MachineVtbl.ConsoleGetCursorPosition(pX, pY)
#define MachineConsoleSetCursorPosition(x, y)							MachineVtbl.ConsoleSetCursorPosition(x, y)

#define MachineUtilityBeep()											MachineVtbl.UtilityBeep()
#define MachineUtilityGetTime()											MachineVtbl.UtilityGetTime()
#define MachineUtilitySetTime(pDateTime)								MachineVtbl.UtilitySetTime(pDateTime)
#define MachineUtilitySetStatusLed(ledId)								MachineVtbl.UtilitySetStatusLed(ledId)
#define MachineUtilityGetBiosDate()										MachineVtbl.UtilityGetBiosDate()
#define MachineUtilityCheckProcessorCompatibility()						MachineVtbl.UtilityCheckProcessorCompatibility()
#define MachineUtilityDelay(milliSecs)									MachineVtbl.UtilityDelay(milliSecs)
#define MachineUtilityPause()											MachineVtbl.UtilityPause()
#define MachineUtilityHalt()											MachineVtbl.UtilityHalt()
#define MachineUtilityReboot()											MachineVtbl.UtilityReboot()

#define MachineMemoryGetMemoryMap(pMemoryMap, pMemoryMapEntryCount)		MachineVtbl.MemoryGetMemoryMap(pMemoryMap, pMemoryMapEntryCount)

