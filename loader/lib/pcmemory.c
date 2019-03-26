/*
  - Date: 2018-04-04
  - Author: Joel
  - Purpose: PC Memory implementation:
		 Machine specific memory functions.
*/

/* INCLUDES */
#include <kldr.h>

#define BIOS_MEMORY_MAP_TYPE_USABLE					1
#define BIOS_MEMORY_MAP_TYPE_RESERVED				2
#define BIOS_MEMORY_MAP_TYPE_ACPI_RECLAIMABLE		3
#define BIOS_MEMORY_MAP_TYPE_ACPI_NVS				4
#define BIOS_MEMORY_MAP_TYPE_BAD					5
	
/* DEFINITIONS */
//__attribute__((packed))
typedef struct tagBIOS_MEMORY_MAP_ENTRY
{
	UINT32 baseLow;
	UINT32 baseHigh;
	UINT32 lengthLow;
	UINT32 lengthHigh;
	UINT32 type;
	UINT32 ACPI;
} BIOS_MEMORY_MAP_ENTRY, *PBIOS_MEMORY_MAP_ENTRY;
/* VARIABLES */


/* FUNCTIONS */
BOOL PcMemoryGetMemoryMap(OUT PMEMORY_DESCRIPTOR pMemoryMap, OUT PUINT32 pMemoryMapEntryCount)
{
	
	*pMemoryMapEntryCount = 0;
	BOOL validE820Call = TRUE;
	
	/*
		INT 15h - Bios Memory services.
		
		On entry:
			EAX = e820h - Query System Memory Map
			EBX = Continuation value (Index = 0)
			ECX = Buffer size
			EDX = Signature ("SMAP")
			ES:DI = Pointer to Buffer
		On return:
			EAX = e820h
			EBX = Continuation value (zero if last entry)
			ECX = Buffer size (actual)
			EDX = Signature ??? not EAX?
			ES:DI = Pointer to filled Buffer

	*/	
	
	REGISTERS regs;
	PREGISTERS pRegs = &regs;
		
	PBIOS_MEMORY_MAP_ENTRY pBiosBuffer = (PBIOS_MEMORY_MAP_ENTRY) (UINT32)X86_REAL_MODE_BUFFER_ADDRESS;
		
	regs.EAX = 0xe820;
	regs.EBX = 0;
	regs.ECX = 24;
	regs.EDX = 0x534d4150;
	regs.ESI = 0;
	regs.EDI = OFFSET((UINT32)pBiosBuffer);
	regs.EBP = 0;
	regs.DS = 0;
	regs.ES = SEGMENT((UINT32)pBiosBuffer);
	regs.FS = 0;
	regs.GS = 0;
	regs.EFLAGS = 0;
	
		
	while(TRUE)
	{
		regs.EAX = 0xe820; /* Needs to be reset before every function call */
		
		CallBiosInterrupt(0x15, pRegs, pRegs);	
		
		
		//DebugPrintf("INT 0x15 Returned: EFLAGS_CARRY=%x, EAX=%x, EBX=%x, ECX=%x, EDX=%x, ES=%x, EDI=%x",regs.EFLAGS & EFLAGS_CARRY, regs.EAX, regs.EBX, regs.ECX, regs.EDX, regs.ES, regs.EDI);
		//PAUSE;
		
		if ((regs.EFLAGS & EFLAGS_CARRY) || (regs.EAX != 0x534d4150))
		{
			/* Function call failed */
			return FALSE;
		}
		
		if (regs.EBX == 0)
		{
			/* Last entry reached --> return with success */
			return TRUE;
		}
		
		/* Successful function call - now copy entry to descriptor */
			
		//DebugPrintf("BUFFER: BASE_LOW=%x, BASE_HIGH=%x, LENGTH_LOW=%x, LENGTH=HIGH=%x, TYPE=%x",pBiosBuffer->baseLow, pBiosBuffer->baseHigh, pBiosBuffer->lengthLow, pBiosBuffer->lengthHigh, pBiosBuffer->type);
		//PAUSE;

		pMemoryMap->base = (PFN_NUMBER) (pBiosBuffer->baseLow);
		pMemoryMap->length = (PFN_NUMBER) (pBiosBuffer->lengthLow); // Round up
		
		/* Type conversion */
		pMemoryMap->type = pBiosBuffer->type;
		
			
		// if (pBiosBuffer->type == BIOS_MEMORY_MAP_TYPE_USABLE)
		// {
			// pMemoryMap->type = MEMORY_DESCRIPTOR_TYPE_FREE;
		// }				
		// else if (pBiosBuffer->type != BIOS_MEMORY_MAP_TYPE_USABLE)
		// {
			// pMemoryMap->type = MEMORY_DESCRIPTOR_TYPE_BIOS_AREA;
		// }	
		
		pMemoryMap++;
		
		(*pMemoryMapEntryCount)++;
		
	}

}

