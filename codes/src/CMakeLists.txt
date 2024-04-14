cmake_minimum_required(VERSION 3.0)
project(PetCare)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)
find_library(PIGPIO_LIBRARY pigpio /usr/local/lib)
find_library(PIGPIO_THREAD pthread /usr/local/lib)

include_directories(${CMAKE_SOURCE_DIR}/lib)

set(SOURCE_FILES
    ../src/main.cpp
     ../lib/motor.cpp
      ../lib/motor.h
       ../lib/sonic.cpp
        ../lib/sonic.h
         ../lib/weight.h
          ../lib/weight.cpp
          ../lib/water.h
          ../lib/water.cpp
    
)

add_executable(PetCare ${SOURCE_FILES})
target_link_libraries(PetCare ${PIGPIO_LIBRARY} ${PIGPIO_THREAD} ${CMAKE_THREAD_LIBS_INIT})
