//TODO:
// - FIX X86 REGISTERS TO USE SEGMENT REGISTERS TOO USED FOR CALLBIOSINTERRUPT...
// - Implement a memory manager (it could allocate stuff at specific addresses from its heap 
// - Implement the Loader Object Manager that the drivers can use to register resource usage.
// - Implement "fake" storage and keyboard (video, mouse?) drivers. They would call a BIOS function to handle these things. 
// - Implement "fake" HAL for Loader. This mini version of "Hal" will be replaced by the real version that the kernel uses.
//   Most of the "fake" HAL functions will be recycled there.
//   Should it be able to handle real interrupts. Should it enable interrupt handling (System Clock???)
//   For the first half of boot (Loader) we cannot use DMA if we don't for example.
// - Separate Ui print functions from Debug print
// - Separate diffent levels in Debug (warning, error, trace)
// - Do box, frame, status bar, progress bar functions
// - Have simple ui functions for text, vga, vesa
// - Have most functions architecture independable (with plug-ins for different hardware) 
// - Remove 0x from hex print???
// - Get rid of magic numbers (use constants and defines instead)
//   Use Status Codes (ARC_STATUS etc.). KLOADER_STATUS status = KLOADER_STATUS_SUCCESS

//TODESIGN:
//- In essence if we were to load a driver to handle scsi for example, then the driver could have a table
//  where it stores the OS Function Call addresses. The Loader here could patch the right addresses.
//  The driver will call these addresses when it is doing a function call. This way the drivers don't need to
//  be updated to be able to use them as Loader Boot drivers.


#include <kldr.h> //KLoader System Headers (including K Standard Types)

PCHAR ptrVideo = (PCHAR)0xb8000;

VOID MyPutChar(char chr)
{
	if (chr == 0) chr='|';
	
	//if (chr)
	{
		*ptrVideo = chr;
		ptrVideo+=2;
	}
}

void MyPrintf(char* str)
{
	if (str)
	{
		while(str[0] != '\0')
		{
			*ptrVideo = *str;
			ptrVideo+=2;
			str++;
		}
	}
}

void clrscr()
{
	for (size_t i = 0; i < 80 * 25; i++)
	{
		*ptrVideo = ' ';
		ptrVideo++;
		*ptrVideo = 0x5e;
		ptrVideo++;
	}	
	ptrVideo = (PCHAR) 0xb8000;
}


//__attribute__ ((dllexport))
VOID __cdecl KLoaderMain(IN PCHAR pCommandLineOptions)
{
	clrscr();
	
	if (!MachineInit())
	{
		//MachineCriticalStop("Compatible processor is not present.");
		ERROR("Compatible processor is not present.");
		HALT;
	};
	
	CommandLineOptionsParse(pCommandLineOptions);
	
	DebugInit(FALSE); /* ProcessIniFileSettings = FALSE */

	TRACE("KLoaderMain called.");
	
	//PAUSE;
	
	BOOL doCompleteUiInit = TRUE;
	if (!UiInit(doCompleteUiInit)) /* doCompleteUiInit = FALSE */
	{
		//MachineCriticalStop("Ui cannot be initialized.");
		ERROR("Ui cannot be initialized.");
		HALT;
	};
	
	
	
	
	
	
	
	//LOADER OPTIONS AREA
	UiDrawBox(20, 10, 60, 15, 0x3b, LINE_STYLE_DOUBLE, "");
	UiDrawTextCenter(20, 10, 60, 14, COLOR_DO_NOT_CARE, "Please wait...");
	UiDrawStatusBar("Please wait...", "            ");
	
	
	
	if (!MemInit())
	{
		ERROR("Memory cannot be initialized.");
		HALT;
	}
	
	DisplayMemoryEntries();
	
	
	
	
	
	
	//MENU
	// UiDrawBox(25, 7, 55, 17, 0x1f, LINE_STYLE_DOUBLE, "  Loader Menu  ");
	// UiDrawTextCenter(20, 10, 60, 14, COLOR_DO_NOT_CARE, "Please wait...");
	// UiDrawStatusBar("Use the up and down arrow keys to select an option from the menu.", "            ");
	
	// UiDrawButton(5, 10, 25, 10, "Disabled", FALSE, FALSE, FALSE, FALSE);
	// UiDrawButton(30, 10, 55, 10, "Enabled", TRUE, FALSE, FALSE, FALSE);
	// UiDrawButton(5, 15, 25, 15, "Default", TRUE, TRUE, FALSE, FALSE);
	// UiDrawButton(30, 15, 55, 15, "Selected", TRUE, FALSE, TRUE, FALSE);
	// UiDrawButton(5, 20, 25, 20, "Disabled", FALSE, TRUE, TRUE, TRUE);
	// UiDrawButton(30, 20, 55, 20, "Pressed", TRUE, FALSE, FALSE, TRUE);
	
	
	
	//UiDrawMessageBox(5, 5, 25, 15, " MessageBox ");
	//UiDrawInfoBox(35, 5, 55, 15, " InfoBox ");
	//UiDrawCriticalMessageBox(5, 17, 40, 21, " CriticalBox ");
	
	//TRACE("YEEEEEEEEEEEE");
	//LOADER OPTIONS AREA - END	
	
	//InitializeMemMan();
	//MemMan is available. Entire pages, aligned blocks from heap are possible to be allocated. Uses Bios 820h to query memory;
	
	//InitializeIoMan();
	//Estabilishes boot path, queries bios devices, gets ready the file system
	
	//Return to REAL MODE
	//Actually never return since it would halt anyways...
	
	HALT;
}


/*
__attribute__ ((dllexport)) uint32_t __cdecl GetSystemTime()
{	
}

__attribute__ ((dllexport)) VOID __cdecl SetSystemTime(uint32_t NewTime)
{	
}
*/