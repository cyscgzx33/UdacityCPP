Now that you have a `RouteModel` class and you have completed the `RouteModel::Node` nested class, you can create `RouteModel` nodes. When the `RouteModel` constructor is called, it calls the `Model` constructor with the open street map data. When this happens, a collection of `Model:Node` objects are created. However, in order to perform the A\* search, you will need to use `RouteModel::Node` objects instead. In this exercise, you will take the vector of `Model:Node` objects and create a vector of `RouteModel::Node` objects from them that will be stored in the `RouteModel`.


To complete this exercise:

- Write a `for` loop with a counter to loop over `this->Nodes()`, which is the list of `Model::Node` objects. For each node, use the `RouteModel::Node` constructor to create a new node with index given by the counter, and push the node to the back of `m_Nodes`. 