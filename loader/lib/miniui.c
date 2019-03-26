/*
  - Date: 2018-03-21
  - Author: Joel
  - Purpose: Minimalistic UI implementation.
			 This textual UI is used to display basic messages.
			 Optionally we can choose not to initialize the other UIs if it is unnecessary.
			 
*/

/* INCLUDES */
#include <kldr.h>


/* PRIVATE VARIABLES */
static UINT32 CursorX = 0;
static UINT32 CursorY = 0;

/* PRIVATE FUNCTIONS */
VOID MiniUiSetVideoMode(UINT8 requestedDisplayMode)
{
	MachineConsoleSetDisplayMode(requestedDisplayMode);
	MachineConsoleShowCursor(FALSE);
}

/* GLOBAL FUNCTIONS */
VOID MiniUiInit(UINT8 requestedDisplayMode)
{
	TRACE("MiniUiInit() called.");
	
	UiVtbl.UiUninit = (PVOID) MiniUiUninit;
	
	UiVtbl.UiDrawText = (PVOID) MiniUiDrawText;
	UiVtbl.UiDrawTextEx = (PVOID) MiniUiDrawTextEx;
	UiVtbl.UiFillArea = (PVOID) MiniUiFillArea;
	
	UiVtbl.UiDrawWelcomeScreen = (PVOID) MiniUiDrawWelcomeScreen;
	UiVtbl.UiDrawBox = (PVOID) MiniUiDrawBox;
	UiVtbl.UiDrawMessageBox = (PVOID) MiniUiDrawMessageBox;
	UiVtbl.UiDrawInfoBox = (PVOID) MiniUiDrawInfoBox;
	UiVtbl.UiDrawCriticalMessageBox = (PVOID) MiniUiDrawCriticalMessageBox;
	
	UiVtbl.UiDrawStatusBar = (PVOID) MiniUiDrawStatusBar;
	UiVtbl.UiDrawButton = (PVOID) MiniUiDrawButton;
	
	MiniUiSetVideoMode(requestedDisplayMode);
	MiniUiDrawWelcomeScreen();
}

VOID MiniUiUninit()
{
	MachineConsoleSetDisplayMode(UI_TEXT);
	MachineConsoleShowCursor(TRUE);
}

VOID MiniUiDrawText(PCSTR pText)
{
	/* Use machine specific character output */
	while(*pText!='\0')
	{
		MachineConsolePutChar(*pText);
		//MachineConsoleGetCursorPosition(&CursorX, &CursorY);

		CursorX++;
		if (CursorX > ScreenWidth)
		{
			CursorY++;
			CursorX = 0;
		}
		
		MachineConsoleSetCursorPosition(CursorX, CursorY);
		
		pText++;
	}
}

/* Standard drawing functions */
VOID MiniUiDrawTextEx(UINT32 x, UINT32 y, UINT8 colorAttribute, PCSTR pText)
{
	/* Use no formatting */
	MiniUiDrawText(pText);
}

VOID MiniUiFillArea(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, CHAR fillChar)
{
}

VOID MiniUiDrawFrame(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, UINT8 lineStyle)
{
}

/* Complex drawing functions - require other standard drawing functions */
VOID MiniUiDrawWelcomeScreen()
{
	//MachineConsoleGetCursorPosition(&CursorX, &CursorY);

	/* Not clearing the screen */
	PCSTR pString = "Starting KoreOS...";
	
	MiniUiDrawText(pString);
}

VOID MiniUiDrawBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, UINT8 lineStyle, PCSTR pCaption)
{
}

VOID MiniUiDrawMessageBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption)
{
}

VOID MiniUiDrawInfoBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption)
{
}

VOID MiniUiDrawCriticalMessageBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption)
{
}

VOID MiniUiDrawStatusBar(PCSTR pStatusText, PCSTR pAdditionalStatusText)
{
}

VOID MiniUiDrawButton(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption, BOOL isEnabled, BOOL isDefault, BOOL isSelected, BOOL isPressed)
{
}
