/*
  - Date:		2018-02-20
  - Author:		Joel
  - Purpose:	Loader debug implementation:
				Using the debug part of command-line options or using the options
				supplied via the BOOT.INI debug levels are set for different debug channels.
				Debug also provides functionality for displaying Tracing, Warning and Error
				information on the set debug ports.
*/

/* INCLUDES */
#include <kldr.h>

/* DEFINITIONS */
#define DEBUG_SERIAL_DEFAULT_BAUD_RATE	115200
#define DEBUG_SERIAL_DEFAULT_COM_PORT	0
#define DEBUG_SERIAL_DEFAULT_IRQ		0

/* GLOBALS */

INT8 DebugChannels[DEBUG_CHANNELS_COUNT];
INT8 DebugPorts;

INT8 DebugSerialConnectionComPort;
INT8 DebugSerialConnectionBaudRate;
INT8 DebugSerialConnectionIrq;

/* FUNCTIONS */
VOID DebugParseOptions(char* pDebugOptions)
{
	NOT_IMPLEMENTED;
}

VOID SetDebugPorts(INT8 NewDebugPorts)
{
	DebugPorts = NewDebugPorts;
}

VOID SetDebugLevelForChannel(INT8 DebugChannelNumber, INT8 NewDebugLevel)
{
	DebugChannels[DebugChannelNumber] = NewDebugLevel;
}

VOID SetDebugLevelForAllChannels(INT8 NewDebugLevel)
{
	for(size_t i = 0; i < DEBUG_CHANNELS_COUNT; i++)
	{
		SetDebugLevelForChannel(i, NewDebugLevel);
	}
}

VOID DebugInit(BOOL ProcessIniFileSettings)
{
	CHAR DebugOptions[256];
	PCHAR pDebugOptions = &DebugOptions[0];
	
	/* Set defaults */
	SetDebugPorts(DEBUG_PORT_SCREEN);
	
	#ifdef BUILD_DEBUG_LEVEL_ALL
		SetDebugLevelForAllChannels(DEBUG_LEVEL_TRACE | DEBUG_LEVEL_WARNING | DEBUG_LEVEL_ERROR);	
	#endif
	#ifdef BUILD_DEBUG_LEVEL_WARNING
		SetDebugLevelForAllChannels(DEBUG_LEVEL_WARNING | DEBUG_LEVEL_ERROR);	
	#endif
	#ifdef BUILD_DEBUG_LEVEL_ERROR
		SetDebugLevelForAllChannels(DEBUG_LEVEL_ERROR);	
	#endif
	
	if (!ProcessIniFileSettings)
	{
		/* Process Debug Options came through Command-line */	
		pDebugOptions = GetCommandLineOptions();
		if (pDebugOptions != NULL)
		{
			/* FIX ME! Not sure why, but we come here and since DebugHalt is implemented it hangs here */
			DebugParseOptions(pDebugOptions);
		}	
	}
	else
	{
		/* Process Debug Options came through the BOOT.INI file */
		NOT_IMPLEMENTED;
		
		PCHAR pIniSection;		
		//if (!IniFileOpenSection("KoreOS", pIniSection)) return;
		//if (!IniFileReadSectionByName(pIniSection, "DEBUG"), DebugOpions, sizeof(DebugOptions)) return;
		
	}
}

VOID DebugPutChar(CHAR ch)
{
	if (DebugPorts & DEBUG_PORT_SCREEN)
	{
		MachineConsolePutChar(ch);
	}
	if (DebugPorts & DEBUG_PORT_SERIAL)
	{
		//Needs init!
		//SerialPutChar(ch);
	}
	if (DebugPorts & DEBUG_PORT_BOSCH)
	{
		//Needs init!
		//BoschPutChar(ch);
	}	
}

