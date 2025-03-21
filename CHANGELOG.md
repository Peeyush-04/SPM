# Changelog

All notable changes to this project will be documented in this file.

## [Unreleased] - 2025-03-22
### Added
- New features and improvements that are in development.
- Example: Dynamic logging system that generates two log files ("implementation_log.txt" and "process_log.txt") in a dedicated "logs" folder.

### Changed
- Code refactoring for modularity (all modules now implemented as header-only in the `include/` folder).
- Improved cross‑platform compatibility (supports both Linux and Windows with MinGW‑w64 for 64‑bit builds).

### Fixed
- Resolved minor issues with process control functions.
- Fixed bugs in log file generation and updates.

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
