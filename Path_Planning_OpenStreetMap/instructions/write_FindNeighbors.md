In this exercise, modify `route_model.h` and `route_model.cpp` to add a `RouteModel::Node` method `FindNeighbors`. The goal of `FindNeighbors` is to populate the `neighbors` vector of the current `Node` object (the vector `this->neighbors`). This vector should contain the closest neighbor from each road that `this` belongs to. Since `FindNeighbors` operates on the current `Node` and modifies the `Node` data, it does not need any arguments and can have return type `void`.

To write this method, you can use the following steps:
1. Add a public `FindNeighbors` declaration to the `RouteModel::Node` class in `route_model.h`. This method will be called from `route_planner.cpp`, so the method needs to be public. `FindNeighbors` should take no arguments and have `void` return type.
2. In `route_model.cpp` define the `FindNeighbors` method.
3. With the `FindNeighbors` method, for each road reference `&road` in the vector `parent_model->node_to_road[this->index]`, `FindNeighbors` should use the `FindNeighbor` method to create a pointer of `RouteModel::Node* ` type. 
4. If that pointer is not a `nullptr`, push the pointer to the back of `this->neighbors`. 