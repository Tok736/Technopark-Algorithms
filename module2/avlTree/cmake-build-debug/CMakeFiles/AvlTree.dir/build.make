# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /snap/clion/97/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/97/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AvlTree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AvlTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AvlTree.dir/flags.make

CMakeFiles/AvlTree.dir/main.cpp.o: CMakeFiles/AvlTree.dir/flags.make
CMakeFiles/AvlTree.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AvlTree.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AvlTree.dir/main.cpp.o -c /home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree/main.cpp

CMakeFiles/AvlTree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AvlTree.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree/main.cpp > CMakeFiles/AvlTree.dir/main.cpp.i

CMakeFiles/AvlTree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AvlTree.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree/main.cpp -o CMakeFiles/AvlTree.dir/main.cpp.s

# Object files for target AvlTree
AvlTree_OBJECTS = \
"CMakeFiles/AvlTree.dir/main.cpp.o"

# External object files for target AvlTree
AvlTree_EXTERNAL_OBJECTS =

AvlTree: CMakeFiles/AvlTree.dir/main.cpp.o
AvlTree: CMakeFiles/AvlTree.dir/build.make
AvlTree: CMakeFiles/AvlTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AvlTree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AvlTree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AvlTree.dir/build: AvlTree

.PHONY : CMakeFiles/AvlTree.dir/build

CMakeFiles/AvlTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AvlTree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AvlTree.dir/clean

CMakeFiles/AvlTree.dir/depend:
	cd /home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree /home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree /home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree/cmake-build-debug /home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree/cmake-build-debug /home/kotik/Education/technoPark/Technopark-Algorithms/module2/avlTree/cmake-build-debug/CMakeFiles/AvlTree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AvlTree.dir/depend

