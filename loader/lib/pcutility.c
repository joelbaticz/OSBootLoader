
/*
  - Date: 2018-03-18
  - Author: Joel
  - Purpose: PC Utility implementation:
			 Machine specific utility functions.
*/

/* INCLUDES */
#include <kldr.h>

/* PRIVATE DEFINITIONS */

/* PRIVATE VARIABLES */


/* PRIVATE FUNCTIONS */

/* GLOBAL FUNCTIONS */
VOID PcUtilityBeep()
{
	NOT_IMPLEMENTED;
}

PDATETIME PcUtilityGetTime()
{
	NOT_IMPLEMENTED;
}

VOID PcUtilitySetTime(PDATETIME pDateTime)
{
	NOT_IMPLEMENTED;
}

VOID PcUtilitySetStatusLed(UINT8 ledId)
{
	NOT_IMPLEMENTED;
}

PDATETIME PcUtilityGetBiosDate()
{
	NOT_IMPLEMENTED;
}

BOOL PcUtilityCheckProcessorCompatibility()
{
	return TRUE;
}

VOID PcUtilityDelay(UINT32 milliSecs)
{
	NOT_IMPLEMENTED;
}

VOID PcUtilityPause()
{
	asm("xchg %bx, %bx");
}

VOID PcUtilityHalt()
{
	for(;;);
}

VOID PcUtilityReboot()
{
	Reboot(); /* PcShould be BiosReboot() */
}


