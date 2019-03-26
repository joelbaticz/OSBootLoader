/*
  - Date: 2018-03-21
  - Author: Joel
  - Purpose: Mini UI definitions
*/

/* GLOBAL DEFINITIONS */
VOID MiniUiInit(UINT8 requestedDisplayMode);
VOID MiniUiUninit();

/* Standard drawing functions */
VOID MiniUiDrawText(PCSTR pText);
VOID MiniUiDrawTextEx(UINT32 x, UINT32 y, UINT8 colorAttribute, PCSTR pText);
VOID MiniUiFillArea(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, CHAR fillChar);
VOID MiniUiDrawFrame(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, UINT8 lineStyle);

/* Complex drawing functions - require other standard drawing functions */
VOID MiniUiDrawWelcomeScreen();

VOID MiniUiDrawBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, UINT8 colorAttribute, UINT8 lineStyle, PCSTR pCaption);
VOID MiniUiDrawMessageBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption);
VOID MiniUiDrawInfoBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption);
VOID MiniUiDrawCriticalMessageBox(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption);

VOID MiniUiDrawStatusBar(PCSTR pStatusText, PCSTR pAdditionalStatusText);
VOID MiniUiDrawButton(UINT32 left, UINT32 top, UINT32 right, UINT32 bottom, PCSTR pCaption, BOOL isEnabled, BOOL isDefault, BOOL isSelected, BOOL isPressed);