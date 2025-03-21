#include <iostream>
#include <vector>

#include "../include/ProcessMonitor.h"
#include "../include/ProcessControl.h"
#include "../include/Logger.h"

using namespace std;

void printProcesses(const vector<Process>& processes) {
    cout << "PID\tName" << endl;
    cout << "----------------------" << endl;
    for (const auto &proc : processes) {
        cout << proc.pid << "\t" << proc.name << endl;
    }
}

int main() {
    int choice;
    // Initialize both loggers.
    ImplementationLogger::init("logs/implementation_log.txt");
    ProcessLogger::init("logs/process_log.txt");
    ImplementationLogger::log(ImplementationLogger::INFO, "SPM started.");

    while (true) {
        cout << "\n=== Smart Process Manager (SPM) ===" << endl;
        cout << "1. List Processes" << endl;
        cout << "2. Kill Process" << endl;
        cout << "3. Change Process Priority" << endl;
        cout << "4. Update Process Log" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                ImplementationLogger::log(ImplementationLogger::INFO, "Listing processes.");
                auto processes = listProcesses();
                printProcesses(processes);
                break;
            }
            case 2: {
                int pid;
                cout << "Enter PID to kill: ";
                cin >> pid;
                if (killProcess(pid)) {
                    cout << "Process " << pid << " killed successfully." << endl;
                    ImplementationLogger::log(ImplementationLogger::INFO, "Killed process with PID " + std::to_string(pid));
                } else {
                    cout << "Failed to kill process " << pid << "." << endl;
                    ImplementationLogger::log(ImplementationLogger::LOG_ERROR, "Failed to kill process with PID " + std::to_string(pid));
                }
                break;
            }
            case 3: {
                int pid, newPriority;
                cout << "Enter PID to change priority: ";
                cin >> pid;
                cout << "For Windows, use 1 (Idle) to 5 (High)." << endl;
                cout << "For Linux, enter nice value (-20 to 19): ";
                cin >> newPriority;
                if (changeProcessPriority(pid, newPriority)) {
                    cout << "Priority changed successfully for process " << pid << "." << endl;
                    ImplementationLogger::log(ImplementationLogger::INFO, "Changed priority for PID " + std::to_string(pid) + " to " + std::to_string(newPriority));
                } else {
                    cout << "Failed to change priority for process " << pid << "." << endl;
                    ImplementationLogger::log(ImplementationLogger::LOG_ERROR, "Failed to change priority for PID " + std::to_string(pid));
                }
                break;
            }
            case 4: {
                auto processes = listProcesses();
                ProcessLogger::update(processes);
                cout << "Process log updated." << endl;
                break;
            }
            case 5: {
                ImplementationLogger::log(ImplementationLogger::INFO, "Exiting SPM.");
                goto exit_loop;  // using goto to break out of the loop for clarity
            }
            default: {
                cout << "Invalid choice! Try again." << endl;
                ImplementationLogger::log(ImplementationLogger::DEBUG, "User entered an invalid menu choice.");
                break;
            }
        }
    }
exit_loop:
    ImplementationLogger::close();
    ProcessLogger::close();
    return 0;
}
