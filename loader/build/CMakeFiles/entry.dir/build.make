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

# Include any dependencies generated for this target.
include CMakeFiles/entry.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/entry.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/entry.dir/flags.make

CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj: CMakeFiles/entry.dir/flags.make
CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj: ../loader_entry/arch/x86-32/entry.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building ASM object CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj"
	C:\MinGW\bin\gcc.exe $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles\entry.dir\loader_entry\arch\x86-32\entry.S.obj -c C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader\loader_entry\arch\x86-32\entry.S

CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj.requires:

.PHONY : CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj.requires

CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj.provides: CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj.requires
	$(MAKE) -f CMakeFiles\entry.dir\build.make CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj.provides.build
.PHONY : CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj.provides

CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj.provides.build: CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj


# Object files for target entry
entry_OBJECTS = \
"CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj"

# External object files for target entry
entry_EXTERNAL_OBJECTS =

../entry.exe: CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj
../entry.exe: CMakeFiles/entry.dir/build.make
../entry.exe: CMakeFiles/entry.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking ASM executable ..\entry.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\entry.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/entry.dir/build: ../entry.exe

.PHONY : CMakeFiles/entry.dir/build

CMakeFiles/entry.dir/requires: CMakeFiles/entry.dir/loader_entry/arch/x86-32/entry.S.obj.requires

.PHONY : CMakeFiles/entry.dir/requires

CMakeFiles/entry.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\entry.dir\cmake_clean.cmake
.PHONY : CMakeFiles/entry.dir/clean

CMakeFiles/entry.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader\build C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader\build C:\!PROGRAMMING\KOREOS\2018-10-16\src\boot\loader\build\CMakeFiles\entry.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/entry.dir/depend

