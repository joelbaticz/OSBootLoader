# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader\build

# Utility rule file for TARGET5.

# Include the progress variables for this target.
include CMakeFiles/TARGET5.dir/progress.make

CMakeFiles/TARGET5: kldr.sys


kldr.sys:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "EXECUTING: [copy /b /y entry.sy_ + loader.sy_ kldr.sys]"
	cd /d C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader && copy /b /y entry.sy_ + loader.sy_ kldr.sys

TARGET5: CMakeFiles/TARGET5
TARGET5: kldr.sys
TARGET5: CMakeFiles/TARGET5.dir/build.make

.PHONY : TARGET5

# Rule to build all files generated by this target.
CMakeFiles/TARGET5.dir/build: TARGET5

.PHONY : CMakeFiles/TARGET5.dir/build

CMakeFiles/TARGET5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TARGET5.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TARGET5.dir/clean

CMakeFiles/TARGET5.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader\build C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader\build C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader\build\CMakeFiles\TARGET5.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TARGET5.dir/depend

