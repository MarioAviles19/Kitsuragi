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
CMAKE_SOURCE_DIR = /home/mario/Kitsuragi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mario/Kitsuragi/Build

# Include any dependencies generated for this target.
include CMakeFiles/kitsuragi.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/kitsuragi.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/kitsuragi.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kitsuragi.dir/flags.make

CMakeFiles/kitsuragi.dir/src/main.cpp.o: CMakeFiles/kitsuragi.dir/flags.make
CMakeFiles/kitsuragi.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/kitsuragi.dir/src/main.cpp.o: CMakeFiles/kitsuragi.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mario/Kitsuragi/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/kitsuragi.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/kitsuragi.dir/src/main.cpp.o -MF CMakeFiles/kitsuragi.dir/src/main.cpp.o.d -o CMakeFiles/kitsuragi.dir/src/main.cpp.o -c /home/mario/Kitsuragi/src/main.cpp

CMakeFiles/kitsuragi.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kitsuragi.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mario/Kitsuragi/src/main.cpp > CMakeFiles/kitsuragi.dir/src/main.cpp.i

CMakeFiles/kitsuragi.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kitsuragi.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mario/Kitsuragi/src/main.cpp -o CMakeFiles/kitsuragi.dir/src/main.cpp.s

# Object files for target kitsuragi
kitsuragi_OBJECTS = \
"CMakeFiles/kitsuragi.dir/src/main.cpp.o"

# External object files for target kitsuragi
kitsuragi_EXTERNAL_OBJECTS =

kitsuragi: CMakeFiles/kitsuragi.dir/src/main.cpp.o
kitsuragi: CMakeFiles/kitsuragi.dir/build.make
kitsuragi: CMakeFiles/kitsuragi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mario/Kitsuragi/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable kitsuragi"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kitsuragi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kitsuragi.dir/build: kitsuragi
.PHONY : CMakeFiles/kitsuragi.dir/build

CMakeFiles/kitsuragi.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kitsuragi.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kitsuragi.dir/clean

CMakeFiles/kitsuragi.dir/depend:
	cd /home/mario/Kitsuragi/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mario/Kitsuragi /home/mario/Kitsuragi /home/mario/Kitsuragi/Build /home/mario/Kitsuragi/Build /home/mario/Kitsuragi/Build/CMakeFiles/kitsuragi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kitsuragi.dir/depend
