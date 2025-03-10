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
## Features:
- **Implemented process management functionality**:
  - **Listing processes**: Added functionality to list running processes with their PIDs and names.
  - **Kill process**: Implemented functionality to kill a running process by its PID.
  - **Change process priority**: Added feature to change the priority of a process (Idle, Below Normal, Normal, Above Normal, High).

- **Refactored code**:
  - Moved function definitions directly into **header files** (`ProcessMonitor.h` and `ProcessControl.h`) for ease of use and improved compilation process.
  - Updated header files to contain inline function implementations to avoid the need for separate `.cpp` files.

## Build System:
- **CMake configuration**:
  - Fixed the `CMakeLists.txt` to set the correct `PROJECT_ROOT_DIR` path, resolving issues with locating source files during the build process.
  - Configured **CMake** to properly reference the updated project structure where source files are in the `src/` folder and headers are in the `include/` folder.
  - Set **output directories** (`bin/`, `lib/`, and `obj/`) to ensure all build artifacts are placed in the `build/` folder.
  - Enabled compilation of the project with **MinGW Makefiles** to ensure smooth building on Windows with the `g++` compiler.

## Bug Fixes:
- Corrected path issues in the `CMakeLists.txt` which caused the build process to fail due to incorrect referencing of source files.

### Notes:
- The CMake build was tested, and now the build artifacts (like executables) are placed in the correct `build/bin/` directory.
- The process management system is now functional and can be easily extended to add more features.
---
