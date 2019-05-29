In the next exercise, you will write a method stub for the A\* search. Before that method can be written, you will need a way to reconstruct the final sequence of nodes found from the `start_node` to the `end_node`, so that the A\* search can store the sequence. The final sequence is reconstructed by starting with the last node that was found, and then iteratively traversing to the parent of that node and each previous node in the sequence until the starting node is reached. In this exercise, you will be writting a method `ConstructFinalPath` that takes a `RouteModel::Node` pointer and iteratively moves the sequence of parents, storing each node in the sequence, until the starting node is reached. 


To complete this exercise, you can use the following steps:
1. Add a `ConstructFinalPath` declaration to the `RoutePlanner` class in `route_planner.h`. This method will be called from the A\* search within the RoutePlanner class, so it can be a private method. `ConstructFinalPath` should accept the pointer `RouteModel::Node *current_node` as the argument, and it should return a vector of ``RouteModel::Node` objects.
2. In `route_planner.cpp` define the `ConstructFinalPath` method. The method should do the following:
  1. Initialize an empty vector `path_found` of `RouteModel::Node` objects and set the class variable `distance` to 0.
  2. Iterate through the node parents until a node with parent equal to `nullptr` is reached - this will be the start node, which has no parent. Each node in the iteration should be pushed to the `path_found` vector.
  3. To keep track of the total path distance, in each step of the iteration, add the distance between a node and its parent to the `distance` variable. 
  4. After the loop, scale the `distance` by multiplying by the model's scale: `m_Model.MetricScale()`. This is done since node coordinates are scaled down when they are stored in the model. They must be rescaled to get an accurate distance.
  5. Return the `path_found`.

Note that the path returned above is in reverse order, with the ending node at the beginning of the vector. This is fine, and is expected by the rendering code.

Note that this exercise has no tests. The `ConstructFinalPath` method will be tested in upcoming exercises as the A\* search methods are implemented.