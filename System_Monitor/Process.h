#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "ProcessParser.h"

/* It looks weried, need to confirm the whole class */

/*
 * Basic class for Process representation.
 * It contains relevant attributes as shown below.
 */
class Process {
  private:
    std::string pid_;
    std::string user_;
    std::string cmd_;
    std::string cpu_;
    std::string mem_;
    std::string up_time_;

  public:
    Process(std::string pid) {
        this->pid_ = pid;
        this->user_ = ProcessParser::getProcUser(pid);
        this->mem_ = ProcessParser::getVmSize(pid);
        this->cmd_ = ProcessParser::getCmd(pid); 
        this->cpu_ = ProcessParser::getCpuPercent(pid); 
        this->up_time_ = ProcessParser::getProcUpTime(pid); 
    }
    
    // setters
    void setPid(int pid);

    // getters
    std::string getPid()const;
    std::string getUser()const;
    std::string getCmd()const;
    int getCpu()const;
    int getMem()const;
    std::string getUpTime()const;
    std::string getProcess();
};

// definitions of setters
void Process::setPid(int pid) {
    this->pid_ = pid;
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

int Process::getCpu() const {
    return std::stod(cpu_); // A c++11 feature;
}

int Process::getMem() const {
    return std::stod(mem_); // A c++11 feature;
}

std::string Process::getUpTime() const {
    return this->up_time_;
}

std::string Process::getProcess(){
    if(!ProcessParser::isPidExisting(this->pid_))
        return "";
    this->mem_ = ProcessParser::getVmSize(this->pid_);
    this->up_time_ = ProcessParser::getProcUpTime(this->pid_);
    this->cpu_ = ProcessParser::getCpuPercent(this->pid_);

    return (this->pid_                  + "   " +
            this->user_                 + "   " +
            this->mem_.substr(0, 5)     + "   " +
            this->cpu_.substr(0, 5)     + "   " +
            this->up_time_.substr(0, 5) + "   " +
            this->cmd_.substr(0, 30)    + "..." ); 
}
#endif