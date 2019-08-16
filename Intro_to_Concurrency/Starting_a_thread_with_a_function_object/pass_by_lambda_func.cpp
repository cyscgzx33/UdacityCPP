#include <iostream>

int main() {
    // create lambdas
    int id = 0; // define and integer variable

    // auto f0 = []() { std::cout << "ID = " << id << std::endl; }; // Error: 'id' cannot be accessed

    id++;
    auto f1 = [id]() { std::cout << "ID = " << id << std::endl; }; // Correct, 'id' is captured by value

    id++;
    auto f2 = [&id]() { std::cout << "ID = " << id << std::endl; }; // Correct, 'id' is captured by reference

    id++;
    // auto f3 = [&id]() { std::cout << "ID = " << ++id << std::endl; }; // Error, 'id' may not be modified
    
    id++;
    auto f4 = [id]() mutable { std::cout << "ID = " << id << std::endl; }; // Correct, 'id' can be modified

    id++;
    auto f5 = [&id]() mutable { std::cout << "ID = " << id << std::endl; }; // OK, 'id' can be modified;
                                                                            // but because of &, f2 also outputs "ID = 5"

    // execute lambdas
    f1();
    f2();
    f4();
    f5();

    return 0;
}