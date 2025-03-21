#ifndef PROCESS_MONITOR_H
#define PROCESS_MONITOR_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#ifdef _WIN32
  #include <windows.h>
  #include <tlhelp32.h>
#else
  #include <dirent.h>
  #include <sys/types.h>
#endif

struct Process {
    int pid;
    std::string name;
};

inline std::vector<Process> listProcesses() {
    std::vector<Process> processes;
#ifdef _WIN32
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to create process snapshot." << std::endl;
        return processes;
    }
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hProcessSnap, &pe32)) {
        do {
            processes.push_back({ 
                static_cast<int>(pe32.th32ProcessID), 
                std::string(pe32.szExeFile) 
            });
        } while (Process32Next(hProcessSnap, &pe32));
    }
    CloseHandle(hProcessSnap);
#else
    DIR* dir = opendir("/proc");
    if (!dir) {
        std::cerr << "Could not open /proc directory." << std::endl;
        return processes;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            std::string dirname(entry->d_name);
            if (std::all_of(dirname.begin(), dirname.end(), ::isdigit)) {
                int pid = std::stoi(dirname);
                processes.push_back({pid, "Unknown"});
            }
        }
    }
    closedir(dir);
#endif
    return processes;
}

#endif // PROCESS_MONITOR_H
