# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/vladimir/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.6262.62/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/vladimir/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.6262.62/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vladimir/CLionProjects/Ruban/Backpack

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vladimir/CLionProjects/Ruban/Backpack/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Backpack.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Backpack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Backpack.dir/flags.make

CMakeFiles/Backpack.dir/main.cpp.o: CMakeFiles/Backpack.dir/flags.make
CMakeFiles/Backpack.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladimir/CLionProjects/Ruban/Backpack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Backpack.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Backpack.dir/main.cpp.o -c /home/vladimir/CLionProjects/Ruban/Backpack/main.cpp

CMakeFiles/Backpack.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Backpack.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vladimir/CLionProjects/Ruban/Backpack/main.cpp > CMakeFiles/Backpack.dir/main.cpp.i

CMakeFiles/Backpack.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Backpack.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vladimir/CLionProjects/Ruban/Backpack/main.cpp -o CMakeFiles/Backpack.dir/main.cpp.s

# Object files for target Backpack
Backpack_OBJECTS = \
"CMakeFiles/Backpack.dir/main.cpp.o"

# External object files for target Backpack
Backpack_EXTERNAL_OBJECTS =

Backpack: CMakeFiles/Backpack.dir/main.cpp.o
Backpack: CMakeFiles/Backpack.dir/build.make
Backpack: CMakeFiles/Backpack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vladimir/CLionProjects/Ruban/Backpack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Backpack"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Backpack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Backpack.dir/build: Backpack

.PHONY : CMakeFiles/Backpack.dir/build

CMakeFiles/Backpack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Backpack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Backpack.dir/clean

CMakeFiles/Backpack.dir/depend:
	cd /home/vladimir/CLionProjects/Ruban/Backpack/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vladimir/CLionProjects/Ruban/Backpack /home/vladimir/CLionProjects/Ruban/Backpack /home/vladimir/CLionProjects/Ruban/Backpack/cmake-build-debug /home/vladimir/CLionProjects/Ruban/Backpack/cmake-build-debug /home/vladimir/CLionProjects/Ruban/Backpack/cmake-build-debug/CMakeFiles/Backpack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Backpack.dir/depend

