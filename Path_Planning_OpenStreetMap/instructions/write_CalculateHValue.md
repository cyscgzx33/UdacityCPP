In this exercise, you will modify `route_planner.h` and `route_planner.cpp` to add a method `CalculateHValue`, which calculates the h-value for a given node. In this project, h-value will be computed as the distance from the node to the end_node.


To write this method, you can use the following steps:
1. Add a `CalculateHValue` declaration to the `RoutePlanner` class in `route_planner.h`. This method will only be used in the `RoutePlanner` class, so it can be a private method. `CalculateHValue` should accept a `const` pointer to a `RouteModel::Node` object, and it should return a `float`.
2. In `route_planner.cpp` define the `CalculateHValue` method. The method should return the distance from the passed argument to the `end_node`.

Note that since `CalculateHValue` is private, there will be no tests for this exercise. The code will be tested implicitly through public functions in later tests.