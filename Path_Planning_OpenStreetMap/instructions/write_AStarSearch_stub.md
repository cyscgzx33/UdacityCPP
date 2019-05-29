In this exercise, you will modify `route_planner.h`, `route_planner.cpp`, `main.cpp`, and `render.cpp` to add a method `AStarSearch`, which will eventually become the search from `start_node` to `end_node`. In this exercise, you will only implement a basic version that returns a direct path between those two nodes. When you are done with this exercise, running the code should render a map with a direct path between the start and end nodes.


To complete this exercise, you can use the following steps:
1. Add a `AStarSearch` declaration to the `RoutePlanner` class in `route_planner.h`. This method will be called from `main.cpp`, so it must be a public method. `AStarSearch` will use the `start_node` and `end_node` class variables, and it will modify the `m_Model` class variable, so it does not need any arguments, and should have `void` return type.
2. In `route_planner.cpp` define the `AStarSearch` method. The method should do the following:
  1. Set the parent of `end_node` to the `start_node`.
  2. Set `m_Model.path` to the result of calling `ConstructFinalPath` on `end_node`.
3. In `main.cpp` call `AStarSearch` on the `RoutePlanner` object. This should happen just after the `RoutePlanner` object is defined, but before the `Render render{model}`. 
4. Also in `main.cpp` use the `GetDistance()` method of the `RoutePlanner` object to print the length of the path.
5. Uncomment the following lines in the `Render::Display` method in `render.cpp`. These lines will include the path in the rendered map:
```
    // DrawPath(surface);
    // DrawStartPosition(surface);   
    // DrawEndPosition(surface);
```