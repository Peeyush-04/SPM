#ifndef PROCESS_CONTROL_H
#define PROCESS_CONTROL_H

#include <iostream>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <signal.h>
    #include <sys/resource.h>
    #include <unistd.h>
#endif

// Kills the process with the given PID.
inline bool killProcess(int pid) {
#ifdef _WIN32
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (!hProcess) {
        std::cerr << "Unable to open process for termination." << std::endl;
        return false;
    }
    bool result = TerminateProcess(hProcess, 0);
    CloseHandle(hProcess);
    return result;
#else
    return (kill(pid, SIGKILL) == 0);
#endif
}

// Changes the process's priority.
// On Windows, newPriority: 1 (Idle) to 5 (High). On Linux, newPriority is the nice value.
inline bool changeProcessPriority(int pid, int newPriority) {
#ifdef _WIN32
    HANDLE hProcess = OpenProcess(PROCESS_SET_INFORMATION, FALSE, pid);
    if (!hProcess) {
        std::cerr << "Failed to open process for priority change." << std::endl;
        return false;
    }
    int priorityClass;
    switch (newPriority) {
        case 1: priorityClass = IDLE_PRIORITY_CLASS; break;
        case 2: priorityClass = BELOW_NORMAL_PRIORITY_CLASS; break;
        case 3: priorityClass = NORMAL_PRIORITY_CLASS; break;
        case 4: priorityClass = ABOVE_NORMAL_PRIORITY_CLASS; break;
        case 5: priorityClass = HIGH_PRIORITY_CLASS; break;
        default: priorityClass = NORMAL_PRIORITY_CLASS;
    }
    bool success = SetPriorityClass(hProcess, priorityClass);
    CloseHandle(hProcess);
    return success;
#else
    return (setpriority(PRIO_PROCESS, pid, newPriority) == 0);
#endif
}

#endif // PROCESS_CONTROL_H
