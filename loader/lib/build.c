/*
  - Date: 2018-02-22
  - Author: Joel
  - Purpose: Store Build information in a data structure
*/

#include <kldr.h>

/* Architecture Types */
static PCHAR pArchTypeX8632 = "X86-32\0";
static PCHAR pArchTypeX8664 = "X86-64\0";
static PCHAR pArchTypeARM = "ARM\0";
static PCHAR pArchTypeMIPS = "MIPS\0";
static PCHAR pArchTypePOWERPC = "POWERPC\0";

/* Machine Types */
static PCHAR pMachineTypePC = "PC\0";
static PCHAR pMachineTypeXBOX = "XBOX\0";

/* Build Types */
static PCHAR pBuildTypeDEBUG = "Debug Build\0";
static PCHAR pBuildTypeRELEASE = "Release Build\0";

/* Debug Levels */
static PCHAR pDebugLevelDEBUG = "Debug\0";
static PCHAR pDebugLevelWARNING = "Warning\0";
static PCHAR pDebugLevelTRACE = "Trace\0";

VOID __cdecl GetBuildInformation(OUT PBUILD_INFO_BLOCK pBuildInfoBlock)
{
	/* ARCH TYPES */
	#ifdef ARCH_TYPE_X86_32
		pBuildInfoBlock->Architecture = pArchTypeX8632;
	#endif
	#ifdef ARCH_TYPE_X86_64
		pBuildInfoBlock->Architecture = pArchTypeX8664;
	#endif
	#ifdef ARCH_TYPE_ARM
		pBuildInfoBlock->Architecture = pArchTypeARM;
	#endif
	#ifdef ARCH_TYPE_MIPS
		pBuildInfoBlock->Architecture = pArchTypeMIPS;
	#endif
	#ifdef ARCH_TYPE_POWERPC
		pBuildInfoBlock->Architecture = pArchTypePOWERPC;
	#endif
	
	/* MACHINE TYPES */
	#ifdef MACHINE_TYPE_PC
		pBuildInfoBlock->Machine = pMachineTypePC;
	#endif
	#ifdef MACHINE_TYPE_XBOX
		pBuildInfoBlock->Machine = pMachineTypeXBOX;
	#endif
	
	/* BUILD TYPES */ 
	#ifdef BUILD_TYPE_DEBUG
		pBuildInfoBlock->Type = pBuildTypeDEBUG;
	#endif
	#ifdef BUILD_TYPE_RELEASE
		pBuildInfoBlock->Type = pBuildTypeRELEASE;
	#endif

	/* DEBUG LEVES */
	#ifdef DEBUG_LEVEL_DEBUG
		pBuildInfoBlock->DebugLevel = pDebugLevelDEBUG;
	#endif
	#ifdef DEBUG_LEVEL_WARNING
		pBuildInfoBlock->DebugLevel = pDebugLevelWARNING;
	#endif
	#ifdef DEBUG_LEVEL_TRACE
		pBuildInfoBlock->DebugLevel = pDebugLevelTRACE;
	#endif
}