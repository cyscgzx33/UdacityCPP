In this exercise, you will will write a `RoutePlanner::NextNode` method which will sort the list of open nodes in the A\* search, return the node with the lowest f-value, and remove the node from the list of open nodes. As you continue to develop your project, it will be easier to store the open list in the class as a vector of pointers to `RouteModel::Node` objects, so you will do that in this exercise as well.

To complete this exercise:
1. In the `RoutePlanner` class in `route_planner.h`, add a private class member variable `open_list`. The `open_list` should be a vector of `RouteModel::Node` pointers.  
2. Modify `route_planner.h` to include a private function declaration for the `NextNode` method. Since the method is just modifying the `open_list` and returning a pointer to a node, `NextNode` does not need any arguments. The method should return a pointer to a `RouteModel::Node` object.
3. In `route_planner.cpp` define the `NextNode` method. This method should:
  1. Sort the `open_list` according to the f-value, which is the sum of a node's h-value and g-value. 
  2. Create a pointer copy of the pointer to the node with the lowest f-value.
  3. Erase that node pointer from `open_list`.
  4. Return the pointer copy.

Since the `NextNode` method is private, there will not be any tests for this exercise. You will be able to test that the method is working with your A\* implementation in upcoming exercises.