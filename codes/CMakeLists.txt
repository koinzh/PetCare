cmake_minimum_required(VERSION 3.0)
project(PetCare)

set(CMAKE_CXX_STANDARD 11)
set(LINKSDK_DIR "${CMAKE_SOURCE_DIR}/external/LinkSDK")


execute_process(
    COMMAND make
    WORKING_DIRECTORY ${LINKSDK_DIR}
    RESULT_VARIABLE MAKE_RESULT
)

if(NOT MAKE_RESULT EQUAL "0")
    message(FATAL_ERROR "Building LinkSDK failed with ${MAKE_RESULT}")
endif()

include_directories(${LINKSDK_DIR}/output/include)

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
          ../lib/IOTConnect.h
          ../lib/IOTConnect.cpp
    
)

add_library(link_sdk STATIC IMPORTED)
set_property(TARGET link_sdk PROPERTY IMPORTED_LOCATION ${LINKSDK_DIR}/output/lib/libaiot.a)

add_executable(PetCare ${SOURCE_FILES})
target_link_libraries(PetCare link_sdk)
target_link_libraries(PetCare ${PIGPIO_LIBRARY} ${PIGPIO_THREAD} ${CMAKE_THREAD_LIBS_INIT})
