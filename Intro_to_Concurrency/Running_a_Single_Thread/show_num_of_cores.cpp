#include <iostream>
#include <thread>

int main() {
    unsigned int n_cores = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with "
              << n_cores << " cores available"
              << std::endl;

    return 0;
}