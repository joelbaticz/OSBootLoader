/*
  - Date: 2018-03-10
  - Author: Joel
  - Purpose: Definitions for PC Console functions
*/

/* GLOBAL FUNCTIONS */
VOID PcConsolePutChar(CHAR ch);
VOID PcConsoleWaitForKeyPress();
CHAR PcConsoleGetChar();
UINT8 PcConsoleDetectBestDisplayMode();
VOID PcConsoleSetDisplayMode(UINT8 requestedDisplayMode);
BOOL PcConsoleShowCursor(BOOL doShowCursor);
VOID PcConsoleGetCursorPosition(PUINT8 pX, PUINT8 pY);
VOID PcConsoleSetCursorPosition(UINT8 x, UINT8 y);
