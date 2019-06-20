# CppND-System-Monitor

Starter code for System Monitor Project in the C++ OOP course. Most of the code is provided for you here. Follow along with the classroom lesson to fill out the `ProcessParser` and `Process` classes to complete your project!

## To setup and compile in Udacity Ubuntu workspace:

1. Clone repository into `/home/workspace/`
```
cd /home/workspace/
git clone https://github.com/udacity/CppND-System-Monitor
```
2. Follow along with the lesson and make sure you complete the `ProcessParser` and `Process` classes before attempting to run the project.

3. Install `ncurses` package
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```
4. Compile and run
```
g++ -std="c++17" main.cpp -lncurses
./a.out
```
5. In case of error that looks like the following: 
```
root@77e30fca8a01:/home/workspace/CppND-Object-Oriented# ./a.out
*** %n in writable segment detected ***
                                      Aborted (core dumped)
```
just keep trying `./a.out` and it should work eventually!
