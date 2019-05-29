Now that you have filled out the header of the `RoutePlanner` class, you can finish writing the constructor in `route_planner.cpp`. The constructor takes one `RouteModel` reference and four `floats` as arguments. The `RouteModel` reference should have been assigned to the `m_Model` variable in the previous exercise. In this exercise, the floats should be used to construct the `start_node` and `end_node` of your class. Follow the instructions below to do this.


To complete this exercise:
1. Within the body of the constructor:
  1. Scale the `float`s to percentages by multiplying each `float` by 0.01 and storing the result in the float variable. For example: `start_x *= 0.01;`
  2. Use the `m_Model.FindClosestNode` method to find the closest nodes to `(start_x, start_y)` and `(end_x, end_y)`. Store pointers to these nodes in the `start_node` and `end_node` class variables.

Note that there are no tests for this exercise. Your code should compile, and this class will be tested in later exercises.