VOID DebugPrintf(const char* Format, ...)
{
	CHAR numberBuffer[32] = "abcdefghijklm\0";
	
	
	
	va_list ap;
	size_t length;
	
	PCHAR pBuffer;// = buffer;
	CHAR buffer[256]= {0};
	
	for (int i = 0; i < sizeof(buffer) - 1; i++)
	{
		buffer[i] = '/';
 	}
	
	
	pBuffer = (char*) buffer;
	
//	size_t length = strlen(Format);
//	PCHAR pBuffer = (char*) Format;
	
	va_start(ap, Format);
	length = vsnprintf(buffer, sizeof(buffer), Format, ap);
	va_end(ap);
	
	
	
	//
	//length = 80;
	//
	
	// if (length = -1)
	// {
		// /* if the buffer was not enough to store the info */
		// length = sizeof(buffer);
		// buffer[length - 1] = '\0';
	// }

//	length = strlen(pBuffer);
	
	
	/* THIS IS THE WRONG LINE ???? */
	//if (length > 50) length = 50;
	//length = 5;
	
	
	/*
	pBuffer = (char*) buffer;
	
	length = 64;
	while (length--)
	{
		MyPutChar(*pBuffer);
		pBuffer++;
		
	}
	
	
	//MyPrintf(pBuffer);
	*/

	/*
	itoa(length, numberBuffer, 10);
	MyPrintf((char*) numberBuffer);
	
	length = strlen(pBuffer);
	itoa(length, numberBuffer, 10);
	MyPrintf((char*) numberBuffer);
	*/
	
	MyPrintf(pBuffer);
	
	//MachineDebugPrintf();  ???? Maybe not, because I have to specify which port I use
	
	
	
	
	
	
	
	//length+=10;
	
	
	
	/*
	while (length--)
	{
		MyPutChar(*pBuffer);
		pBuffer++;
		
	}
*/

	
}
	
	
VOID DebugPrintfWithAdditionalInfo(UINT32 DebugChannel, UINT32 DebugLevel, const char *File, UINT32 Line, const char *Format, ...)
{
	va_list ap;
	UINT32 length;
	
	CHAR buffer[256] = {0};
	PCHAR pBuffer = (char*) buffer;
	CHAR buffer2[32] = {0};
	PCHAR pBuffer2 = (char*) buffer2;
	
	/* Handle Debug Levels */
	if (DebugLevel == DEBUG_LEVEL_ERROR) strcpy(buffer, "ERROR ");
	else if (DebugLevel == DEBUG_LEVEL_WARNING) strcpy(buffer, "WARNING ");
	else if (DebugLevel == DEBUG_LEVEL_TRACE) strcpy(buffer, "TRACE ");
	
	/* Handle Debug Channels */
	if (DebugChannel == DEBUG_CHANNEL_NONE) strcat(buffer, "[None]"); 
	else if (DebugChannel == DEBUG_CHANNEL_UI) strcat(buffer, "[UI]");
	else if (DebugChannel == DEBUG_CHANNEL_MEMORY) strcat(buffer, "[Memory]");
	else if (DebugChannel == DEBUG_CHANNEL_FILESYSTEM) strcat(buffer, "[FileSystem]");
	else if (DebugChannel == DEBUG_CHANNEL_DISK) strcat(buffer, "[Disk]");
	else if (DebugChannel == DEBUG_CHANNEL_CACHE) strcat(buffer, "[Cache]");
	
	strcat(buffer, " - \"");
	
	strcat(buffer, File);
	
	strcat(buffer, "\" (");
	
	strcat(buffer, itoa(Line, pBuffer2, 10));
	
	strcat(buffer, ") ");
	
	length = strlen(buffer);
	
	va_start(ap, Format);
	length = vsnprintf(buffer + length, sizeof(buffer) - length, Format, ap);
	va_end(ap);
	
	MyPrintf(pBuffer);
	
}

VOID DebugPause()
{
	MachineUtilityPause();
}

VOID DebugHalt()
{
	MachineUtilityHalt();
}

	
