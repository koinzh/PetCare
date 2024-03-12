cmake_minimum_required(VERSION 3.0)
project(SmartPet)


set(CMAKE_CXX_STANDARD 11)
#set(WiringPi_INCLUDE_DIR "/home/pi/WiringPi/WiringPi")
#set(WiringPi_LIBRARY "/home/pi/WiringPi/wiringPi/libwiringPi.so.2.70")


include_directories(${CMAKE_SOURCE_DIR}/lib)
set(SOURCE_FILES
    main.cpp
    ../lib/SmartPet.h
    ../lib/sonic.h
    ../lib/motor.h
    ../lib/SmartPet.cpp
    ../lib/sonic.cpp
    ../lib/motor.cpp
)

add_executable(SmartPet ${SOURCE_FILES})
#target_link_libraries(SmartPet ${WiringPi_LIBRARY})
find_package(Threads REQUIRED)
target_link_libraries(SmartPet Threads::Threads)

# Find pigpio library paths
find_path(PIGPIO_INCLUDE_DIR NAMES pigpio.h)
find_library(PIGPIO_LIBRARY NAMES pigpio)

# Include pigpio headers
include_directories(${PIGPIO_INCLUDE_DIR})

# Link pigpio library
target_link_libraries(SmartPet ${PIGPIO_LIBRARIES})