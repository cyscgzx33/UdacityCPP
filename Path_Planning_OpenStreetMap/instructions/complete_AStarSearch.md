In this exercise, you will complete `AStarSearch()` in `route_planner.cpp` using the `NextNode`, `ConstructFinalPath`, and `AddNeighbors` methods you have written previously.

To complete this exercise:
1. Delete the current contents of `AStarSearch`.
2. Use the `NextNode`, `ConstructFinalPath` and `AddNeighbors` methods to implement the pseudocode below in `AStarSearch`:

>AStarSearch:
>
>1. Set `start_node->visited` to be `true`.
> 
>2. Push `start_node` to the back of `open_list`.
>  
>3. Create a pointer `RouteModel::Node *current_node` and initialize the pointer to `nullptr`.
>
>4. **while** the `open_list` size is greater than 0:
>    
>  1. Set the `current_node` pointer to the results of calling `NextNode`.
>  2. **if** the distance from `current_node` to the `end_node` is 0:
    - Call `ConstructFinalPath` using `current_node` and set `m_Model.path` with the results.
    - Return to exit the A\* search.
>    
>  4. **else** call `AddNeighbors` with the `current_node`./CppND-Route-Planning-Solution -f ../map.osm
````
