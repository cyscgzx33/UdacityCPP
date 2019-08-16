#include <iostream>
#include <thread>
#include <string>

void printID(int id)
{
    std::this_thread::sleep_for( std::chrono::milliseconds(50) );
    std::cout << "ID = " << id << std::endl;
}

void printIDAndName(int id, std::string name)
{
    std::this_thread::sleep_for( std::chrono::milliseconds(100) );
    std::cout << "ID = " << id << ", name = " << name << std::endl;
}

int main() {
    
}