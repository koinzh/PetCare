cmake_minimum_required(VERSION 3.0)
project(SmartPet)


set(CMAKE_CXX_STANDARD 11)
set(WiringPi_INCLUDE_DIR "/home/pi/WiringPi/WiringPi")
set(WiringPi_LIBRARY "/home/pi/WiringPi/wiringPi/libwiringPi.so.2.70")
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



include_directories(${CMAKE_SOURCE_DIR}/lib)
set(SOURCE_FILES
    main.cpp
    ../lib/SmartPet.h
    ../lib/SmartPet.cpp


    
)
add_library(link_sdk STATIC IMPORTED)
set_property(TARGET link_sdk PROPERTY IMPORTED_LOCATION ${LINKSDK_DIR}/output/lib/libaiot.a)

add_executable(SmartPet ${SOURCE_FILES})
target_link_libraries(SmartPet link_sdk)
target_link_libraries(SmartPet ${WiringPi_LIBRARY})

find_package(Threads REQUIRED)
target_link_libraries(SmartPet Threads::Threads)
