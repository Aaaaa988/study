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
CMAKE_SOURCE_DIR = /home/vladimir/CLionProjects/Ruban/MultiMatrix

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vladimir/CLionProjects/Ruban/MultiMatrix/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MultiMatrix.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MultiMatrix.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MultiMatrix.dir/flags.make

CMakeFiles/MultiMatrix.dir/main.cpp.o: CMakeFiles/MultiMatrix.dir/flags.make
CMakeFiles/MultiMatrix.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vladimir/CLionProjects/Ruban/MultiMatrix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MultiMatrix.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MultiMatrix.dir/main.cpp.o -c /home/vladimir/CLionProjects/Ruban/MultiMatrix/main.cpp

CMakeFiles/MultiMatrix.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MultiMatrix.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vladimir/CLionProjects/Ruban/MultiMatrix/main.cpp > CMakeFiles/MultiMatrix.dir/main.cpp.i

CMakeFiles/MultiMatrix.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MultiMatrix.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vladimir/CLionProjects/Ruban/MultiMatrix/main.cpp -o CMakeFiles/MultiMatrix.dir/main.cpp.s

# Object files for target MultiMatrix
MultiMatrix_OBJECTS = \
"CMakeFiles/MultiMatrix.dir/main.cpp.o"

# External object files for target MultiMatrix
MultiMatrix_EXTERNAL_OBJECTS =

MultiMatrix: CMakeFiles/MultiMatrix.dir/main.cpp.o
MultiMatrix: CMakeFiles/MultiMatrix.dir/build.make
MultiMatrix: CMakeFiles/MultiMatrix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vladimir/CLionProjects/Ruban/MultiMatrix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MultiMatrix"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MultiMatrix.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MultiMatrix.dir/build: MultiMatrix

.PHONY : CMakeFiles/MultiMatrix.dir/build

CMakeFiles/MultiMatrix.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MultiMatrix.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MultiMatrix.dir/clean

CMakeFiles/MultiMatrix.dir/depend:
	cd /home/vladimir/CLionProjects/Ruban/MultiMatrix/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vladimir/CLionProjects/Ruban/MultiMatrix /home/vladimir/CLionProjects/Ruban/MultiMatrix /home/vladimir/CLionProjects/Ruban/MultiMatrix/cmake-build-debug /home/vladimir/CLionProjects/Ruban/MultiMatrix/cmake-build-debug /home/vladimir/CLionProjects/Ruban/MultiMatrix/cmake-build-debug/CMakeFiles/MultiMatrix.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MultiMatrix.dir/depend

