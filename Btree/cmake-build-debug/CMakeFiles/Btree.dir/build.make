# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mac/wihow/code/pythonhwk/Btree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mac/wihow/code/pythonhwk/Btree/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Btree.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Btree.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Btree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Btree.dir/flags.make

CMakeFiles/Btree.dir/main.cpp.o: CMakeFiles/Btree.dir/flags.make
CMakeFiles/Btree.dir/main.cpp.o: ../main.cpp
CMakeFiles/Btree.dir/main.cpp.o: CMakeFiles/Btree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mac/wihow/code/pythonhwk/Btree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Btree.dir/main.cpp.o"
	/opt/homebrew/Cellar/gcc/11.3.0_2/bin/aarch64-apple-darwin21-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Btree.dir/main.cpp.o -MF CMakeFiles/Btree.dir/main.cpp.o.d -o CMakeFiles/Btree.dir/main.cpp.o -c /Users/mac/wihow/code/pythonhwk/Btree/main.cpp

CMakeFiles/Btree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Btree.dir/main.cpp.i"
	/opt/homebrew/Cellar/gcc/11.3.0_2/bin/aarch64-apple-darwin21-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mac/wihow/code/pythonhwk/Btree/main.cpp > CMakeFiles/Btree.dir/main.cpp.i

CMakeFiles/Btree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Btree.dir/main.cpp.s"
	/opt/homebrew/Cellar/gcc/11.3.0_2/bin/aarch64-apple-darwin21-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mac/wihow/code/pythonhwk/Btree/main.cpp -o CMakeFiles/Btree.dir/main.cpp.s

# Object files for target Btree
Btree_OBJECTS = \
"CMakeFiles/Btree.dir/main.cpp.o"

# External object files for target Btree
Btree_EXTERNAL_OBJECTS =

Btree: CMakeFiles/Btree.dir/main.cpp.o
Btree: CMakeFiles/Btree.dir/build.make
Btree: CMakeFiles/Btree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mac/wihow/code/pythonhwk/Btree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Btree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Btree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Btree.dir/build: Btree
.PHONY : CMakeFiles/Btree.dir/build

CMakeFiles/Btree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Btree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Btree.dir/clean

CMakeFiles/Btree.dir/depend:
	cd /Users/mac/wihow/code/pythonhwk/Btree/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mac/wihow/code/pythonhwk/Btree /Users/mac/wihow/code/pythonhwk/Btree /Users/mac/wihow/code/pythonhwk/Btree/cmake-build-debug /Users/mac/wihow/code/pythonhwk/Btree/cmake-build-debug /Users/mac/wihow/code/pythonhwk/Btree/cmake-build-debug/CMakeFiles/Btree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Btree.dir/depend

