/*
  - Date: 2018-03-18
  - Author: Joel
  - Purpose: Definitions for PC Utility functions
*/

/* GLOBAL DEFINITIONS */

/* GLOBAL VARIABLES */

/* GLOBAL FUNCTIONS */
VOID PcUtilityBeep();
PDATETIME PcUtilityGetTime();
VOID PcUtilitySetTime(PDATETIME pDateTime);
VOID PcUtilitySetStatusLed(UINT8 ledId);
PDATETIME PcUtilityGetBiosDate();
BOOL PcUtilityCheckProcessorCompatibility();
VOID PcUtilityDelay(UINT32 milliSecs);
VOID PcUtilityPause();
VOID PcUtilityHalt();
VOID PcUtilityReboot();


