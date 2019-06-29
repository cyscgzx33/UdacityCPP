#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include "util.h"
#include "constants.h"
#include "ProcessParser.h"

/* function goal: get CPU percentage by acquiring relevant times of active occupation of CPU*/
std::string ProcessParser::getCpuPercent(string pid) {
    
    std::string line;

    // open stream for a specific file
    std::ifstream stream = Util::getStream( (Path::basePath() + pid + Path::statPath()) );

    std::getline(stream, line);
    // std::string str = line; // Why do we need this line? can we omit it?
    std::istringstream buf(line);
    std::istream_iterator<string> begin(buf), end;
    std::vector<string> values(begin, end);

    // acquiring relevant times for calculation of active occupation of CPU for selected process
    float utime = stof(ProcessParser::getProcUpTime(pid));
    float stime = stof(values[14]);  // 14; based on linux format
    float cutime = stof(values[15]); // 15; based on linux format
    float cstime = stof(values[16]); // 16; based on linux format
    float starttime = stof(values[21]); // 21; based on linux format
    float uptime = ProcessParser::getSysUpTime();
    float freq = sysconf(_SC_CLK_TCK); // the number of clock ticks per second, 
                                       // specifically, the kernel is configured for how many clocks per second (or Hz of clock).

    float total_time = utime + stime + cutime + cstime;
    float seconds = uptime - (starttime / freq);
    float result = 100.0 * ( (total_time / freq) / seconds );

    return std::to_string(result);

}

int main(int argc, char** argv) {
    std::cout << ProcessParser::getCpuPercent("1651") << std::endl;
    return 0;
}