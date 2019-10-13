# Elevator System
This is a repo for the Capstone project in Udacity C++ Nanodegree Program.
The Capstone chosen here gives a chance to practice the knowledge of C++ programming language, by implementing the well-know Object-Oreiented Design (OOD) problem, Elevator System Design.

## Dependencies for Running Locally
* cmake >= 3.7
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
* gcc/g++ >= 5.4

## Instructions for Building the Project
* Clone this repo.
* Make a build directory in the top level directory by: `mkdir build && cd build`.
* Compile by: `cmake .. && make`.

## Instructions for Running the Project
* Step 0: after finish the build process, run the executable by
    * `./elev_sys_sim`.
* Step 1: initialize an elevator system with N floors
    * the terminal would ask `Please set elevator system with N floors/levels, where N should a positive integer:`
    * simply type in a positive interger, for example, `6`, then hit `Enter`
    * if everything works fine, the terminal would hint the initialization works successfully, and shows some information about the current status of the elevator system
    * At this moment, the elevator system should look like this:
    <img src="https://github.com/cyscgzx33/UdacityCPP/tree/master/Elevator_System/images/elevator_initialized.png">
## Information about Rubric & Criteria
* Loops, Functions, I/O
    * The project demonstrates an understanding of C++ functions and control sturctures.
    * The project accepts user input and processes the input.
* Object Oriented Programming
    * The project uses Object Oriented Programming techniques.
    * Classes use appropriate access specifiers for class members.
    * Class constructors utilize member initialization lists.
    * Classes abstract implementation details from their interfaces.
    * Classes encapsulate behavior.
* Memory Management
    * The project makes use of references in function declarations.
    * The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
* Concurrency
    * (Right now, no Concurrency stategy has been adopted)