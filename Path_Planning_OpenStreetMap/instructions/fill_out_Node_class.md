The `Model::Node` class that exists in the current code doesn't contain all the data that would be needed to perfom an A\* search. In order to perform a search, it would be ideal for each node to contain at least the following information:
- The g-value for the node.
- The h-value for the node.
- A boolean to indicate if the node has been visited.
- A pointer to the node's parent.

In this exercise, you will fill out the `RouteModel::Node` class, which will extend the `Model::Node` class so that the data above, along with a few other useful variables, can be included with each node.


To complete this exercise:
1. Add the following public variables to the `RouteModel::Node` class:
  - A `Node` pointer `parent`, which is initialized to a `nullptr`.
  - A `float` `h_value`, which is initialized to the maximum possible: `std::numeric_limits<float>::max()`.
  - A `float` `g_value`, which is initialized to 0.0.
  - A `bool` `visited`, which is initialized to `false`.
  - A vector of `Node` pointers named `neighbors`.
2. Add the following two constructors for `RouteModel::Node` objects:
  - A default constructor `Node(){}`.
  - A constructor which accepts an `int` index named `idx`, a pointer to a `RouteModel` object named `search_model`, and a `Model::Node` object named `node`. This constructor should use a constructor list to call the `Model::Node` constructor using `node`, and set the two private variables (discussed below) as follows: `parent_model(search_model)` and `index(idx)`.
3. Add the following private variables to the `RouteModel::Node` class:
  - An `int` `index`.
  - A pointer to a `RouteModel` object named `parent_model`. This variable is important, as it allows each node to access data stored in the parent model that the node belongs to.