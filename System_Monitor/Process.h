#include <string>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
private:
    std::string pid_;
    std::string user_;
    std::string cmd_;
    std::string cpu_;
    std::string mem_;
    std::string upTime_;

public:
    Process(string pid) {
        this->pid_ = pid;
        this->user_ = ProcessParser::getProcUser(pid);
        this->mem_ = "0.0"; //completed initialization for mem_
        this->cmd_ = "0.0"; //completed initialization for cmd_
        this->cpu_ = "0.0"; //completed initialization for cpu_
        this->upTime_ = "0:00:00"; //completed initialization for upTime_
    }
    
    // setters
    void setPid(int pid);
    void setUser(std::string user);
    void setCmd(std::string cmd);
    void setCpu(double cpu); // default is int
    void setMem(double mem); // default is int
    void setUpTime(std::string upTime);

    // getters
    std::string getPid()const;
    std::string getUser()const;
    std::string getCmd()const;
    double getCpu()const; // default is int
    double getMem()const;
    std::string getUpTime()const;

    // others
    std::string getProcess();
};

// definitions of setters
void Process::setPid(int pid) {
    this->pid_ = pid;
}

void Process::setUser(std::string user) {
    this->user_ = user;
}

void Process::setCmd(std::string cmd) {
    this->cmd_ = cmd;
}

void Process::setCpu(double cpu) {
    this->cpu_ = std::to_string(cpu);
}

void Process::setMem(double mem) {
    this->mem_ = std::to_string(mem);
}

void Process::setUpTime(std::string upTime) {
    this->upTime_ = upTime;
}

// definitions of getters
std::string Process::getPid() const {
    return this->pid_;
}

std::string Process::getUser() const {
    return this->user_;
}

std::string Process::getCmd() const {
    return this->cmd_;
}

double Process::getCpu() const {
    return std::stod(cpu_); // A c++11 feature;
}

double Process::getMem() const {
    return std::stod(mem_); // A c++11 feature;
}

std::string Process::getUpTime() const {
    return this->upTime_;
}

// definitions of others
std::string Process::getProcess(){
    if(!ProcessParser::isPidExisting(this->pid_))
        return "";
    this->mem = ProcessParser::getVmSize(this->pid_);
    this->upTime = ProcessParser::getProcUpTime(this->pid_);
    this->cpu = ProcessParser::getCpuPercent(this->pid_);

    return (this->pid_ + "   " +
            this->user_ + "   " +
            this->mem_ + "   " +
            this->cpu_ + "   " +
            this->upTime_ + "   "
            ); 
            // finished the string by adding: this->user + "   "+ mem...cpu...upTime...;
}
