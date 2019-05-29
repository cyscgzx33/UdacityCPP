You are now read to begin filling out the `RoutePlanner` class, which will contain methods and data to perform the A\* search on the `RouteModel` data. A class stub and empty class constructor have been provided in the `route_planner.h` and `route_planner.cpp` files. In this exercise, you will be starting with the header file `route_planner.h`.


To complete this exercise:
1. Add the following private variables to the `RoutePlanner` class in `route_planer.h`:
  - A `RouteModel` reference `m_Model`. This will refer to the model that you will be performing A\* search on.
  - `RouteModel::Node` pointers `start_node` and `end_node`. These will point to the nodes in the model which are closest to our starting and ending points.
  - A float `distance`. This variable will hold the total distance for the route that A\* search finds from `start_node` to `end_node`.
2. Add the following public method to the `RoutePlanner` class in `route_planner.h`:
  - A `GetDistance()` method. This is a public getter method for the `distance` variable, and should just return `distance`. This method will later be used to print out the total distance from `main.cpp`.
3. Use an initializer list in the `RoutePlanner` constructor in `route_planner.cpp` to initialize the `m_Model` variable with the passed `RoutePlanner` reference `model`.

Note that this exercise has no tests associated with it, but there will be tests in future exercises using the `RoutePlanner` class.