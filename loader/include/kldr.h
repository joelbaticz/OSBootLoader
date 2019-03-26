/*
  - Date: 2018-01-01
  - Author: Joel
  - Purpose: General definitions for Loader
*/

#ifndef __KLDR_H
#define __KLDR_H

#define IN const
#define OUT

/* PUBLIC HEADERS */

#include <ktypes.h> //K Standard Types
#include <crt/string.h>
#include <crt/stdio.h>
#include <crt/stdlib.h>

/* INTERNAL HEADERS */

/* STATUS CODES */
#include <status.h>

/* BUILD */
#include <build.h>

/* COMMAND LINE */
#include <cmdline.h>

/* DEBUG */
#include <debug.h>

/* Memory */
/* It needs to be here, because the header files below are using it */
#include <mem.h> 

/* MACHINE & ARCH */
#include <machine.h>

#ifdef MACHINE_TYPE_PC
#include <pc.h>
#include <pcbios.h>
#include <pcio.h>
#include <pcconsole.h>
#include <pcutility.h>
#include <pcmemory.h>
//#include <pcsystem.h>
//#include <pcdisk.h>
#endif

#ifdef MACHINE_TYPE_XBOX
#include <xbox.h>
//#include <xboxio.h>
//#include <xboxsystem.h>
//#include <xboxdisk.h>
#endif


/* UI */
#include <ui.h>
#include <miniui.h>
#include <tui.h>
//#include <ui/uitext.h>
//#include <uivga.h>
//#include <uivesa.h>



/* File System */

/* Architecture specific includes */

#if defined(ARCH_TYPE_X86_32) || defined(ARCH_TYPE_X86_64)
    #include <arch/x86/common/def.S>
#endif

VOID __cdecl KLoaderMain(IN PCHAR pCommandLineOptions);
VOID MyPutChar(char chr);
void MyPrintf(char* str);

#endif /* __KLDR_H */

