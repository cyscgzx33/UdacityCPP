
# message("TESTING = ${TESTING}")

# Choose which test .cpp file based on the exercise.
if(${TESTING} STREQUAL "RouteModel")
    add_executable(test utest_route_model_class.cpp)
elseif(${TESTING} STREQUAL "RMNodeClass")
    add_executable(test utest_rm_node_class.cpp)
elseif(${TESTING} STREQUAL "RMSNodes")
    add_executable(test utest_rm_snodes.cpp)
elseif(${TESTING} STREQUAL "NodeDist")
    add_executable(test utest_rm_node_dist.cpp)
elseif(${TESTING} STREQUAL "NodeToRoad")
    add_executable(test utest_rm_hashmap.cpp)
elseif(${TESTING} STREQUAL "FindNeighbors")
    add_executable(test utest_rm_find_neighbors.cpp)
elseif(${TESTING} STREQUAL "FindClosest")
    add_executable(test utest_rm_find_closest_node.cpp)
elseif(${TESTING} STREQUAL "AStarStub")
    add_executable(test utest_rp_a_star_stub.cpp)
elseif(${TESTING} STREQUAL "AStarSearch")
    add_executable(test utest_rp_a_star_search.cpp)
else()
    # If the user calls CMake with no flags, don't compile any test files.
    add_executable(test)
endif()

target_link_libraries(test gtest_main route_planner pugixml)
add_test(NAME test COMMAND test)

unset(TESTING CACHE)
