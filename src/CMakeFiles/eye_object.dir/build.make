# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/cmake-3.30.3-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.30.3-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ducndc/workspaces/virtual-assistant

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ducndc/workspaces/virtual-assistant

# Include any dependencies generated for this target.
include src/CMakeFiles/eye_object.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/eye_object.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/eye_object.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/eye_object.dir/flags.make

src/CMakeFiles/eye_object.dir/eye_object.cpp.o: src/CMakeFiles/eye_object.dir/flags.make
src/CMakeFiles/eye_object.dir/eye_object.cpp.o: src/eye_object.cpp
src/CMakeFiles/eye_object.dir/eye_object.cpp.o: src/CMakeFiles/eye_object.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ducndc/workspaces/virtual-assistant/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/eye_object.dir/eye_object.cpp.o"
	cd /home/ducndc/workspaces/virtual-assistant/src && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/eye_object.dir/eye_object.cpp.o -MF CMakeFiles/eye_object.dir/eye_object.cpp.o.d -o CMakeFiles/eye_object.dir/eye_object.cpp.o -c /home/ducndc/workspaces/virtual-assistant/src/eye_object.cpp

src/CMakeFiles/eye_object.dir/eye_object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/eye_object.dir/eye_object.cpp.i"
	cd /home/ducndc/workspaces/virtual-assistant/src && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ducndc/workspaces/virtual-assistant/src/eye_object.cpp > CMakeFiles/eye_object.dir/eye_object.cpp.i

src/CMakeFiles/eye_object.dir/eye_object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/eye_object.dir/eye_object.cpp.s"
	cd /home/ducndc/workspaces/virtual-assistant/src && /usr/lib/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ducndc/workspaces/virtual-assistant/src/eye_object.cpp -o CMakeFiles/eye_object.dir/eye_object.cpp.s

# Object files for target eye_object
eye_object_OBJECTS = \
"CMakeFiles/eye_object.dir/eye_object.cpp.o"

# External object files for target eye_object
eye_object_EXTERNAL_OBJECTS =

src/libeye_object.a: src/CMakeFiles/eye_object.dir/eye_object.cpp.o
src/libeye_object.a: src/CMakeFiles/eye_object.dir/build.make
src/libeye_object.a: src/CMakeFiles/eye_object.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ducndc/workspaces/virtual-assistant/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libeye_object.a"
	cd /home/ducndc/workspaces/virtual-assistant/src && $(CMAKE_COMMAND) -P CMakeFiles/eye_object.dir/cmake_clean_target.cmake
	cd /home/ducndc/workspaces/virtual-assistant/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eye_object.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/eye_object.dir/build: src/libeye_object.a
.PHONY : src/CMakeFiles/eye_object.dir/build

src/CMakeFiles/eye_object.dir/clean:
	cd /home/ducndc/workspaces/virtual-assistant/src && $(CMAKE_COMMAND) -P CMakeFiles/eye_object.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/eye_object.dir/clean

src/CMakeFiles/eye_object.dir/depend:
	cd /home/ducndc/workspaces/virtual-assistant && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ducndc/workspaces/virtual-assistant /home/ducndc/workspaces/virtual-assistant/src /home/ducndc/workspaces/virtual-assistant /home/ducndc/workspaces/virtual-assistant/src /home/ducndc/workspaces/virtual-assistant/src/CMakeFiles/eye_object.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/eye_object.dir/depend

