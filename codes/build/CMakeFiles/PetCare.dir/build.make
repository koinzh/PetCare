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
CMAKE_SOURCE_DIR = /home/pi/Desktop/PetCare/codes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Desktop/PetCare/codes/build

# Include any dependencies generated for this target.
include CMakeFiles/PetCare.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PetCare.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PetCare.dir/flags.make

CMakeFiles/PetCare.dir/src/main.cpp.o: CMakeFiles/PetCare.dir/flags.make
CMakeFiles/PetCare.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PetCare.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PetCare.dir/src/main.cpp.o -c /home/pi/Desktop/PetCare/codes/src/main.cpp

CMakeFiles/PetCare.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PetCare.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/src/main.cpp > CMakeFiles/PetCare.dir/src/main.cpp.i

CMakeFiles/PetCare.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PetCare.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/src/main.cpp -o CMakeFiles/PetCare.dir/src/main.cpp.s

CMakeFiles/PetCare.dir/lib/motor.cpp.o: CMakeFiles/PetCare.dir/flags.make
CMakeFiles/PetCare.dir/lib/motor.cpp.o: ../lib/motor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PetCare.dir/lib/motor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PetCare.dir/lib/motor.cpp.o -c /home/pi/Desktop/PetCare/codes/lib/motor.cpp

CMakeFiles/PetCare.dir/lib/motor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PetCare.dir/lib/motor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/lib/motor.cpp > CMakeFiles/PetCare.dir/lib/motor.cpp.i

CMakeFiles/PetCare.dir/lib/motor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PetCare.dir/lib/motor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/lib/motor.cpp -o CMakeFiles/PetCare.dir/lib/motor.cpp.s

CMakeFiles/PetCare.dir/lib/sonic.cpp.o: CMakeFiles/PetCare.dir/flags.make
CMakeFiles/PetCare.dir/lib/sonic.cpp.o: ../lib/sonic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PetCare.dir/lib/sonic.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PetCare.dir/lib/sonic.cpp.o -c /home/pi/Desktop/PetCare/codes/lib/sonic.cpp

CMakeFiles/PetCare.dir/lib/sonic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PetCare.dir/lib/sonic.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/lib/sonic.cpp > CMakeFiles/PetCare.dir/lib/sonic.cpp.i

CMakeFiles/PetCare.dir/lib/sonic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PetCare.dir/lib/sonic.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/lib/sonic.cpp -o CMakeFiles/PetCare.dir/lib/sonic.cpp.s

CMakeFiles/PetCare.dir/lib/weight.cpp.o: CMakeFiles/PetCare.dir/flags.make
CMakeFiles/PetCare.dir/lib/weight.cpp.o: ../lib/weight.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PetCare.dir/lib/weight.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PetCare.dir/lib/weight.cpp.o -c /home/pi/Desktop/PetCare/codes/lib/weight.cpp

CMakeFiles/PetCare.dir/lib/weight.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PetCare.dir/lib/weight.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/lib/weight.cpp > CMakeFiles/PetCare.dir/lib/weight.cpp.i

CMakeFiles/PetCare.dir/lib/weight.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PetCare.dir/lib/weight.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/lib/weight.cpp -o CMakeFiles/PetCare.dir/lib/weight.cpp.s

CMakeFiles/PetCare.dir/lib/water.cpp.o: CMakeFiles/PetCare.dir/flags.make
CMakeFiles/PetCare.dir/lib/water.cpp.o: ../lib/water.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/PetCare.dir/lib/water.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PetCare.dir/lib/water.cpp.o -c /home/pi/Desktop/PetCare/codes/lib/water.cpp

CMakeFiles/PetCare.dir/lib/water.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PetCare.dir/lib/water.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/lib/water.cpp > CMakeFiles/PetCare.dir/lib/water.cpp.i

CMakeFiles/PetCare.dir/lib/water.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PetCare.dir/lib/water.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/lib/water.cpp -o CMakeFiles/PetCare.dir/lib/water.cpp.s

CMakeFiles/PetCare.dir/lib/IOTConnect.cpp.o: CMakeFiles/PetCare.dir/flags.make
CMakeFiles/PetCare.dir/lib/IOTConnect.cpp.o: ../lib/IOTConnect.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/PetCare.dir/lib/IOTConnect.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PetCare.dir/lib/IOTConnect.cpp.o -c /home/pi/Desktop/PetCare/codes/lib/IOTConnect.cpp

CMakeFiles/PetCare.dir/lib/IOTConnect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PetCare.dir/lib/IOTConnect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/lib/IOTConnect.cpp > CMakeFiles/PetCare.dir/lib/IOTConnect.cpp.i

CMakeFiles/PetCare.dir/lib/IOTConnect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PetCare.dir/lib/IOTConnect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/lib/IOTConnect.cpp -o CMakeFiles/PetCare.dir/lib/IOTConnect.cpp.s

# Object files for target PetCare
PetCare_OBJECTS = \
"CMakeFiles/PetCare.dir/src/main.cpp.o" \
"CMakeFiles/PetCare.dir/lib/motor.cpp.o" \
"CMakeFiles/PetCare.dir/lib/sonic.cpp.o" \
"CMakeFiles/PetCare.dir/lib/weight.cpp.o" \
"CMakeFiles/PetCare.dir/lib/water.cpp.o" \
"CMakeFiles/PetCare.dir/lib/IOTConnect.cpp.o"

# External object files for target PetCare
PetCare_EXTERNAL_OBJECTS =

PetCare: CMakeFiles/PetCare.dir/src/main.cpp.o
PetCare: CMakeFiles/PetCare.dir/lib/motor.cpp.o
PetCare: CMakeFiles/PetCare.dir/lib/sonic.cpp.o
PetCare: CMakeFiles/PetCare.dir/lib/weight.cpp.o
PetCare: CMakeFiles/PetCare.dir/lib/water.cpp.o
PetCare: CMakeFiles/PetCare.dir/lib/IOTConnect.cpp.o
PetCare: CMakeFiles/PetCare.dir/build.make
PetCare: ../external/LinkSDK/output/lib/libaiot.a
PetCare: /usr/lib/libpigpio.so
PetCare: /usr/lib/aarch64-linux-gnu/libpthread.so
PetCare: CMakeFiles/PetCare.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable PetCare"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PetCare.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PetCare.dir/build: PetCare

.PHONY : CMakeFiles/PetCare.dir/build

CMakeFiles/PetCare.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PetCare.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PetCare.dir/clean

CMakeFiles/PetCare.dir/depend:
	cd /home/pi/Desktop/PetCare/codes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/PetCare/codes /home/pi/Desktop/PetCare/codes /home/pi/Desktop/PetCare/codes/build /home/pi/Desktop/PetCare/codes/build /home/pi/Desktop/PetCare/codes/build/CMakeFiles/PetCare.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PetCare.dir/depend

