# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/pi/Desktop/PetCare/codes/test/weight_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Desktop/PetCare/codes/test/weight_test/build

# Include any dependencies generated for this target.
include CMakeFiles/Weight_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Weight_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Weight_test.dir/flags.make

CMakeFiles/Weight_test.dir/main.cpp.o: CMakeFiles/Weight_test.dir/flags.make
CMakeFiles/Weight_test.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/test/weight_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Weight_test.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Weight_test.dir/main.cpp.o -c /home/pi/Desktop/PetCare/codes/test/weight_test/main.cpp

CMakeFiles/Weight_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Weight_test.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/test/weight_test/main.cpp > CMakeFiles/Weight_test.dir/main.cpp.i

CMakeFiles/Weight_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Weight_test.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/test/weight_test/main.cpp -o CMakeFiles/Weight_test.dir/main.cpp.s

CMakeFiles/Weight_test.dir/lib/weight.cpp.o: CMakeFiles/Weight_test.dir/flags.make
CMakeFiles/Weight_test.dir/lib/weight.cpp.o: ../lib/weight.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/test/weight_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Weight_test.dir/lib/weight.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Weight_test.dir/lib/weight.cpp.o -c /home/pi/Desktop/PetCare/codes/test/weight_test/lib/weight.cpp

CMakeFiles/Weight_test.dir/lib/weight.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Weight_test.dir/lib/weight.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/test/weight_test/lib/weight.cpp > CMakeFiles/Weight_test.dir/lib/weight.cpp.i

CMakeFiles/Weight_test.dir/lib/weight.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Weight_test.dir/lib/weight.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/test/weight_test/lib/weight.cpp -o CMakeFiles/Weight_test.dir/lib/weight.cpp.s

# Object files for target Weight_test
Weight_test_OBJECTS = \
"CMakeFiles/Weight_test.dir/main.cpp.o" \
"CMakeFiles/Weight_test.dir/lib/weight.cpp.o"

# External object files for target Weight_test
Weight_test_EXTERNAL_OBJECTS =

Weight_test: CMakeFiles/Weight_test.dir/main.cpp.o
Weight_test: CMakeFiles/Weight_test.dir/lib/weight.cpp.o
Weight_test: CMakeFiles/Weight_test.dir/build.make
Weight_test: /usr/lib/libpigpio.so
Weight_test: /usr/lib/aarch64-linux-gnu/libpthread.so
Weight_test: CMakeFiles/Weight_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/PetCare/codes/test/weight_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Weight_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Weight_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Weight_test.dir/build: Weight_test

.PHONY : CMakeFiles/Weight_test.dir/build

CMakeFiles/Weight_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Weight_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Weight_test.dir/clean

CMakeFiles/Weight_test.dir/depend:
	cd /home/pi/Desktop/PetCare/codes/test/weight_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/PetCare/codes/test/weight_test /home/pi/Desktop/PetCare/codes/test/weight_test /home/pi/Desktop/PetCare/codes/test/weight_test/build /home/pi/Desktop/PetCare/codes/test/weight_test/build /home/pi/Desktop/PetCare/codes/test/weight_test/build/CMakeFiles/Weight_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Weight_test.dir/depend
