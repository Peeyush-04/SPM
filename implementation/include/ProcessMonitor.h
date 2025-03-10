#ifndef PROCESS_MONITOR_H
#define PROCESS_MONITOR_H

#include <vector>
#include <string>

struct Process {
    int pid;
    std::string name;
};

class ProcessMonitor {
public:
    // Directly define the function in the header file
    static std::vector<Process> listProcesses() {
        return {
            {1234, "example.exe"},
            {5678, "test.exe"}
        };
    }
};

#endif // PROCESS_MONITOR_H

