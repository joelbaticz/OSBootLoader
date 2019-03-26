#include <kldr.h>

VOID UiTextClearScreen()
{
	PCHAR ptrVidMem = ptrVideoMemory;
	SIZE i = 0;
	
	for (i = 0; i < 80*25; i++)
	{
		*ptrVidMem = ' ';
		ptrVidMem++;
		*ptrVidMem = currentTextColor;
		ptrVidMem++;
	}
	
//	cursorPosX = 0;
//	cursorPosY = 0;
	
	//Set Cursor Position
	// REGISTERS regs;
	// regs.EAX = 0x0200;
	// regs.EBX = 0;
	// regs.ECX = 0;
	// regs.EDX = 0;
	// regs.ESI = 0;
	// regs.EDI = 0;
	// regs.EFLAGS = 0;
	// PREGISTERS pRegs = &regs;
	// CallRealModeInterrupt(0x10, pRegs);
}
