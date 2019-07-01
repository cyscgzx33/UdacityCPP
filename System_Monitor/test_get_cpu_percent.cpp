#include "ProcessParser.h"

int main(int argc, char** argv) {
    std::cout << ProcessParser::getCpuPercent("1651") << std::endl;
    return 0;
}