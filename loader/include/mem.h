/*
  - Date: 2018-04-02
  - Author: Joel
  - Purpose: Definitions for Memory functions
*/

#ifndef __MEM_H
#define __MEM_H

/* DEFINITIONS */
#if defined(ARCH_TYPE_X86_32) || defined(ARCH_TYPE_X86_64)
	#define PAGE_SIZE 			4096
#endif

#define MAX_MEMORY_DESCRIPTORS					128

#define MEMORY_DESCRIPTOR_TYPE_FREE				0
#define MEMORY_DESCRIPTOR_TYPE_BIOS_AREA		1
#define MEMORY_DESCRIPTOR_TYPE_X				2
#define MEMORY_DESCRIPTOR_TYPE_Y				3






typedef INT32 PFN_NUMBER;

typedef struct tagMEMORY_DESCRIPTOR
{
	PFN_NUMBER base;	//Allocation base (page size aligned)
	PFN_NUMBER length;	//Allocation length (page size aligned)
	INT32 type;			//Allocation type
} MEMORY_DESCRIPTOR, *PMEMORY_DESCRIPTOR;


/* FUNCTIONS */
BOOL MemInit();
VOID DisplayMemoryEntries();

#endif /* __MEM_H */