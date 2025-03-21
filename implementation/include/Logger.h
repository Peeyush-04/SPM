#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <mutex>
#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(dir) _mkdir(dir)
#else
    #include <sys/stat.h>
    #define MKDIR(dir) mkdir(dir, 0755)
#endif

// Helper function to create a directory if it doesn't exist.
inline void createDirectory(const std::string& dir) {
    MKDIR(dir.c_str());
}

// ========================= Implementation Logger =========================
class ImplementationLogger {
public:
    enum LogLevel {
        INFO,
        DEBUG,
        LOG_ERROR
    };

    // Initializes the implementation logger.
    static void init(const std::string& logFilePath = "logs/implementation_log.txt") {
        std::lock_guard<std::mutex> guard(mutex_);
        createDirectory("logs");
        instance().logFile_.open(logFilePath, std::ios::app);
        if (!instance().logFile_.is_open()) {
            std::cerr << "Error: Could not open implementation log file: " << logFilePath << std::endl;
        }
    }

    // Logs a message at the specified level.
    static void log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> guard(mutex_);
        if (!instance().logFile_.is_open()) {
            std::cerr << "Implementation log file not open!" << std::endl;
            return;
        }
        std::time_t now = std::time(nullptr);
        char buf[80];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", std::localtime(&now));

        std::string levelStr;
        switch (level) {
            case INFO: levelStr = "INFO"; break;
            case DEBUG: levelStr = "DEBUG"; break;
            case LOG_ERROR: levelStr = "ERROR"; break;
            default: levelStr = "INFO"; break;
        }
        instance().logFile_ << "[" << buf << "] " << levelStr << ": " << message << std::endl;
    }

    static void close() {
        std::lock_guard<std::mutex> guard(mutex_);
        if (instance().logFile_.is_open()) {
            instance().logFile_.close();
        }
    }

private:
    ImplementationLogger() = default;
    ~ImplementationLogger() = default;
    ImplementationLogger(const ImplementationLogger&) = delete;
    ImplementationLogger& operator=(const ImplementationLogger&) = delete;

    static ImplementationLogger& instance() {
        static ImplementationLogger loggerInstance;
        return loggerInstance;
    }

    std::ofstream logFile_;
    static std::mutex mutex_;
};

std::mutex ImplementationLogger::mutex_;

// ============================ Process Logger =============================
class ProcessLogger {
public:
    // Initializes the process logger.
    static void init(const std::string& logFilePath = "logs/process_log.txt") {
        std::lock_guard<std::mutex> guard(mutex_);
        createDirectory("logs");
        instance().logFile_.open(logFilePath, std::ios::app);
        if (!instance().logFile_.is_open()) {
            std::cerr << "Error: Could not open process log file: " << logFilePath << std::endl;
        }
    }

    // Updates the process log with the current list of processes.
    // Expects a vector of Process structures (from ProcessMonitor.h).
    static void update(const std::vector<struct Process>& processes) {
        std::lock_guard<std::mutex> guard(mutex_);
        if (!instance().logFile_.is_open()) {
            std::cerr << "Process log file not open!" << std::endl;
            return;
        }
        std::time_t now = std::time(nullptr);
        char buf[80];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", std::localtime(&now));
        instance().logFile_ << "=== Process Log Update at " << buf << " ===" << std::endl;
        for (const auto& proc : processes) {
            instance().logFile_ << "PID: " << proc.pid << ", Name: " << proc.name << std::endl;
        }
        instance().logFile_ << "==========================================" << std::endl;
    }

    static void close() {
        std::lock_guard<std::mutex> guard(mutex_);
        if (instance().logFile_.is_open()) {
            instance().logFile_.close();
        }
    }
private:
    ProcessLogger() = default;
    ~ProcessLogger() = default;
    ProcessLogger(const ProcessLogger&) = delete;
    ProcessLogger& operator=(const ProcessLogger&) = delete;

    static ProcessLogger& instance() {
        static ProcessLogger loggerInstance;
        return loggerInstance;
    }

    std::ofstream logFile_;
    static std::mutex mutex_;
};

std::mutex ProcessLogger::mutex_;

#endif // LOGGER_H
