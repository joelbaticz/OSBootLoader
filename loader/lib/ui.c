/*
  - Date: 2018-03-14
  - Author: Joel
  - Purpose: UI implementation:
			 Higher level UI function init.
*/

/* INCLUDES */
#include <kldr.h>

/* GLOBAL FUNCTIONS */
BOOL UiInit(BOOL doCompleteUiInit)
{
	UINT8 detectedVideoMode;
	
	TRACE("UiInit() called.");

	/* Functions implemented in Ui.c itself */	
	UiVtbl.UiDrawTextCenter = (PVOID) UiDrawTextCenter;
	
	
	
	
	
	
	
	
	
	if (!doCompleteUiInit)
	{
		MiniUiInit(UI_TEXT);
		return TRUE;
	}
		
	detectedVideoMode = MachineConsoleDetectBestDisplayMode();
	
	//Check INI file options related to the requested video mode
	//IF INI OPTIONS ARE AVAILABLE!!!

	if (detectedVideoMode == UI_TEXT)
	{
		TuiInit(detectedVideoMode);
	}
	else if (detectedVideoMode == UI_GRAPHICS)
	{
		NOT_IMPLEMENTED;
		//GuiInit();
	}

	//Check INI file options related to Colors and other Ui settings that need to 
	//override defaults.
	//IF INI OPTIONS ARE AVAILABLE!!!
		
	return TRUE; //detectedVideoMode;
}

VOID UiUninit()
{
	UiVtbl.UiUninit();
}

/* Standard drawing functions */
VOID UiDrawText(PCSTR pText)
{
	UiVtbl.UiDrawText(pText);
}

VOID UiDrawTextCenter(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, PCSTR pText)
{
	UINT32 centerX;
	UINT32 centerY;
	
	centerX = (left + right - strlen(pText)) / 2 + 1;
	centerY = (top + bottom) / 2;
	
	UiDrawTextEx(centerX, centerY, colorAttribute, pText); 
}

VOID UiDrawTextEx(UINT32 x, UINT32 y, UINT8 colorAttribute, PCSTR pText)
{
	UiVtbl.UiDrawTextEx(x, y, colorAttribute, pText);
}

VOID UiFillArea(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, CHAR fillChar)
{
	UiVtbl.UiFillArea(left, top, right, bottom, colorAttribute, fillChar);
}

VOID UiDrawFrame(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, UINT8 lineStyle)
{
	UiVtbl.UiDrawFrame(left, top, right, bottom, colorAttribute, lineStyle);
}

/* Complex drawing functions - require other standard drawing functions */
VOID UiDrawWelcomeScreen()
{
	UiVtbl.UiDrawWelcomeScreen();
}

VOID UiDrawBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, UINT8 lineStyle, PCSTR pCaption)
{
	UiVtbl.UiDrawBox(left, top, right, bottom, colorAttribute, lineStyle, pCaption);
}

VOID UiDrawMessageBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption)
{
	UiVtbl.UiDrawMessageBox(left, top, right, bottom, pCaption);
}

VOID UiDrawInfoBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption)
{
	UiVtbl.UiDrawInfoBox(left, top, right, bottom, pCaption);
}

VOID UiDrawCriticalMessageBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption)
{
	UiVtbl.UiDrawCriticalMessageBox(left, top, right, bottom, pCaption);
}

VOID UiDrawStatusBar(PCSTR pStatusText, PCSTR pAdditionalStatusText)
{
	UiVtbl.UiDrawStatusBar(pStatusText, pAdditionalStatusText);
}

VOID UiDrawButton(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption, BOOL isEnabled, BOOL isDefault, BOOL isSelected, BOOL isPressed)
{
	UiVtbl.UiDrawButton(left, top, right, bottom, pCaption, isEnabled, isDefault, isSelected, isPressed);
}