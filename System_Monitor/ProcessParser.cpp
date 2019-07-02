#include "ProcessParser.h"

#include "constants.h"
#include "util.h"

// TODO: Define all of the above functions below:

/* function goal: figure out how much RAM is a given process using */
std::string ProcessParser::getVmSize(std::string pid) {
    
    std::string line;

    // declare search attributes for file
    std::string name = "VmData";
    std::string value;
    float result;

    // open stream for a specific file
    std::ifstream stream = Util::getStream( (Path::basePath() + pid + Path::statusPath()) );

    while (std::getline(stream, line)) { // read the data by lines
        // searching line by line
        if (line.compare(0, name.size(), name) == 0) {
            // slicing string line on ws for values using sstream
            // Note: 1. it is using buf to collect each line;
            //       2. and parse it into begin and end
            //       3. finally it processes into a vector of string
            // Example:
            //       1. try "cat /proc/16559/"
            //       2. one can get:
            //              "...
            //               VmData: 1131692 kB
            //               ..."
            //       3. Here, "1131692" is the values[1]    
            std::istringstream buf(line);
            std::istream_iterator<std::string> begin(buf), end;
            std::vector<std::string> values(begin, end);

            // conversion kB -> GB
            result = ( stof(values[1]) / float(1024*1024) );
            break;
        }
    }
    
    return std::to_string(result);
}

/* function goal: get CPU percentage by acquiring relevant times of active occupation of CPU*/
std::string ProcessParser::getCpuPercent(std::string pid) {
    
    std::string line;

    // open stream for a specific file
    std::ifstream stream = Util::getStream( (Path::basePath() + pid + Path::statPath()) );

    std::getline(stream, line);
    // std::string str = line; // Why do we need this line? can we omit it?
    std::istringstream buf(line);
    std::istream_iterator<std::string> begin(buf), end;
    std::vector<std::string> values(begin, end);

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


std::string ProcessParser::getProcUpTime(std::string pid) {
    std::string line;
    std::string value;

    // open stream for a specific file
    std::ifstream stream = Util::getStream( (Path::basePath() + pid + Path::statPath()) );

    std::getline(stream, line);
    // std::string str = line; // Why do we need this line? can we omit it?
    std::istringstream buf(line);
    std::istream_iterator<std::string> begin(buf), end;
    std::vector<std::string> values(begin, end);

    // get clock ticks of the host machine using sysconf()
    return std::to_string( float( stof(values[13]) / sysconf(_SC_CLK_TCK) ) );
}

long int ProcessParser::getSysUpTime() {
    std::string line;
    std::string value;

    // open stream for a specific line
    std::ifstream stream = Util::getStream( ( Path::basePath() + Path::upTimePath() ) );

    std::getline(stream, line);
    std::istringstream buf(line);
    std::istream_iterator<std::string> begin(buf), end;
    std::vector<std::string> values(begin, end);

    return stoi(values[0]); // it should be the default index, which is 0
}

/* Retrieve the process user thru UID*/
std::string ProcessParser::getProcUser(std::string pid) {
    std::string line;

    std::string name = "Uid"; // TODO: confirm if I have to use "Uid:"
    std::string result = "";
    // open stream for a specific line
    std::ifstream stream = Util::getStream( ( Path::basePath() + pid + Path::upTimePath() ) );

    // Getting UID for user
    while ( std::getline(stream, line) ) {
        if ( line.compare(0, name.size(), name) == 0 ) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> begin, end;
            std::vector<std::string> values(begin, end);
            result = values[1];
            break;
        }
    }
    stream = Util::getStream("/etc/passwd");
    name = "x:" + result;

    // Search for name of the user with selected UID
    while ( std::getline(stream, line) ) {
        if ( line.find(name) != std::string::npos ) {
            result = line.substr( 0, line.find(":") );
            return result;
        }
    }

    return "";
}

