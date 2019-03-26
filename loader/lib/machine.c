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

/* GLOBAL FUNCTIONS */
BOOL MachineInit()
{
	#ifdef MACHINE_TYPE_PC
		PcInit();
	#endif

	#ifdef MACHINE_TYPE_XBOX
		DEBUG_NOT_IMPLEMENTED;
		//XBoxInit();
	#endif
	
	return MachineUtilityCheckProcessorCompatibility();	
}

