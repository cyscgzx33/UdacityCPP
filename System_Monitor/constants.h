// To avoid calling the header file multiple times that cause crash
/* For example:
 * class A and B both included class Path, and 
 * class C inherits both A and B,
 * then in C the class Path will only be called once.
 */
#ifndef PATH_H
#define PATH_H

#include <string>
using namespace std;

enum CPUStates{
	S_USER = 1,
	S_NICE,
	S_SYSTEM,
	S_IDLE,
	S_IOWAIT,
	S_IRQ,
	S_SOFTIRQ,
	S_STEAL,
	S_GUEST,
	S_GUEST_NICE
};

class Path{

public:
    static string basePath() { // In terminal, try "cd /proc/",
                               // and try "cat stat",
                               // something interesting happens.
                               // Use "man proc" to check the manual?
        return "/proc/";
    }
    static string cmdPath(){
        return "/cmdline";
    }
    static string statusPath(){
        return "/status";
    }
    static string statPath(){
        return "stat";
    }
    static string upTimePath(){
        return "uptime";
    }
    static string memInfoPath(){
        return "meminfo";
    }
    static string versionPath(){
        return "version";
    }
    static string cpuInfoPath(){
        return "cpuinfo";
    }
};

#endif