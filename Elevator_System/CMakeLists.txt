project(Elevator_System)
cmake_minimum_required(VERSION 3.7)
add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(sources src/elevator.cpp src/elevator_sim.cpp)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS} src)
include_directories(include)

#add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp)
add_executable(elev_sys_sim ${sources})
#string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
#target_link_libraries(SnakeGame ${SDL2_LIBRARIES})