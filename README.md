# UdacityCPP
Udacity C++ Nanodegree Program

## A* Search Algorithm
Implemented an A* grid-based search algorithm. 
The searching behavior a BFS like algorithm to visit priority of neighbor nodes w/ higher ```int f``` value, which is a dynamic value relate to its current node during the search process, that equals to the sum of ```int h (Heuristic)``` and ```int g``` value, i.e., ```f(n) = g(n) + h(n)```.
A set of tests is provided by Udacity and have been passed using such implementation.
