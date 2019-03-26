/*
  - Date: 2018-03-10
  - Author: Joel
  - Purpose: PC Input/Output implementation:
			 Machine specific video/keyboard functions.
*/

/* INCLUDES */
#include <kldr.h>

/* PRIVATE DEFINITIONS */
#define TEXT_CURSOR_SHAPE_ROW_START					0x06
#define TEXT_CURSOR_SHAPE_ROW_END					0x07

/* PRIVATE VARIABLES */
UINT8 TextCursorShapeRowStart = TEXT_CURSOR_SHAPE_ROW_START;
UINT8 TextCursorShapeRowEnd = TEXT_CURSOR_SHAPE_ROW_END;

/* PRIVATE FUNCTIONS */

BOOL PcConsoleSetCursorShape(UINT8 rowStart, UINT8 rowEnd)
{
	/*
		INT 10h - Video Bios Services.
		
		On entry:
			AH = 01h set text-mode cursor shape
			CH = scan row start
			CL = scan row end
		On return:
			Nothing
	*/	
	
	REGISTERS regs;
	PREGISTERS pRegs = &regs;
		
	regs.EAX = (0x01) << 8;
	regs.EBX = 0;
	regs.ECX = (rowStart) << 8 | rowEnd;
	regs.EDX = 0;
	regs.ESI = 0;
	regs.EDI = 0;
	regs.EBP = 0;
	regs.DS = 0;
	regs.ES = 0;
	regs.FS = 0;
	regs.GS = 0;
	regs.EFLAGS = 0;
	
	CallBiosInterrupt(0x10, pRegs, pRegs);	
}

VOID PcConsoleSetBiosVideoMode(UINT8 requestedBiosVideoMode)
{
	/*
		INT 10h - Video Bios Services.
		
		On entry:
			AH = 00h set video mode
			AL = video mode
		On return:
			AL = video mode flag / CRT controller mode byte
	*/	
	
	REGISTERS regs;
	PREGISTERS pRegs = &regs;
		
	regs.EAX = (0x00) << 8 | requestedBiosVideoMode;
	regs.EBX = 0;
	regs.ECX = 0;
	regs.EDX = 0;
	regs.ESI = 0;
	regs.EDI = 0;
	regs.EBP = 0;
	regs.DS = 0;
	regs.ES = 0;
	regs.FS = 0;
	regs.GS = 0;
	regs.EFLAGS = 0;
	
	CallBiosInterrupt(0x10, pRegs, pRegs);	
}

/* GLOBAL FUNCTIONS */
VOID PcConsolePutChar(CHAR ch)
{	
	//TRACE("PcIoPutChar() called.");
	
	/*
		INT 10h - Video Bios Services.
		
		On entry:
			AH = 0ah write character only at cursor position (no attribute byte)
			AL = character
			BH = page number
			CX = number of times to print character
		On return:
			Nothing
	*/	
	
	REGISTERS regs;
	PREGISTERS pRegs = &regs;
		
	regs.EAX = (0x0a) << 8 | ch;
	regs.EBX = 0;
	regs.ECX = 1;
	regs.EDX = 0;
	regs.ESI = 0;
	regs.EDI = 0;
	regs.EBP = 0;
	regs.DS = 0;
	regs.ES = 0;
	regs.FS = 0;
	regs.GS = 0;
	regs.EFLAGS = 0;
		
	CallBiosInterrupt(0x10, pRegs, pRegs);
	
	//TRACE("RETURNED!!!");
}

VOID PcConsoleWaitForKeyPress()
{
	
}

CHAR PcConsoleGetChar()
{
	
}

UINT8 PcConsoleDetectBestDisplayMode()
{
	UINT8 detectedVideoMode = UI_TEXT;
	return detectedVideoMode;
}