/* Retrieve a pid list from /proc */
std::vector<std::string> ProcessParser::getPidList() {

    DIR* dir;

    std::vector<std::string> container;

    // check if opening the directory is succeeded
    if ( !( dir = opendir("/proc") ) ) {
        throw std::runtime_error( std::strerror(errno) );
    }

    // Note: it is IMPORTANT that for each element (file || dirctoary) inside the /proc
    while ( dirent* dirp = readdir(dir) ) {
        // STEP 1 : check if it is this a directory
        if ( dirp->d_type != DT_DIR ) continue;

        // STEP 2 : check if every chararcter in it is a digit
        /* Note:
         * The function starting with "[]" is called "lambda function" or "arrow function",
         * here, it specifically checks from start to end, and check each element is a digit (return true if yes for each)
         * in the end, if all the elements are digits, then the all_of() returns true
         */
        if ( all_of( dirp->d_name, dirp->d_name + std::strlen(dirp->d_name), [](char c){ return std::isdigit(c); } ) ) {
            container.push_back(dirp->d_name);
        }
    }

    // check if closing the directory is succeeded
    if ( closedir(dir) ) {
        throw std::runtime_error( std::strerror(errno) );
    }

    return container;

}

/* Retrieve the command that executed the process */
std::string ProcessParser::getCmd(std::string pid) {
    string line;
    std::ifstream stream = Util::getStream( (Path::basePath() + pid + Path::cmdPath() ) );
    std::getline(stream, line);

    return line;
}

/* Retrieve the number of CPU cores on the host */
int ProcessParser::getNumberOfCores() {
    std::string line;
    std::string name = "cpu cores";
    std::ifstream stream = Util::getStream( Path::basePath() + Path::cpuInfoPath() );

    while ( std::getline(stream, line) ) {
        if ( line.compare(0, name.size(), name) == 0 ) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> begin(buf), end;
            std::vector<std::string> values(begin, end);
            // verbosely check:
            // std::cout << "The vector of strings contains:" << std::endl;
            // for (auto& str : values) cout << str << ", ";
            // std::cout << '\n';
            
            return stoi(values[3]); // FYI, the raw info: "cpu cores       : 2"
        }
    }
}


std::vector<std::string> ProcessParser::getSysCpuPercent(std::string core_number) {

    // It is possible to use this method for selection of data for
    // overall cpu or every core.
    // When nothing is passed "cpu" line is read
    // When, for example, "0" is passed -> cpu0 -> data for first core is read
    std::string line;
    std::string name = "cpu" + core_number;
    std::ifstream stream = Util::getStream( Path::basePath() + Path::statPath() );

    while ( std::getline(stream, line) ) {
        if ( line.compare(0, name.size(), name) == 0 ) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> begin(buf), end;
            std::vector<std::string> values(begin, end);

            return values;
        }
    }

    // otherwise, just return an empty vector
    // Note: look at the way it is constructed
    return std::vector<std::string>();

}

std::string ProcessParser::PrintCpuStats(std::vector<std::string> values_1,
                                         std::vector<std::string> values_2) 
{
    /* Note:
     * Because CPU stats can be calculated only if you take measurements
     * in two different time, this function has two parameters: 
     * two vectors of relevant values.
     * We use a formula to calculate overall activity of processor.
     */
    float active_time =   ProcessParser::getSysActiveCpuTime(values_2) 
                        - ProcessParser::getSysActiveCpuTime(values_1);
    float idle_time   =   ProcessParser::getSysIdleCpuTime(values_2) 
                        - ProcessParser::getSysIdleCpuTime(values_1);

    float total_time  = active_time + idle_time;
    float result      = 100.0 * (active_time / total_time);
    return std::to_string(result);
}

float ProcessParser::getSysActiveCpuTime(std::vector<std::string> values) {
    return ( stof(values[S_USER])       +
             stof(values[S_NICE])       +
             stof(values[S_SYSTEM])     +
             stof(values[S_IRQ])        +
             stof(values[S_SOFTIRQ])    +
             stof(values[S_STEAL])      +
             stof(values[S_GUEST])      +
             stof(values[S_GUEST_NICE]) );
}

float ProcessParser::getSysIdleCpuTime(std::vector<std::string> values) {
    return ( stof(values[S_IDLE]) + stof(values[S_IOWAIT]) );
}


int main(int argc, char** argv) {

    std::cout << "test get num of cores" << std::endl;
    std::cout << ProcessParser::getNumberOfCores() << std::endl;
    std::cout << "test get system up time:" << std::endl;
    std::cout << ProcessParser::getSysUpTime() << std::endl;
    return 0;
}