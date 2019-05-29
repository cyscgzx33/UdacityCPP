In this exercise, you will will write a `RoutePlanner::AddNeighbors` method to take each neighbor of the current node in the A\* search, set the neighbor's g-value, h-value, and parent, and add the neighbor to the open list. To do this, you will use the `RouteModel::Node::FindNeighbors()`, and the `CalculateHValue` method that you have written previously.

To complete this exercise:
1. Modify `route_planner.h` to include a private method declaration for the `AddNeighbors` method. This method should accept a pointer to a `RouteModel::Node` object as the argument, and since the method is just modifying the `RoutePlanner` instance variable `open_list`, the method can have `void` return type. 
2. In `route_planner.cpp` define the `AddNeighbors` method using the `FindNeighbors` and `CalculateHValue` methods. You can use the pseudocode below as a guideline:

> AddNeighbors(RouteModel::Node *current_node)
> 1. Call `FindNeighbors()` on `current_node` to populate the `current_node`'s `neighbors` vector.
> 2. For each `neighbor` in the `current_node`'s `neighbors`
>   1. Set the `neighbor`s `parent` to the `current_node`.
>   2. Set the `neighbor`'s `g_value` to the sum of the `current_node`'s `g_value` plus the distance from the `curent_node` to the `neighbor`.
>   3. Set the `neighbor`'s `h_value` using `CalculateHValue`
>   4. Push the `neighbor` to the back of the `open_list`.
>   5. Mark the `neighbor` as visited.

This exercise does not have any tests associated with it, but you will be completing A\* search in the next exercise, and the code will be tested with the results of `AStarSearch()`.