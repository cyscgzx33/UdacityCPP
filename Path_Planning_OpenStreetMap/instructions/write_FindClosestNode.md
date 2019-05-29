In the upcoming exercises, you will start working on the `RoutePlanner` class, which will contain methods to perform the A\* search. A `RoutePlanner` class will be initialized starting and ending coordinates provided by the user. These will be input as float values, but in order for the search to be performed, you will need to find the nodes in the `RouteModel` that are closest to the starting and ending coordinates. In this exercise, you will write a method `FindClosestNode` that accepts two `floats` and finds the closest node in your model.


To complete this exercise:
1. Add a public method declaration `FindClosestNode` in the `RouteModel` class in `route_model.h`. This method should accept two floats `x` and `y` as arguments, and should return a reference to a `RouteModel::Node` object.
2. Add a method definition `route_model.cpp`
3. In the body of the method, you will need to do the following:
  1. Create a temporary `Node` with `x` and `y` coordinates given by the method inputs.
  2. Create a float `min_dist = std::numeric_limits<float>::max()` for the minum distance found in your search.
  3. Create an `int` variable `closest_idx` to store the index of the closest
  4. Write a loop that iterates through the vector given by calling `Roads()`. 
  5. For each reference `&road` in the vector, check that the type is not a footway: `road.type != Model::Road::Type::Footway`. If the road is not a footway:
      1. Loop over each node index in the `way` that the road belongs to: `Ways()[road.way].nodes`.
      2. Update `closest_idx` and `min_dist`, if needed.
  6. Return the node from the `SNodes()` vector using the found index.