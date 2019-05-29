The `Model` class that exists in the current code doesn't contain all the data or methods that will be needed to perfom an A\* search, so we are going to extend that class with a `RouteModel` class. In this exercise, you will fill out the `RouteModel` class in `route_model.h`. In the next exercises, you will also fill out the `RouteModel::Node` class as well.


To complete this exercise:
In `route_model.h`:
1. Add a public constructor declaration in the `RouteModel` class. This constructor should accept the following argument, which will be the Open Street Map data: `const std::vector<std::byte> &xml`.
2. Add a private vector of `Node` objects named `m_Nodes`. This will store all of the nodes from the Open Street Map data.
3. Add a public getter method `SNodes`. This method should have as the return type a reference to a vector of `Nodes`. The method should return `m_Nodes`.

In `route_model.cpp`:
1. Add a `RouteModel` constructor in `route_model.cpp`. In the `RouteModel` constructor, use a constructor list to call the `Model` constructor with the `xml` variable: `Model(xml)`.