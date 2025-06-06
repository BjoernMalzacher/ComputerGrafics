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
CMAKE_SOURCE_DIR = /home/malzacher/ComputerGrafics/assignment_3/viewer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/malzacher/ComputerGrafics/assignment_3/viewer

# Include any dependencies generated for this target.
include CMakeFiles/viewer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/viewer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/viewer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/viewer.dir/flags.make

CMakeFiles/viewer.dir/viewer.cc.o: CMakeFiles/viewer.dir/flags.make
CMakeFiles/viewer.dir/viewer.cc.o: viewer.cc
CMakeFiles/viewer.dir/viewer.cc.o: CMakeFiles/viewer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/malzacher/ComputerGrafics/assignment_3/viewer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/viewer.dir/viewer.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/viewer.dir/viewer.cc.o -MF CMakeFiles/viewer.dir/viewer.cc.o.d -o CMakeFiles/viewer.dir/viewer.cc.o -c /home/malzacher/ComputerGrafics/assignment_3/viewer/viewer.cc

CMakeFiles/viewer.dir/viewer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewer.dir/viewer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/malzacher/ComputerGrafics/assignment_3/viewer/viewer.cc > CMakeFiles/viewer.dir/viewer.cc.i

CMakeFiles/viewer.dir/viewer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewer.dir/viewer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/malzacher/ComputerGrafics/assignment_3/viewer/viewer.cc -o CMakeFiles/viewer.dir/viewer.cc.s

CMakeFiles/viewer.dir/wavefront.cc.o: CMakeFiles/viewer.dir/flags.make
CMakeFiles/viewer.dir/wavefront.cc.o: wavefront.cc
CMakeFiles/viewer.dir/wavefront.cc.o: CMakeFiles/viewer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/malzacher/ComputerGrafics/assignment_3/viewer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/viewer.dir/wavefront.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/viewer.dir/wavefront.cc.o -MF CMakeFiles/viewer.dir/wavefront.cc.o.d -o CMakeFiles/viewer.dir/wavefront.cc.o -c /home/malzacher/ComputerGrafics/assignment_3/viewer/wavefront.cc

CMakeFiles/viewer.dir/wavefront.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewer.dir/wavefront.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/malzacher/ComputerGrafics/assignment_3/viewer/wavefront.cc > CMakeFiles/viewer.dir/wavefront.cc.i

CMakeFiles/viewer.dir/wavefront.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewer.dir/wavefront.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/malzacher/ComputerGrafics/assignment_3/viewer/wavefront.cc -o CMakeFiles/viewer.dir/wavefront.cc.s

# Object files for target viewer
viewer_OBJECTS = \
"CMakeFiles/viewer.dir/viewer.cc.o" \
"CMakeFiles/viewer.dir/wavefront.cc.o"

# External object files for target viewer
viewer_EXTERNAL_OBJECTS =

viewer: CMakeFiles/viewer.dir/viewer.cc.o
viewer: CMakeFiles/viewer.dir/wavefront.cc.o
viewer: CMakeFiles/viewer.dir/build.make
viewer: CMakeFiles/viewer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/malzacher/ComputerGrafics/assignment_3/viewer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable viewer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/viewer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/viewer.dir/build: viewer
.PHONY : CMakeFiles/viewer.dir/build

CMakeFiles/viewer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/viewer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/viewer.dir/clean

CMakeFiles/viewer.dir/depend:
	cd /home/malzacher/ComputerGrafics/assignment_3/viewer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/malzacher/ComputerGrafics/assignment_3/viewer /home/malzacher/ComputerGrafics/assignment_3/viewer /home/malzacher/ComputerGrafics/assignment_3/viewer /home/malzacher/ComputerGrafics/assignment_3/viewer /home/malzacher/ComputerGrafics/assignment_3/viewer/CMakeFiles/viewer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/viewer.dir/depend

