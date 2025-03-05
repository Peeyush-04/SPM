#ifndef PROCESSMONITOR_H
#define PROCESSMONITOR_H

#include <vector>
#include <string>

struct Process {
    int pid;
    std::string name;
};

namespace ProcessMonitor {
    std::vector<Process> listProcesses() {
        return std::vector<Process>{
            {1, "System"},
            {2, "Kernel"},
            {3, "Init"}
        };
    }
}

#endif // PROCESSMONITOR_H