VOID PcConsoleEnableBlinking(BOOL enableBlinking)
{
	REGISTERS regs;
	PREGISTERS pRegs = &regs;
		
	regs.EAX = (0x10) << 8 | 0x03;
	if (enableBlinking)
		regs.EBX = 1;
	else
		regs.EBX = 0;

	regs.ECX = 0;
	regs.EDX = 0;
	regs.ESI = 0;
	regs.EDI = 0;
	regs.EBP = 0;
	regs.DS = 0;
	regs.ES = 0;
	regs.FS = 0;
	regs.GS = 0;
	regs.EFLAGS = 0;
		
	CallBiosInterrupt(0x10, pRegs, pRegs);
}

VOID PcConsoleSetPaletteColor(UINT8 colorToChange, UINT8 red, UINT8 green, UINT8 blue)
{
	REGISTERS regs;
	PREGISTERS pRegs = &regs;
		
	regs.EAX = (0x10) << 8 | 0x10;
	regs.EBX = colorToChange;
	regs.ECX = green << 4 | blue;
	regs.EDX = red << 4;
	regs.ESI = 0;
	regs.EDI = 0;
	regs.EBP = 0;
	regs.DS = 0;
	regs.ES = 0;
	regs.FS = 0;
	regs.GS = 0;
	regs.EFLAGS = 0;
		
	CallBiosInterrupt(0x10, pRegs, pRegs);
}

VOID PcConsoleSetDisplayMode(UINT8 requestedDisplayMode)
{
	if (requestedDisplayMode == UI_TEXT)
	{
		PcConsoleSetBiosVideoMode(0x03);
		ScreenWidth = 80;
		ScreenHeight = 25;
		ScreenBytesPerScanLine = 160;
		ScreenBufferSize = ScreenBytesPerScanLine * ScreenHeight;
		PcConsoleEnableBlinking(FALSE);
		//PcConsoleSetPaletteColor(15, 63, 63, 0);
	}
	else if (requestedDisplayMode == UI_VESA_GRAPHICS)
	{
		NOT_IMPLEMENTED;
	}	
}	

BOOL PcConsoleShowCursor(BOOL doShowCursor)
{
	/* Use SetCursorShape to Show or Hide the cursor */
	if (doShowCursor)
		PcConsoleSetCursorShape(TextCursorShapeRowStart, TextCursorShapeRowEnd);
	else
		PcConsoleSetCursorShape(TextCursorShapeRowEnd, TextCursorShapeRowStart);
}


VOID PcConsoleGetCursorPosition(PUINT8 pX, PUINT8 pY)
{
	/*
		INT 10h - Video Bios Services.
		
		On entry:
			AH = 02h set cursor position
			BH = video page number
			DH = row
			DL = column
		On return:
			Nothing
	*/	
	
	/*
	REGISTERS regs;
	PREGISTERS pRegs = &regs;
		
	regs.EAX = (0x02) << 8;
	regs.EBX = (0x00) << 8;
	regs.ECX = 0;
	regs.EDX = (y) << 8 | x;
	regs.ESI = 0;
	regs.EDI = 0;
	regs.EBP = 0;
	regs.DS = 0;
	regs.ES = 0;
	regs.FS = 0;
	regs.GS = 0;
	regs.EFLAGS = 0;
	
	CallBiosInterrupt(0x10, pRegs, pRegs);	
	*/
	*pY++;
	
}

VOID PcConsoleSetCursorPosition(UINT8 x, UINT8 y)
{
	/*
		INT 10h - Video Bios Services.
		
		On entry:
			AH = 02h set cursor position
			BH = video page number
			DH = row
			DL = column
		On return:
			Nothing
	*/	
	
	REGISTERS regs;
	PREGISTERS pRegs = &regs;
		
	regs.EAX = (0x02) << 8;
	regs.EBX = (0x00) << 8;
	regs.ECX = 0;
	regs.EDX = (y) << 8 | x;
	regs.ESI = 0;
	regs.EDI = 0;
	regs.EBP = 0;
	regs.DS = 0;
	regs.ES = 0;
	regs.FS = 0;
	regs.GS = 0;
	regs.EFLAGS = 0;
	
	CallBiosInterrupt(0x10, pRegs, pRegs);	
}
