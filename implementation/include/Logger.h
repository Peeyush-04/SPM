#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "ProcessMonitor.h"

namespace Logger {
    inline void logProcesses(const std::vector<Process>& processes, const std::string& filename) {
        std::ofstream ofs(filename, std::ios::app);
        if (!ofs.is_open()) {
            return;
        }

        // Get current timestamp
        std::time_t now = std::time(nullptr);
        ofs << "Process Log Timestamp: " << std::ctime(&now);
        ofs << "Process Log:\n";
        ofs << std::left << std::setw(10) << "PID" << std::setw(30) << "Name" << "\n";
        ofs << std::string(40, '-') << "\n";

        for (const auto& proc : processes) {
            ofs << std::left << std::setw(10) << proc.pid << std::setw(30) << proc.name << "\n";
        }
        ofs << std::string(40, '-') << "\n\n";
    }
}

#endif // LOGGER_H

