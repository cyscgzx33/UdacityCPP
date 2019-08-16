#include <iostream>

int main() {
    int id = 0; // Define an integer variable

    // create lambda
    auto f = [](const int id) { std::cout << "ID = " << id << std::endl; }; // ID is passed as a parameter
                                                                            // no "const" also works 

    // execute function object and pass the parameter
    f(id);

    return 0;
}