/*
  - Date: 2018-03-14
  - Author: Joel
  - Purpose: UI implementation:
			 Higher level UI function implementation for Text UI interface.
*/

/* INCLUDES */
#include <kldr.h>

/* PRIVATE DEFINITIONS */
#define TEXT_VIDEO_BUFFER_ADDRESS						0xb8000

/* PRIVATE VARIABLES */
static UINT32 CursorX = 0;
static UINT32 CursorY = 0;

/* PRIVATE FUNCTIONS */
VOID TuiSetVideoMode(UINT8 requestedDisplayMode)
{
	MachineConsoleSetDisplayMode(requestedDisplayMode);
	MachineConsoleShowCursor(FALSE);
}

/* GLOBAL FUNCTIONS */
VOID TuiInit(UINT8 requestedDisplayMode)
{
	TRACE("TuiInit() called.");
	
	UiVtbl.UiUninit = (PVOID) TuiUninit;
	
	UiVtbl.UiDrawText = (PVOID) TuiDrawText;
	UiVtbl.UiDrawTextEx = (PVOID) TuiDrawTextEx;
	UiVtbl.UiFillArea = (PVOID) TuiFillArea;
	UiVtbl.UiDrawFrame = (PVOID) TuiDrawFrame;
	
	UiVtbl.UiDrawWelcomeScreen = (PVOID) TuiDrawWelcomeScreen;
	
	UiVtbl.UiDrawBox = (PVOID) TuiDrawBox;
	UiVtbl.UiDrawMessageBox = (PVOID) TuiDrawMessageBox;
	UiVtbl.UiDrawInfoBox = (PVOID) TuiDrawInfoBox;
	UiVtbl.UiDrawCriticalMessageBox = (PVOID) TuiDrawCriticalMessageBox;

	UiVtbl.UiDrawStatusBar = (PVOID) TuiDrawStatusBar;
	UiVtbl.UiDrawButton = (PVOID) TuiDrawButton;
	
	
	TuiSetVideoMode(requestedDisplayMode);
	TuiDrawWelcomeScreen();
}

VOID TuiUninit()
{
	MachineConsoleSetDisplayMode(UI_TEXT);
	MachineConsoleShowCursor(TRUE);
}

VOID TuiPutChar(CHAR ch)
{
	PCHAR pVideo = (PCHAR) TEXT_VIDEO_BUFFER_ADDRESS;
	
	pVideo += (CursorY * ScreenWidth + CursorX) * 2;
	
	*pVideo = ch;
	
	CursorX++;
	if (CursorX > ScreenWidth)
	{
		CursorY++;
		CursorX = 0;
	}	
}

VOID TuiPutCharEx(UINT32 x, UINT32 y, UINT8 colorAttribute, CHAR ch)
{
	PCHAR pVideo = (PCHAR) TEXT_VIDEO_BUFFER_ADDRESS;
	
	CursorX = x;
	CursorY = y;
	
	pVideo += (CursorY * ScreenWidth + CursorX) * 2;
	
	*pVideo = ch;
	
	if (colorAttribute != COLOR_DO_NOT_CARE)
	{
		pVideo++;
		*pVideo = colorAttribute;
	}
	
	CursorX++;
	if (CursorX > ScreenWidth)
	{
		CursorY++;
		CursorX = 0;
	}
}

/* Standard drawing functions */
VOID TuiDrawText(PCSTR pText)
{
	while(*pText!='\0')
	{
		TuiPutChar(*pText);		
		pText++;
	}
}

VOID TuiDrawTextEx(UINT32 x, UINT32 y, UINT8 colorAttribute, PCSTR pText)
{
	while(*pText!='\0')
	{
		TuiPutCharEx(x, y, colorAttribute, *pText);		
		pText++;
		x++;
	}
}

VOID TuiFillArea(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, CHAR fillChar)
{
	for(size_t y = top; y <= bottom; y++)
	{
		for(size_t x = left; x <= right; x++)
		{
			TuiPutCharEx(x, y, colorAttribute, fillChar);		
		}
	}	
}

VOID TuiDrawFrame(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, UINT8 lineStyle)
{
	//TRACE("TuiDrawFrame() called.");
	
	if (lineStyle == LINE_STYLE_SINGLE)
	{
		TuiPutCharEx(left, top, colorAttribute, CORNER_UPPER_LEFT);
		TuiPutCharEx(right, top, colorAttribute, CORNER_UPPER_RIGHT);
		TuiPutCharEx(left, bottom, colorAttribute, CORNER_LOWER_LEFT);
		TuiPutCharEx(right, bottom, colorAttribute, CORNER_LOWER_RIGHT);	
		TuiFillArea(left + 1, top, right - 1, top, colorAttribute, LINE_HORIZONTAL);
		TuiFillArea(left + 1, bottom, right - 1, bottom, colorAttribute, LINE_HORIZONTAL);
		TuiFillArea(left, top + 1, left, bottom - 1, colorAttribute, LINE_VERTICAL);
		TuiFillArea(right, top + 1, right, bottom - 1, colorAttribute, LINE_VERTICAL);
	}
	else if (lineStyle == LINE_STYLE_DOUBLE)
	{
		TuiPutCharEx(left, top, colorAttribute, CORNER_UPPER_LEFT_DOUBLE);
		TuiPutCharEx(right, top, colorAttribute, CORNER_UPPER_RIGHT_DOUBLE);
		TuiPutCharEx(left, bottom, colorAttribute, CORNER_LOWER_LEFT_DOUBLE);
		TuiPutCharEx(right, bottom, colorAttribute, CORNER_LOWER_RIGHT_DOUBLE);	
		TuiFillArea(left + 1, top, right - 1, top, colorAttribute, LINE_HORIZONTAL_DOUBLE);
		TuiFillArea(left + 1, bottom, right - 1, bottom, colorAttribute, LINE_HORIZONTAL_DOUBLE);
		TuiFillArea(left, top + 1, left, bottom - 1, colorAttribute, LINE_VERTICAL_DOUBLE);
		TuiFillArea(right, top + 1, right, bottom - 1, colorAttribute, LINE_VERTICAL_DOUBLE);
	} 
}

