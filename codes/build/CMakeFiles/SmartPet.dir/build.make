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
include CMakeFiles/SmartPet.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SmartPet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SmartPet.dir/flags.make

CMakeFiles/SmartPet.dir/main.cpp.o: CMakeFiles/SmartPet.dir/flags.make
CMakeFiles/SmartPet.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SmartPet.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SmartPet.dir/main.cpp.o -c /home/pi/Desktop/PetCare/codes/main.cpp

CMakeFiles/SmartPet.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SmartPet.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/main.cpp > CMakeFiles/SmartPet.dir/main.cpp.i

CMakeFiles/SmartPet.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SmartPet.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/main.cpp -o CMakeFiles/SmartPet.dir/main.cpp.s

CMakeFiles/SmartPet.dir/lib/SmartPet.cpp.o: CMakeFiles/SmartPet.dir/flags.make
CMakeFiles/SmartPet.dir/lib/SmartPet.cpp.o: ../lib/SmartPet.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SmartPet.dir/lib/SmartPet.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SmartPet.dir/lib/SmartPet.cpp.o -c /home/pi/Desktop/PetCare/codes/lib/SmartPet.cpp

CMakeFiles/SmartPet.dir/lib/SmartPet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SmartPet.dir/lib/SmartPet.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/lib/SmartPet.cpp > CMakeFiles/SmartPet.dir/lib/SmartPet.cpp.i

CMakeFiles/SmartPet.dir/lib/SmartPet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SmartPet.dir/lib/SmartPet.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/lib/SmartPet.cpp -o CMakeFiles/SmartPet.dir/lib/SmartPet.cpp.s

CMakeFiles/SmartPet.dir/lib/sonic.cpp.o: CMakeFiles/SmartPet.dir/flags.make
CMakeFiles/SmartPet.dir/lib/sonic.cpp.o: ../lib/sonic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SmartPet.dir/lib/sonic.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SmartPet.dir/lib/sonic.cpp.o -c /home/pi/Desktop/PetCare/codes/lib/sonic.cpp

CMakeFiles/SmartPet.dir/lib/sonic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SmartPet.dir/lib/sonic.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/lib/sonic.cpp > CMakeFiles/SmartPet.dir/lib/sonic.cpp.i

CMakeFiles/SmartPet.dir/lib/sonic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SmartPet.dir/lib/sonic.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/lib/sonic.cpp -o CMakeFiles/SmartPet.dir/lib/sonic.cpp.s

CMakeFiles/SmartPet.dir/lib/motor.cpp.o: CMakeFiles/SmartPet.dir/flags.make
CMakeFiles/SmartPet.dir/lib/motor.cpp.o: ../lib/motor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SmartPet.dir/lib/motor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SmartPet.dir/lib/motor.cpp.o -c /home/pi/Desktop/PetCare/codes/lib/motor.cpp

CMakeFiles/SmartPet.dir/lib/motor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SmartPet.dir/lib/motor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/lib/motor.cpp > CMakeFiles/SmartPet.dir/lib/motor.cpp.i

CMakeFiles/SmartPet.dir/lib/motor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SmartPet.dir/lib/motor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/lib/motor.cpp -o CMakeFiles/SmartPet.dir/lib/motor.cpp.s

CMakeFiles/SmartPet.dir/lib/weight.cpp.o: CMakeFiles/SmartPet.dir/flags.make
CMakeFiles/SmartPet.dir/lib/weight.cpp.o: ../lib/weight.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SmartPet.dir/lib/weight.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SmartPet.dir/lib/weight.cpp.o -c /home/pi/Desktop/PetCare/codes/lib/weight.cpp

CMakeFiles/SmartPet.dir/lib/weight.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SmartPet.dir/lib/weight.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/PetCare/codes/lib/weight.cpp > CMakeFiles/SmartPet.dir/lib/weight.cpp.i

CMakeFiles/SmartPet.dir/lib/weight.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SmartPet.dir/lib/weight.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/PetCare/codes/lib/weight.cpp -o CMakeFiles/SmartPet.dir/lib/weight.cpp.s

# Object files for target SmartPet
SmartPet_OBJECTS = \
"CMakeFiles/SmartPet.dir/main.cpp.o" \
"CMakeFiles/SmartPet.dir/lib/SmartPet.cpp.o" \
"CMakeFiles/SmartPet.dir/lib/sonic.cpp.o" \
"CMakeFiles/SmartPet.dir/lib/motor.cpp.o" \
"CMakeFiles/SmartPet.dir/lib/weight.cpp.o"

# External object files for target SmartPet
SmartPet_EXTERNAL_OBJECTS =

SmartPet: CMakeFiles/SmartPet.dir/main.cpp.o
SmartPet: CMakeFiles/SmartPet.dir/lib/SmartPet.cpp.o
SmartPet: CMakeFiles/SmartPet.dir/lib/sonic.cpp.o
SmartPet: CMakeFiles/SmartPet.dir/lib/motor.cpp.o
SmartPet: CMakeFiles/SmartPet.dir/lib/weight.cpp.o
SmartPet: CMakeFiles/SmartPet.dir/build.make
SmartPet: /home/pi/WiringPi/wiringPi/libwiringPi.so.2.70
SmartPet: CMakeFiles/SmartPet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/PetCare/codes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable SmartPet"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SmartPet.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SmartPet.dir/build: SmartPet

.PHONY : CMakeFiles/SmartPet.dir/build

CMakeFiles/SmartPet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SmartPet.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SmartPet.dir/clean

CMakeFiles/SmartPet.dir/depend:
	cd /home/pi/Desktop/PetCare/codes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/PetCare/codes /home/pi/Desktop/PetCare/codes /home/pi/Desktop/PetCare/codes/build /home/pi/Desktop/PetCare/codes/build /home/pi/Desktop/PetCare/codes/build/CMakeFiles/SmartPet.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SmartPet.dir/depend

