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
            std::cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                auto processes = ProcessMonitor::listProcesses();
                std::cout << "Running Processes:\nPID\t\tName\n-----------------------------\n";
                for (const auto& proc : processes) {
                    std::cout << proc.pid << "\t\t" << proc.name << "\n";
                }
                break;
            }
            case 2: {
                int pid;
                std::cout << "Enter PID to kill: ";
                if (!(std::cin >> pid)) {
                    std::cout << "Invalid PID. Please enter a number.\n";
                    clearInputBuffer();
                    continue;
                }
                if (ProcessControl::killProcess(pid))
                    std::cout << "Process " << pid << " killed successfully.\n";
                else
                    std::cout << "Failed to kill process " << pid << ".\n";
                break;
            }
            case 3: {
                int pid, newPriority;
                std::cout << "Enter PID to change priority: ";
                if (!(std::cin >> pid)) {
                    std::cout << "Invalid PID. Please enter a number.\n";
                    clearInputBuffer();
                    continue;
                }
                std::cout << "Priority Levels:\n1. Idle\n2. Below Normal\n3. Normal\n4. Above Normal\n5. High\n";
                std::cout << "Enter new priority (1-5): ";
                if (!(std::cin >> newPriority) || newPriority < 1 || newPriority > 5) {
                    std::cout << "Invalid priority. Please enter a number between 1 and 5.\n";
                    clearInputBuffer();
                    continue;
                }
                if (ProcessControl::changeProcessPriority(pid, newPriority))
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

