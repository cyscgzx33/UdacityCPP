# UdacityCPP
Course metrials of Udacity C++ Nanodegree Program: **Knowledge** and **Porjects**.

## A* Search Algorithm
* Contained in the folder `A_star`
* Implemented an A* grid-based search algorithm. 
    * The searching behavior a *BFS like algorithm* to visit priority of neighbor nodes w/ higher ```int f``` value, which is a dynamic value relate to its current node during the search process, that equals to the sum of ```int h (Heuristic)``` and ```int g``` value, i.e., ```f(n) = g(n) + h(n)```.
    * A set of tests is provided by Udacity and have been passed using such implementation.

## Path Planning Project
* Contained in the folder `Path_Planning_OpenStreetMap`
* In this project, an A* algorithm is utilized to implement a path planning algorithm
    * it is within the *OpenStreetMap* frame
    * it searches a path from givin *start* and *end* position

## Introduction to Object-Oriented-Pogramming (OOP)
* Contained in the folder `Intro_to_OOP`
* The materials/topics include a series of introduction, examples and exercise scripts about how C++ handles memory management, such as allocation and deleting without memory leak. Such topics include:
    * **Basic Data Type**: `Stack`, `Heap`, `Pointer`, `Reference`, etc.
    * **Memory Process**: `new`, `delete`, `malloc`, `memset`, etc.
    * **Smart Pointer**: `unique_ptr`, `shared_ptr`, etc.
    * others / etc.

## System Monitor Project
* Contained in the folder `System_Monitor`
* In this project, a Linux System Monitor is built using C++ OOP topics, including *abstraction*, *inheritance*, *polymorphism*, and etc.
    * it implements similar functionalities as `htop`
    * the basic idea is to read and parse system file contents in `/proc`
    * (TODO) refine the UI by utilizing Ncurses package

## Introduction to Memory Management (OOP)
* Contained in the folder `Intro_to_Memory_Mgmt`
* Thie materials/topics include a series of introduction, examples and exercise scripts about OOP in C++:
    * **Abstraction**(class declaration/definition, access modifiers)
    * **Inheritance**(basics, multiple inheritance, multi-level inheritance, friend class)
    * **Polymorphism**(overload operator/function, virtual functions)
    * **Generic Programming**(class/function template, deduction and multiple generic types)
    * others / etc.

## Smart Pointer Project
* Contained in the folder `Smart_Pointer`
* In this project, a simple garbage collector pointer class has been implemented. The garbage collector basically uses three classes: `Pointer`, `PtrDetails` and `Iter`:
    * `Pointer` is the core garbage collector class, which implements a garbage-collection pointer
    * `PtrDetails` maintains a list reference counts with allocated memory, and bonds a reference count to a piece of allocated memory
    * `Iter` is a template class similar in function to an `STL` iterator, and it defines all pointer *operations*, including pointer arithmetic, such as `*`, `->`, `begin()`, and `end()`, which work much like their equivalents in the `STL`.