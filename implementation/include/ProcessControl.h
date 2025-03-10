#ifndef PROCESS_CONTROL_H
#define PROCESS_CONTROL_H

#include <iostream>

class ProcessControl {
public:
    // Directly define the function in the header file
    static bool killProcess(int pid) {
        std::cout << "Simulating process termination for PID " << pid << "\n";
        return true;
    }

    static bool changeProcessPriority(int pid, int priority) {
        std::cout << "Simulating changing priority for PID " << pid << " to " << priority << "\n";
        return true;
    }
};

#endif // PROCESS_CONTROL_H

