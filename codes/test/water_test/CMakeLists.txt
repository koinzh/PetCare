cmake_minimum_required(VERSION 3.0)
project(Water_test)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)
find_library(PIGPIO_LIBRARY pigpio /usr/local/lib)
find_library(PIGPIO_THREAD pthread /usr/local/lib)

include_directories(${CMAKE_SOURCE_DIR}/lib)

set(SOURCE_FILES
    ../main.cpp
     ../lib/water.cpp
     ..//lib/water.h
    
)

add_executable(Water_test ${SOURCE_FILES})
target_link_libraries(Water_test ${PIGPIO_LIBRARY} ${PIGPIO_THREAD} ${CMAKE_THREAD_LIBS_INIT})