VOID TuiDrawShadow(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom)
{
	INT32 x;

	//x = right + 1;
	//y = top + 1;
	
	TuiFillArea(right + 1, top + 1, right + 1, bottom + 1, 0x07, ' ');
	TuiFillArea(left + 1, bottom + 1, right + 1, bottom + 1, 0x07, ' ');
	
}

/* Complex drawing functions - require other standard drawing functions */
VOID TuiDrawWelcomeScreen()
{
	/* Clear screen */
	TuiFillArea(0, 0, 80, 25, ColorBackground, ' ');
	
	/* Draw welcome text */
	TuiDrawTextEx(2,2, COLOR_DO_NOT_CARE, "Kore Loader");//UiTextBackgroundColor << 4 | UiTextForegroundColor);
	TuiDrawTextEx(2,3, COLOR_DO_NOT_CARE, "===========");//UiTextBackgroundColor << 4 | UiTextForegroundColor);
}

VOID TuiDrawBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, UINT8 lineStyle, PCSTR pCaption)
{
	UINT32 textPosition;
	
	TuiFillArea(left, top, right, bottom, colorAttribute, ' ');
	TuiDrawFrame(left, top, right, bottom, colorAttribute, lineStyle);
	TuiDrawShadow(left, top, right, bottom);
	
	textPosition = (left + right - strlen(pCaption)) / 2 + 1;	
	TuiDrawTextEx(textPosition, top, colorAttribute, pCaption);	
}

VOID TuiDrawMessageBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption)
{
	TuiDrawBox(left, top, right, bottom, ColorMessageBox, LINE_STYLE_DOUBLE, pCaption);
}

VOID TuiDrawInfoBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption)
{
	TuiDrawBox(left, top, right, bottom, ColorInfoBox, LINE_STYLE_SINGLE, pCaption);
}

VOID TuiDrawCriticalMessageBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption)
{
	TuiDrawBox(left, top, right, bottom, ColorCriticalMessageBox, LINE_STYLE_DOUBLE, pCaption);
}

VOID TuiDrawStatusBar(PCSTR pStatusText, PCSTR pAdditionalStatusText)
{
	UINT32 textPosition;
	
	TuiFillArea(0, ScreenHeight - 1, ScreenWidth, ScreenHeight - 1, ColorStatusBar, ' ');
	TuiDrawTextEx(0, ScreenHeight - 1, COLOR_DO_NOT_CARE, pStatusText);
	
	textPosition = ScreenWidth - strlen(pAdditionalStatusText) - 3;
	//TuiDrawTextEx(textPosition, ScreenHeight - 1, COLOR_DO_NOT_CARE, " ");
	TuiPutCharEx(textPosition, ScreenHeight - 1, COLOR_DO_NOT_CARE, LINE_VERTICAL);
	TuiDrawTextEx(textPosition + 2, ScreenHeight - 1, COLOR_DO_NOT_CARE, pAdditionalStatusText);
	
}

VOID TuiDrawButton(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption, BOOL isEnabled, BOOL isDefault, BOOL isSelected, BOOL isPressed)
{
	UINT32 textPositionX;
	UINT32 textPositionY;
	UINT8 buttonColor;
	
	if (isEnabled)
		buttonColor = ColorButtonNormal;
	else	
		buttonColor = ColorButtonDisabled;
	
	if (isEnabled)
	{
		if (isSelected)
			buttonColor = ColorButtonSelected;
		if (isPressed)
			buttonColor = ColorButtonPressed;		
	}

	TuiFillArea(left, top, right, bottom, buttonColor, ' ');
	
	if (isDefault)
	{
		TuiPutCharEx(left, textPositionY, COLOR_DO_NOT_CARE, '<');
		TuiPutCharEx(right, textPositionY, COLOR_DO_NOT_CARE, '>');
	}
	
	textPositionX = (left + right - strlen(pCaption)) / 2;
	textPositionY = (top + bottom) / 2;
	TuiDrawTextEx(textPositionX, textPositionY, COLOR_DO_NOT_CARE, pCaption);
	
	
	
	
}