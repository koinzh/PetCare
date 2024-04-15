cmake_minimum_required(VERSION 3.0)
project(Weight_test)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)
find_library(PIGPIO_LIBRARY pigpio /usr/local/lib)
find_library(PIGPIO_THREAD pthread /usr/local/lib)

include_directories(${CMAKE_SOURCE_DIR}/lib)

set(SOURCE_FILES
    ../src/main.cpp
     ../lib/weight.cpp
     ../lib/weight.h
    
)

add_executable(Weight_test ${SOURCE_FILES})
target_link_libraries(Weight_test ${PIGPIO_LIBRARY} ${PIGPIO_THREAD} ${CMAKE_THREAD_LIBS_INIT})
