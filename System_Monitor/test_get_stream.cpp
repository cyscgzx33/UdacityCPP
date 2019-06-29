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

            // Note: 1. it is using buf to collect each line;
            //       2. and parse it into begin and end
            //       3. finally it processes into a vector of string
            std::istringstream buf(line);
            std::istream_iterator<string> begin(buf), end;
            std::vector<string> values(begin, end);

            // conversion kB -> GB
            result = ( stof(values[1]) / float(1024*1024) );
            break;
        }
    }
    
    return std::to_string(result);
}

int main(int argc, char** argv) {
    std::cout << getVmSize("1") << std::endl;
    return 0;
}