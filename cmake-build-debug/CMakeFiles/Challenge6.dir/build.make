# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Challenge6.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Challenge6.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Challenge6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Challenge6.dir/flags.make

CMakeFiles/Challenge6.dir/library.c.o: CMakeFiles/Challenge6.dir/flags.make
CMakeFiles/Challenge6.dir/library.c.o: ../library.c
CMakeFiles/Challenge6.dir/library.c.o: CMakeFiles/Challenge6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Challenge6.dir/library.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Challenge6.dir/library.c.o -MF CMakeFiles/Challenge6.dir/library.c.o.d -o CMakeFiles/Challenge6.dir/library.c.o -c /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/library.c

CMakeFiles/Challenge6.dir/library.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Challenge6.dir/library.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/library.c > CMakeFiles/Challenge6.dir/library.c.i

CMakeFiles/Challenge6.dir/library.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Challenge6.dir/library.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/library.c -o CMakeFiles/Challenge6.dir/library.c.s

CMakeFiles/Challenge6.dir/simulator.c.o: CMakeFiles/Challenge6.dir/flags.make
CMakeFiles/Challenge6.dir/simulator.c.o: ../simulator.c
CMakeFiles/Challenge6.dir/simulator.c.o: CMakeFiles/Challenge6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Challenge6.dir/simulator.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Challenge6.dir/simulator.c.o -MF CMakeFiles/Challenge6.dir/simulator.c.o.d -o CMakeFiles/Challenge6.dir/simulator.c.o -c /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/simulator.c

CMakeFiles/Challenge6.dir/simulator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Challenge6.dir/simulator.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/simulator.c > CMakeFiles/Challenge6.dir/simulator.c.i

CMakeFiles/Challenge6.dir/simulator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Challenge6.dir/simulator.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/simulator.c -o CMakeFiles/Challenge6.dir/simulator.c.s

# Object files for target Challenge6
Challenge6_OBJECTS = \
"CMakeFiles/Challenge6.dir/library.c.o" \
"CMakeFiles/Challenge6.dir/simulator.c.o"

# External object files for target Challenge6
Challenge6_EXTERNAL_OBJECTS =

libChallenge6.so: CMakeFiles/Challenge6.dir/library.c.o
libChallenge6.so: CMakeFiles/Challenge6.dir/simulator.c.o
libChallenge6.so: CMakeFiles/Challenge6.dir/build.make
libChallenge6.so: CMakeFiles/Challenge6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C shared library libChallenge6.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Challenge6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Challenge6.dir/build: libChallenge6.so
.PHONY : CMakeFiles/Challenge6.dir/build

CMakeFiles/Challenge6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Challenge6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Challenge6.dir/clean

CMakeFiles/Challenge6.dir/depend:
	cd /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6 /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6 /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/cmake-build-debug /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/cmake-build-debug /mnt/c/Users/wilke/CLionProjects/cs3100/Challenge6/cmake-build-debug/CMakeFiles/Challenge6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Challenge6.dir/depend

