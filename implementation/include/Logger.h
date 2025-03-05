#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>
#include <fstream>
#include "ProcessMonitor.h"

namespace Logger {
    // Placeholder for logging functionality
    void logProcesses(const std::vector<Process>& processes, const std::string& filename) {
        std::ofstream logFile(filename, std::ios::app);
        if (logFile.is_open()) {
            logFile << "Simple Process Log\n";
            for (const auto& process : processes) {
                logFile << "PID: " << process.pid << ", Name: " << process.name << "\n";
            }
            logFile.close();
        }
    }
}

#endif // LOGGER_H
