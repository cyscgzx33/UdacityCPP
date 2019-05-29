cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_COMPILER  "/usr/bin/g++-7")
set(CMAKE_CXX_FLAGS "-std=c++1z")

if(NOT TESTING)
    set(TESTING "notest")
endif()

message("TESTING = ${TESTING}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Use the CMakeLists.txt's parent-directory-name for the project's id/name
get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
project(${PROJECT_ID})

#
# Project Output Paths
#
set(MAINFOLDER ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${MAINFOLDER}/bin")
set(LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

#
# Locate Project Prerequisites
#
find_package(io2d REQUIRED)
find_package(Cairo)
find_package(GraphicsMagick)

#
# Add Build Targets
#
set(IO2D_WITHOUT_SAMPLES 1)
set(IO2D_WITHOUT_TESTS 1)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(thirdparty/pugixml)
add_subdirectory(thirdparty/googletest)
