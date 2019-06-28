#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include "util.h"
#include "constants.h"

std::string getVmSize(std::string pid) {
    
    std::string line;

    // declare search attributes for file
    std::string name = "VmData";
    std::string value;
    float result;

    // open stream for a specific file
    std::ifstream stream = Util::getStream( (Path::basePath() + pid + Path::statusPath()) );
    
    // verbosely check the path obtained above
    std::cout << (Path::basePath() + pid + Path::statusPath()) << std::endl;

    while(std::getline(stream, line)) {
        // searching line by line
        if (line.compare(0, name.size(), name) == 0) {
            // slicing string line on ws for values using sstream
            std::istringstream buf(line);
            std::istream_iterator<string> beg(buf), end;
            std::vector<string> values(beg, end);

            // conversion kB -> GB
            result = ( stof(values[1]) / float(1024) );
            break;
        }
    }
    
    return std::to_string(result);
}

int main(int argc, char** argv) {
    std::cout << getVmSize("1") << std::endl;
    return 0;
}