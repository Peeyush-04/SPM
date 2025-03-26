# Changelog

All notable changes to this project will be documented in this file.

## Released - 2025-03-22
### Added
- **Dynamic Table Logging:**  
  - Process table output is now formatted with vertical and horizontal borders.
  - The table is center-aligned in each column (PID, Status, Priority) while the Name column has a fixed width (25 characters) and truncates longer names with "..." for neat display.
  - The same table format is used both on the console and when logging to the process log file.
  
### Changed
- Updated process table printing to support center alignment for numeric columns and dynamic truncation for long process names.
- Enhanced the ProcessLogger module to log the process table in the same table format to file.
- Minor refactoring to keep table formatting code modular and maintainable.

### Fixed
- Corrected alignment issues in the process table display compared to previous releases.
- Improved consistency between console output and file log formatting.

---

## 2025-03-21
### Added
- Integrated Windows (MinGW‑w64) support alongside Linux.
- Implemented two logging modules:
  - **ImplementationLogger** for general event logging.
  - **ProcessLogger** for logging the current process list.
- Modularized code: Process monitoring, process control, and logging functionality are now placed in the `include/` folder.

### Changed
- Updated menu system to use a `switch-case` statement for cleaner syntax.
- Refactored build process to support 64‑bit architecture.

### Fixed
- Addressed issues with relative include paths.
- Resolved naming conflicts (e.g., renaming the error log level from `ERROR` to `LOG_ERROR`).

---

## 2025-03-15
### Added
- Initial release of the Smart Process Manager (SPM) with basic process monitoring and control.
- Simple logging functionality and CLI-based user interface.
