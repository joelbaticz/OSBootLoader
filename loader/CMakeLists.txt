cmake_minimum_required(VERSION 3.10)
project(KLoader C ASM)

#----------------------------------
# COMMON OPTIONS
#----------------------------------

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./")
set(CMAKE_OUTPUT_FILE_FINAL "kldr.sys")
#set(CMAKE_ASM_COMPILER "c:/MinGW/bin/gcc.exe")
set(CMAKE_C_COMPILER "c:/MinGW/bin/gcc.exe")
enable_language(ASM)

message("Log: CMAKE_RUNTIME_OUTPUT_DIRECTORY=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

#----------------------------------
# SOURCE & BUILD DIRS
#----------------------------------

message("Log: CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("Log: CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")

#----------------------------------
# BUILD TYPE
#----------------------------------

set(BUILD_TYPE_DEBUG "BUILD_TYPE_DEBUG")
set(BUILD_TYPE_RELEASE "BUILD_TYPE_RELEASE")

set(BUILD_TYPE ${BUILD_TYPE_DEBUG} CACHE STRING "Select Build Type")
add_definitions(-D${BUILD_TYPE})

message("Log: BUILD_TYPE=${BUILD_TYPE}")

#----------------------------------
# DEBUG OPTIONS
#----------------------------------

set(BUILD_DEBUG_LEVEL_ALL "BUILD_DEBUG_LEVEL_ALL")
set(BUILD_DEBUG_LEVEL_TRACE "BUILD_DEBUG_LEVEL_WARNING")
set(BUILD_DEBUG_LEVEL_ERROR "BUILD_DEBUG_LEVEL_ERROR")

set(BUILD_DEBUG_LEVEL ${BUILD_DEBUG_LEVEL_ALL} CACHE STRING "Select Debug Level")
add_definitions(-D${BUILD_DEBUG_LEVEL})

message("Log: BUILD_DEBUG_LEVEL=${BUILD_DEBUG_LEVEL}")

#----------------------------------
# ARCH TYPES
#----------------------------------

set(ARCH_TYPE_X86_32 "ARCH_TYPE_X86_32")
set(ARCH_TYPE_X86_64 "ARCH_TYPE_X86_64")
set(ARCH_TYPE_ARM "ARCH_TYPE_ARM")
set(ARCH_TYPE_MIPS "ARCH_TYPE_MIPS")
set(ARCH_TYPE_POWERPC "ARCH_TYPE_POWERPC")

set(ARCH_TYPE ${ARCH_TYPE_X86_32} CACHE STRING "Select Architecture Type")
message("Log: ARCH_TYPE=${ARCH_TYPE}")
add_definitions(-D${ARCH_TYPE})

#----------------------------------
# MACHINE TYPES
#----------------------------------

set(MACHINE_TYPE_PC "MACHINE_TYPE_PC")
set(MACHINE_TYPE_XBOX "MACHINE_TYPE_XBOX")

set(MACHINE_TYPE ${MACHINE_TYPE_PC} CACHE STRING "Select Machine Type")
message("Log: MACHINE_TYPE=${MACHINE_TYPE}")
add_definitions(-D${MACHINE_TYPE})

#----------------------------------
# LOADER ENTRY
#----------------------------------

if(ARCH_TYPE STREQUAL ${ARCH_TYPE_X86_32})
    set(CMAKE_ENTRY_INPUT_FILE "./loader_entry/arch/x86-32/entry.S")
endif()
set(CMAKE_ENTRY_OUTPUT_FILE "entry")
set(CMAKE_ENTRY_OUTPUT_FILE_EXE "${CMAKE_ENTRY_OUTPUT_FILE}.exe")
set(CMAKE_ENTRY_OUTPUT_FILE_FINAL "entry.sy_")

add_executable(${CMAKE_ENTRY_OUTPUT_FILE} ${CMAKE_ENTRY_INPUT_FILE})
set_target_properties(${CMAKE_ENTRY_OUTPUT_FILE} PROPERTIES LINK_FLAGS "-std=c99 -nostdlib -s -T./loader_entry/arch/x86-32/link.ld")
add_custom_target(TARGET1 ALL DEPENDS ${CMAKE_ENTRY_OUTPUT_FILE}) 

set(CMAKE_OBJCOPY_COMMAND "objcopy -O binary -j .text ${CMAKE_ENTRY_OUTPUT_FILE_EXE} ${CMAKE_ENTRY_OUTPUT_FILE_FINAL}")
separate_arguments(CMAKE_OBJCOPY_COMMAND_SEPARATED WINDOWS_COMMAND ${CMAKE_OBJCOPY_COMMAND})

add_custom_command(
	WORKING_DIRECTORY	${CMAKE_CURRENT_SOURCE_DIR}
	COMMAND			${CMAKE_OBJCOPY_COMMAND_SEPARATED}
	DEPENDS			${CMAKE_ENTRY_OUTPUT_FILE}
	OUTPUT			${CMAKE_ENTRY_OUTPUT_FILE_FINAL}
	#TARGET			TARGET2
	COMMENT			"[${CMAKE_OBJCOPY_COMMAND}]")

add_custom_target(TARGET2 ALL DEPENDS ${CMAKE_ENTRY_OUTPUT_FILE_FINAL}) 

#----------------------------------
# LOADER MAIN
#----------------------------------

set(CMAKE_MAIN_INPUT_FILE "loader_main/loader.c")
set(CMAKE_MAIN_OUTPUT_FILE "loader")
set(CMAKE_MAIN_OUTPUT_FILE_FINAL "loader.sy_")

list(APPEND CMAKE_LOADER_SOURCE
	"${CMAKE_SOURCE_DIR}/loader_main/loader.c"
		

	"${CMAKE_SOURCE_DIR}/lib/crt/string.c"
	"${CMAKE_SOURCE_DIR}/lib/crt/stdio.c"
	"${CMAKE_SOURCE_DIR}/lib/crt/stdlib.c"
	
	"${CMAKE_SOURCE_DIR}/lib/build.c"
	"${CMAKE_SOURCE_DIR}/lib/cmdline.c"
	"${CMAKE_SOURCE_DIR}/lib/debug.c"

	"${CMAKE_SOURCE_DIR}/lib/machine.c"
	"${CMAKE_SOURCE_DIR}/lib/pc.c"	
	"${CMAKE_SOURCE_DIR}/lib/pcbios.c"
	"${CMAKE_SOURCE_DIR}/lib/pcio.c"
	"${CMAKE_SOURCE_DIR}/lib/pcconsole.c"
	"${CMAKE_SOURCE_DIR}/lib/pcutility.c"
	"${CMAKE_SOURCE_DIR}/lib/pcmemory.c"
	
	#"${CMAKE_SOURCE_DIR}/lib/xbox.c"
	#"${CMAKE_SOURCE_DIR}/lib/xboxbios.c"
	#"${CMAKE_SOURCE_DIR}/lib/xboxio.c"
	#"${CMAKE_SOURCE_DIR}/lib/xboxconsole.c"
	#"${CMAKE_SOURCE_DIR}/lib/xboxutility.c"
	
	"${CMAKE_SOURCE_DIR}/lib/ui.c"
	"${CMAKE_SOURCE_DIR}/lib/miniui.c"
	"${CMAKE_SOURCE_DIR}/lib/tui.c"
	
	"${CMAKE_SOURCE_DIR}/lib/mem.c"
)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${CMAKE_MAIN_OUTPUT_FILE} ${CMAKE_LOADER_SOURCE})
#set_target_properties(${CMAKE_MAIN_OUTPUT_FILE} PROPERTIES LINK_FLAGS "-masm=intel -ffreestanding --entry=_KLoaderMain -nostdlib -Ttext=0x10000")
set_target_properties(${CMAKE_MAIN_OUTPUT_FILE} PROPERTIES LINK_FLAGS "-masm=intel -ffreestanding --entry=_KLoaderMain -nostdlib -T./loader_main/link.ld")
add_custom_target(TARGET3 ALL DEPENDS ${CMAKE_MAIN_OUTPUT_FILE}) 

#----------------------------------
# LOADER RENAME PART
#----------------------------------

#set(RENAME_COMMAND_FULL "move /y ${CMAKE_MAIN_OUTPUT_FILE}.exe ${CMAKE_MAIN_OUTPUT_FILE_FINAL}")
set(RENAME_COMMAND_FULL "copy /y loader.exe loader.sy_")
separate_arguments(RENAME_COMMAND_FULL_SEPARATED WINDOWS_COMMAND ${RENAME_COMMAND_FULL})

add_custom_command(
	WORKING_DIRECTORY	${CMAKE_CURRENT_BINARY_DIR}
	COMMAND			${RENAME_COMMAND_FULL_SEPARATED} 
	DEPENDS			TARGET2 #${CMAKE_MAIN_OUTPUT_FILE}
	OUTPUT			${CMAKE_MAIN_OUTPUT_FILE_FINAL}
	#TARGET			TARGET4
	COMMENT			"EXECUTING: [${RENAME_COMMAND_FULL}]"
	)

add_custom_target(TARGET4 ALL DEPENDS ${CMAKE_MAIN_OUTPUT_FILE_FINAL})

#----------------------------------
# LOADER MERGE PART (ENTRY + MAIN)
#----------------------------------

set(COPY_COMMAND_FULL "copy /b /y ${CMAKE_ENTRY_OUTPUT_FILE_FINAL} + ${CMAKE_MAIN_OUTPUT_FILE_FINAL} ${CMAKE_OUTPUT_FILE_FINAL}")
separate_arguments(COPY_COMMAND_FULL_SEPARATED WINDOWS_COMMAND ${COPY_COMMAND_FULL})

add_custom_command(
	WORKING_DIRECTORY	${CMAKE_CURRENT_SOURCE_DIR}
	COMMAND			${COPY_COMMAND_FULL_SEPARATED} 
	DEPENDS			TARGET2 TARGET4
	OUTPUT			${CMAKE_OUTPUT_FILE_FINAL}
	#TARGET			TARGET5
	COMMENT			"EXECUTING: [${COPY_COMMAND_FULL}]"
	)

add_custom_target(TARGET5 ALL DEPENDS ${CMAKE_OUTPUT_FILE_FINAL})

#TARGET1 = entry.exe
#TARGET2 = entry.sy_
#TARGET3 = loader.exe
#TARGET4 = loader.sy_
#TARGET5 = kldr.sys

#add_dependencies(TARGET2 TARGET1)
#add_dependencies(TARGET4 TARGET3)
#add_dependencies(TARGET5 TARGET2)
#add_dependencies(TARGET5 TARGET4)

