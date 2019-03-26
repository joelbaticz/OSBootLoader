/*
  - Date: 2018-02-20
  - Author: Joel
  - Purpose: Debugging definitions
*/

#ifndef __DEBUG_H
#define __DEBUG_H

/* DEFINITIONS */

#define DEBUG_CHANNEL_NONE				0	/* No specific debug channel */
#define DEBUG_CHANNEL_UI				1
#define DEBUG_CHANNEL_MEMORY			2
#define DEBUG_CHANNEL_FILESYSTEM		3
#define DEBUG_CHANNEL_DISK				4
#define DEBUG_CHANNEL_CACHE				5

#define DEBUG_CHANNELS_COUNT			6
#define DEBUG_CHANNEL_DEFAULT			DEBUG_CHANNEL_NONE


#define DEBUG_LEVEL_ERROR				1
#define DEBUG_LEVEL_WARNING				2
#define DEBUG_LEVEL_TRACE				4

#define DEBUG_PORT_SCREEN				1
#define DEBUG_PORT_SERIAL				2
#define DEBUG_PORT_BOSCH				4

#define DEBUG_PORT_DEFAULT				DEBUG_PORT_SCREEN

#define ERROR(Format, ...)				DebugPrintfWithAdditionalInfo(DEBUG_CHANNEL_DEFAULT, DEBUG_LEVEL_ERROR, __FILE__, __LINE__, Format, ##__VA_ARGS__)
#define WARNING(Format, ...)			DebugPrintfWithAdditionalInfo(DEBUG_CHANNEL_DEFAULT, DEBUG_LEVEL_WARNING, __FILE__, __LINE__, Format, ##__VA_ARGS__)
#define TRACE(Format, ...)				DebugPrintfWithAdditionalInfo(DEBUG_CHANNEL_DEFAULT, DEBUG_LEVEL_TRACE, __FILE__, __LINE__, Format, ##__VA_ARGS__)

#define ERROR_WITH_CHANNEL(DebugChannel, Format, ...)	DebugPrintfWithAdditionalInfo(DebugChannel, DEBUG_LEVEL_ERROR, __FILE__, __LINE__, Format, ##__VA_ARGS__)
#define WARNING_WITH_CHANNEL(DebugChannel, Format, ...)	DebugPrintfWithAdditionalInfo(DebugChannel, DEBUG_LEVEL_WARNING, __FILE__, __LINE__, Format, ##__VA_ARGS__)
#define TRACE_WITH_CHANNEL(DebugChannel, Format, ...)	DebugPrintfWithAdditionalInfo(DebugChannel, DEBUG_LEVEL_TRACE, __FILE__, __LINE__, Format, ##__VA_ARGS__)

#define PAUSE							DebugPause()
#define HALT							DebugHalt()

#define NOT_IMPLEMENTED					DebugPrintf("WARNING: [%s : %d] %s is not implemented!\n", __FILE__, __LINE__, __FUNCTION__); //DebugHalt()

/* FUNCTIONS */
VOID DebugInit(BOOL ProcessIniFileSettings                                                           );
VOID DebugPrintf(const char *Format, ...);
VOID DebugPrintfWithAdditionalInfo(UINT32 DebugChannel, UINT32 DebugLevel, const char *File, UINT32 Line, const char *Format, ...);
VOID DebugPause();
VOID DebugHalt();

/*
[done] init debug
[done] set default debug channel
[done] unimplemented
[done] have DebugChannels
[done] set debug channels
[done] Implement DebugPrint

different functions for different debug levels (DEBUG_TRACE, DEBUG_TRACE_WITH_CHANNEL)
breakpoint?
dumpbuffer?
bugcheck (print and halt ++ with message)
set up ports (bosch + serial), baudrate, irq in C file
if not maininit get stuff from commandline
if maininit get stuff from ini file
Init serial port. If fails remove it from actual used ports.
Add debug channel level, 
msgboxprint
do all this if DEBUG_LEVEL_ALL set, otherwise debugprint should return 0

*/

#endif /* __DEBUG_H */