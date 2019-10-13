project(Elevator_System)
cmake_minimum_required(VERSION 3.7)
add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(sources src/elevator.cpp src/elevator_sim.cpp)

include_directories(include)
add_executable(elev_sys_sim ${sources})