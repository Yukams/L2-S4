# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/TP3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TP3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TP3.dir/flags.make

CMakeFiles/TP3.dir/Course_au_clavier.c.o: CMakeFiles/TP3.dir/flags.make
CMakeFiles/TP3.dir/Course_au_clavier.c.o: ../Course_au_clavier.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TP3.dir/Course_au_clavier.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TP3.dir/Course_au_clavier.c.o   -c "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/Course_au_clavier.c"

CMakeFiles/TP3.dir/Course_au_clavier.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TP3.dir/Course_au_clavier.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/Course_au_clavier.c" > CMakeFiles/TP3.dir/Course_au_clavier.c.i

CMakeFiles/TP3.dir/Course_au_clavier.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TP3.dir/Course_au_clavier.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/Course_au_clavier.c" -o CMakeFiles/TP3.dir/Course_au_clavier.c.s

CMakeFiles/TP3.dir/term_canon.c.o: CMakeFiles/TP3.dir/flags.make
CMakeFiles/TP3.dir/term_canon.c.o: ../term_canon.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TP3.dir/term_canon.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TP3.dir/term_canon.c.o   -c "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/term_canon.c"

CMakeFiles/TP3.dir/term_canon.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TP3.dir/term_canon.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/term_canon.c" > CMakeFiles/TP3.dir/term_canon.c.i

CMakeFiles/TP3.dir/term_canon.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TP3.dir/term_canon.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/term_canon.c" -o CMakeFiles/TP3.dir/term_canon.c.s

# Object files for target TP3
TP3_OBJECTS = \
"CMakeFiles/TP3.dir/Course_au_clavier.c.o" \
"CMakeFiles/TP3.dir/term_canon.c.o"

# External object files for target TP3
TP3_EXTERNAL_OBJECTS =

../TP3: CMakeFiles/TP3.dir/Course_au_clavier.c.o
../TP3: CMakeFiles/TP3.dir/term_canon.c.o
../TP3: CMakeFiles/TP3.dir/build.make
../TP3: CMakeFiles/TP3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ../TP3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TP3.dir/build: ../TP3

.PHONY : CMakeFiles/TP3.dir/build

CMakeFiles/TP3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TP3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TP3.dir/clean

CMakeFiles/TP3.dir/depend:
	cd "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3" "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3" "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/cmake-build-debug" "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/cmake-build-debug" "/Users/valentin/Library/Mobile Documents/com~apple~CloudDocs/Fac/L2/S4/Systemes/TP3/cmake-build-debug/CMakeFiles/TP3.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/TP3.dir/depend
