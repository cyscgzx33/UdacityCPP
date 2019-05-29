In this exercise, modify `route_model.h` and `route_model.cpp` to add a `RouteModel::Node` method `FindNeighbor`. The goal of `FindNeighbor` is to return a pointer to the closest unvisited node from a vector of node indices, where the distance is measured to the current node (`this`).


To write this method, you can use the following steps:
1. Add a `FindNeighbor` declaration to the `RouteModel::Node` class in `route_model.h`. This method will only be used later in another `RouteModel::Node` method to find the closest node in each `Road` containing the current node, so `FindNeighbor` can be a private method. `FindNeighbor` should accept a `vector<int> node_indices` argument and return a pointer to a node: `RouteModel::Node*` type.
2. In `route_model.cpp` define an empty `FindNeighbor` method. At this step, compile the code using `make` to check that your method declaration and empty method definiton have matching signatures.
3. Within the `FindNeighbor` method, loop through the `node_indices` vector to find the closest unvisited node. To do this, start with a pointer `Node *closest_node = nullptr`, and then update `closest_node` as you find closer nodes in the loop. The following will be useful:
  - For each index in the loop, you can retrieve the `Node` object with `parent_model->SNodes()[index]`.
  - For each retrieved `Node` in the loop, you should check that the node has not been visted (`!node.visited`) _and_ that the distance to `this` is nonzero. In other words, you want the closest unvisted node that is not the current node.
  - The `RouteModel::Node::distance` method can be used to find the distance between two nodes.

Pseudocode for the exercise is given below:

>The FindNeighbor method, given a `vector<int> node_indices`:
>
>1. Create a pointer `Node *closest_node = nullptr`
>2. Declare a temporary Node variable `node`
>
>3. For each `node_index` in `node_indices`
        
>  1. Set `node` equal to the `parent_model->SNodes()[node_index]`
>  2. If the distance from `this` to `node` is nonzero, _and_ the `node` has not been visited:
>
>    1. If the `closest_node` equals `nullptr`, _or_ the distance from `this` to `node` is less than the distance from `this` to `*closest_node`:
>      - Set `closest_node` to point to the address of `parent_model->SNodes()[node_index]`.
>4. Finally, return the `closest_node`.


Note that there will be no tests for this method. The method is private, and will be used as a helper function in a public method in the next exercise.