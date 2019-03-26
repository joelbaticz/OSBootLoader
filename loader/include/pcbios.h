/*
  - Date: 2018-03-10
  - Author: Joel
  - Purpose: Definitions for PC BIOS
*/


/* DEFINITIONS */

/* GLOBALS */
#pragma pack(1)
typedef struct tagREGISTERS
{
	UINT32 EAX;
	UINT32 EBX;
	UINT32 ECX;
	UINT32 EDX;
	UINT32 ESI;
	UINT32 EDI;
	UINT32 EBP;

	UINT16 DS;
	UINT16 ES;
	UINT16 FS;
	UINT16 GS;

	UINT32 EFLAGS;  //Only low 16 bits are usable	

} REGISTERS, *PREGISTERS;

#define EFLAGS_CARRY			0x0001
#define EFLAGS_ZERO				0x0040

#define SEGMENT(value)			(value / 16)
#define OFFSET(value)			(value - (value / 16) * 16)

/* GLOBAL FUNCTION PROTOTYPES */
VOID _cdecl Reboot(); /* Should be PcBiosReboot() */
STATUS_CODE _cdecl CallBiosInterrupt(UINT8 interruptNumber, PREGISTERS pRegsIn, PREGISTERS pRegsOut); /* Should be PcBiosCallInterrupt() */
