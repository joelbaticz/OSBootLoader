/*
  - Date: 2018-04-02
  - Author: Joel
  - Purpose: Memory functions implementation:
			 Machine independent memory functions.
*/

/* INCLUDES */
#include <kldr.h>

/* DEFINITIONS */
#define MAX_MEMORY_DESCRIPTOR_COUNT				128

/* VARIABLES */
MEMORY_DESCRIPTOR MemoryMap[MAX_MEMORY_DESCRIPTOR_COUNT];
UINT32 memoryMapEntryCount;

/* FUNCTIONS */
BOOL MemInit()
{
	
	/* Call machine specific Memory Map feature */
	/* It will give us a pointer to the architecture independent memory map and set how many entries we have */
	if(!MachineMemoryGetMemoryMap(&MemoryMap[0], &memoryMapEntryCount))
	{
		/* Function call unsuccessful */
		return FALSE;
	}
	else
	{
		/* Function call successful */
		return TRUE;
	}
	
	/* If the memory map query did not result in any entries */
	//if (memoryMapEntryCount == 0) return FALSE;
	
	/* We had actual results back */	
	//return TRUE;
}

PCHAR Convert(PCHAR dest, unsigned int num)
{
	CHAR temp[20] = {0};
	PCHAR pTemp = &temp[0];
	PCHAR pText = dest;
		
	uitoa(num, pTemp, 16);
	strcpy(pText, pTemp);
	pText += strlen(pTemp);
	*pText++ = ' ';
	*pText++ = '(';
	uitoa(num, pTemp, 10);
	strcpy(pText, pTemp);
	pText += strlen(pTemp);
	*pText++ = ')';
	*pText++ = '\0';
	
	return dest;
}

VOID DisplayMemoryEntries()
{
	UINT32 x = 7;
	UINT32 y = 0;
	UINT32 x2 = 74;
	UINT32 y2 = 23 - y;
	
	UiDrawBox(x, y, x2, y2, 0x3b, LINE_STYLE_SINGLE, "");
	UiDrawTextEx(x + 2, y, COLOR_DO_NOT_CARE, "Memory Descriptors:     ");
	
	CHAR temp[20] = {0};
	itoa(memoryMapEntryCount, &temp[0], 10);
	UiDrawTextEx(x + 22, y, COLOR_DO_NOT_CARE, &temp[0]);

	//DebugPrintf("MapEntryCount=%x", memoryMapEntryCount);
	
	
	UiDrawTextEx(x + 2, y + 1, COLOR_DO_NOT_CARE, "BASE                   | LENGTH                 | TYPE");
	UiDrawTextEx(x + 2, y + 2, COLOR_DO_NOT_CARE, "-----------------------+------------------------+---------------");
	CHAR text[80] = {0};
	
	int tempLength = 0;
	int textLength = 0;
	
	unsigned int maxMem = 0;
	
	for(int index = 0; index < memoryMapEntryCount; index++)
	{
		
		UiDrawTextEx(x + 2, y + 3 + index, COLOR_DO_NOT_CARE, Convert(&text[0], MemoryMap[index].base));
		UiDrawTextEx(x + 27, y + 3 + index, COLOR_DO_NOT_CARE, Convert(&text[0], MemoryMap[index].length));
		UiDrawTextEx(x + 52, y + 3 + index, COLOR_DO_NOT_CARE, Convert(&text[0], MemoryMap[index].type));
				
		UiDrawTextEx(x + 25, y + 3 + index, COLOR_DO_NOT_CARE, "|");
		UiDrawTextEx(x + 50, y + 3 + index, COLOR_DO_NOT_CARE, "|");
		
		if (maxMem < MemoryMap[index].base + MemoryMap[index].length)
		{
			maxMem = MemoryMap[index].base + MemoryMap[index].length;
		}
		
		//DebugPrintf("Base = %x, Length = %x, Type = %x", MemoryMap[index].base, MemoryMap[index].length, MemoryMap[index].type);
	}
	
	int index = memoryMapEntryCount;
	
	UiDrawTextEx(x + 2, y + 3 + index, COLOR_DO_NOT_CARE, "-----------------------+------------------------+---------------");
	index+=2;
	
	UiDrawTextEx(x + 2, y + 3 + index, COLOR_DO_NOT_CARE, "Max memory: ");
	UiDrawTextEx(x + 20, y + 3 + index, COLOR_DO_NOT_CARE, Convert(&text[0], maxMem));
	
	//UiDrawTextEx(x + 20, y + 4 + index, COLOR_DO_NOT_CARE, Convert(&text[0], 0x0ffffffff));
	
	
	
}