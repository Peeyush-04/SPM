# CHANGELOG for Smart Process Manager (SPM)

## [Unreleased]

### Day 1 – Initial Project Setup and Basic Structure
- **Folder Structure Created:**  
  - `SPM/implementation/`
    - `src/` – Contains the main application file.
    - `include/` – Contains initial header files.
- **Files Added:**
  - **CMakeLists.txt:** An empty file to be configured later.
  - **src/main.cpp:** Added with basic structure to run the application.
  - **include/ProcessMonitor.h:**  
    - Contains a minimal `Process` structure and a placeholder function `listProcesses()` that returns a fixed list (e.g., System, Kernel, Init).
  - **include/ProcessControl.h:**  
    - Includes placeholder implementations for functions to kill processes and change process priorities.
  - **include/Logger.h:**  
    - Provides a simple logging function that writes basic process information to a log file.
- **Repository Initialization:**  
  - Git repository initialized and commit recorded with a message outlining the basic setup.

### Day 2 - Initial Setup
- Created `CMakeLists.txt` for project configuration.
- Added `main.cpp` to handle the process management.
- Implemented basic structure for logging, process listing, and control.
- Established header files for `Logger`, `ProcessMonitor`, and `ProcessControl`.

---
