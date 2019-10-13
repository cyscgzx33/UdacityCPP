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
    * at this moment, the elevator system should look like this:  
    <img align="center" src="images/elevator_initialized.png" width="250" />
* Step 2: set up external requests (i.e., push *Up* or *Down* buttons on multiple floors) to trigger the elevator
    * the terminal would ask `Please give an input: at how many floors the external elevator button is pushed (from 1 to N)`, where `N` is set in the step 1, in this example, `N` is `6` (the intuition here is to simulate that: in how many floors, people have pushed the **external elevator buttons**, i.e., *Up* or *Down*)
        * for example, we type in `3` then hit `Enter`
    * now, based on what the user has typed in, the terminal would ask multiple times about: `Please give an input: at which floor the external elevator button is pushed (from 1 to 6)` and `Which button you would press, Up or Down (u/d)? `
        * at this example, we iteratively type in `1` + `u`, `3` + `u`, following by `5` + `d`
    * if everything works fine, the terminal would hint the external requests have been set up, and will start to execute them
    * at this moment, the elevator system should look like this:  
    <img align="center" src="images/external_requests_set_up.png" width="250" />
* Step 3: execute external requests, together with set up & execte internal requests (i.e., push *Floor #* buttons inside the elevator)
    *


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