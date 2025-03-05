#include <iostream>
#include <limits>
#include "../include/ProcessMonitor.h"
#include "../include/ProcessControl.h"
#include "../include/Logger.h"

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int choice;
    while (true) {
        std::cout << "\n=== Smart Process Manager (SPM) ===\n";
        std::cout << "1. List Processes\n";
        std::cout << "2. Kill Process\n";
        std::cout << "3. Change Process Priority\n";
        std::cout << "4. Log Processes to File\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please try again.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                auto processes = ProcessMonitor::listProcesses();
                std::cout << "Running Processes:\n";
                for (const auto& proc : processes) {
                    std::cout << "PID: " << proc.pid << " Name: " << proc.name << "\n";
                }
                break;
            }
            case 2: {
                int pid;
                std::cout << "Enter PID to kill: ";
                if (!(std::cin >> pid)) {
                    std::cout << "Invalid PID. Please try again.\n";
                    clearInputBuffer();
                    continue;
                }
                if (ProcessControl::killProcess(pid))
                    std::cout << "Process killed successfully.\n";
                else
                    std::cout << "Failed to kill process.\n";
                break;
            }
            case 3: {
                int pid, priority;
                std::cout << "Enter PID to change priority: ";
                if (!(std::cin >> pid)) {
                    std::cout << "Invalid PID. Please try again.\n";
                    clearInputBuffer();
                    continue;
                }
                std::cout << "Enter new priority: ";
                if (!(std::cin >> priority)) {
                    std::cout << "Invalid priority. Please try again.\n";
                    clearInputBuffer();
                    continue;
                }
                if (ProcessControl::changeProcessPriority(pid, priority))
                    std::cout << "Priority changed successfully.\n";
                else
                    std::cout << "Failed to change priority.\n";
                break;
            }
            case 4: {
                auto processes = ProcessMonitor::listProcesses();
                Logger::logProcesses(processes, "process_log.txt");
                std::cout << "Processes logged to process_log.txt\n";
                break;
            }
            case 5:
                std::cout << "Exiting Smart Process Manager...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
