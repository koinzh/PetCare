cmake_minimum_required(VERSION 3.0)
project(SmartPet)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)
find_library(PIGPIO_LIBRARY pigpio /usr/local/lib)
find_library(PIGPIO_THREAD pthread /usr/local/lib)

include_directories(${CMAKE_SOURCE_DIR}/lib)

set(SOURCE_FILES
    ../main.cpp
     ../lib/motor.cpp
      ../lib/MotorController.h
       ../lib/sonic.cpp
        ../lib/UltrasonicSensor.h
         ../lib/weight.h
          ../lib/weight.cpp
    
)

add_executable(SmartPet ${SOURCE_FILES})
target_link_libraries(SmartPet ${PIGPIO_LIBRARY} ${PIGPIO_THREAD} ${CMAKE_THREAD_LIBS_INIT})
