#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "../include/ProcessMonitor.h"
#include "../include/ProcessControl.h"
#include "../include/Logger.h"

using namespace std;

// Helper function to center align a string.
string centerString(const string &s, int width) {
    int len = s.length();
    if (width <= len) return s;
    int pad = width - len;
    int padLeft = pad / 2;
    int padRight = pad - padLeft;
    return string(padLeft, ' ') + s + string(padRight, ' ');
}

// Helper function to print a horizontal line.
void printHorizontalLine(int pidWidth, int nameWidth, int statusWidth, int priorityWidth) {
    cout << "+" 
         << string(pidWidth, '-') << "+"
         << string(nameWidth, '-') << "+"
         << string(statusWidth, '-') << "+"
         << string(priorityWidth, '-') << "+"
         << endl;
}

// Prints the process table to the console with table borders.
void printProcesses(const vector<Process>& processes, int pidWidth = 5, int nameWidth = 25, int statusWidth = 12, int priorityWidth = 8) {
    // Print header.
    printHorizontalLine(pidWidth, nameWidth, statusWidth, priorityWidth);
    cout << "|" << centerString("PID", pidWidth)
         << "|" << centerString("Name", nameWidth)
         << "|" << centerString("Status", statusWidth)
         << "|" << centerString("Priority", priorityWidth)
         << "|" << endl;
    printHorizontalLine(pidWidth, nameWidth, statusWidth, priorityWidth);

    // Print each process row.
    for (const auto& proc : processes) {
        string displayName = proc.name;
        if (displayName.length() > nameWidth) {
            displayName = displayName.substr(0, nameWidth - 3) + "...";
        }
        cout << "|" << centerString(to_string(proc.pid), pidWidth)
             << "|" << centerString(displayName, nameWidth)
             << "|" << centerString(proc.status, statusWidth)
             << "|" << centerString(to_string(proc.priority), priorityWidth)
             << "|" << endl;
    }
    printHorizontalLine(pidWidth, nameWidth, statusWidth, priorityWidth);
}

int main() {
    int choice;
    int pid, newPriority;
    
    // Initialize loggers.
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
                cout << "Enter PID to kill: ";
                cin >> pid;
                if (killProcess(pid)) {
                    cout << "Process " << pid << " killed successfully." << endl;
                    ImplementationLogger::log(ImplementationLogger::INFO, "Killed process with PID " + to_string(pid));
                } else {
                    cout << "Failed to kill process " << pid << "." << endl;
                    ImplementationLogger::log(ImplementationLogger::LOG_ERROR, "Failed to kill process with PID " + to_string(pid));
                }
                break;
            }
            case 3: {
                cout << "Enter PID to change priority: ";
                cin >> pid;
                
                // Retrieve current processes to check if PID exists.
                auto processes = listProcesses();
                auto it = std::find_if(processes.begin(), processes.end(), [pid](const Process &p) {
                    return p.pid == pid;
                });
                if (it == processes.end()) {
                    cout << "[ERROR] Process ID " << pid << " not found. Please enter a valid PID." << endl;
                    ImplementationLogger::log(ImplementationLogger::LOG_ERROR, "Attempted to change priority for invalid PID " + to_string(pid));
                    break;
                }
                
                Process beforeChange = getProcessInfo(pid);
                cout << "Current priority for process " << pid << ": " << beforeChange.priority << endl;
                cout << "For Windows, use 1 (Idle) to 5 (High)." << endl;
                cout << "For Linux, enter desired nice value (-20 to 19): ";
                cin >> newPriority;
                if (changeProcessPriority(pid, newPriority)) {
                    Process afterChange = getProcessInfo(pid);
                    cout << "Priority changed successfully for process " << pid << "." << endl;
                    ImplementationLogger::log(ImplementationLogger::INFO, 
                        "Changed priority for PID " + to_string(pid) +
                        " from " + to_string(beforeChange.priority) +
                        " to " + to_string(afterChange.priority));
                } else {
                    cout << "Failed to change priority for process " << pid << "." << endl;
                    ImplementationLogger::log(ImplementationLogger::LOG_ERROR, "Failed to change priority for PID " + to_string(pid));
                }
                break;
            }
            case 4: {
                auto processes = listProcesses();
                ProcessLogger::update(processes);
                cout << "Process log updated (table format logged to file)." << endl;
                break;
            }
            case 5: {
                ImplementationLogger::log(ImplementationLogger::INFO, "Exiting SPM.");
                goto exit_loop;
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
