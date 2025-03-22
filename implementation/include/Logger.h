#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <mutex>
#include <sstream>
#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(dir) _mkdir(dir)
#else
    #include <sys/stat.h>
    #define MKDIR(dir) mkdir(dir, 0755)
#endif

// Helper: Create a directory if it doesn't exist.
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

    // Initialize the implementation logger.
    static void init(const std::string& logFilePath = "logs/implementation_log.txt") {
        std::lock_guard<std::mutex> guard(mutex_);
        createDirectory("logs");
        instance().logFile_.open(logFilePath, std::ios::app);
        if (!instance().logFile_.is_open()) {
            std::cerr << "Error: Could not open implementation log file: " << logFilePath << std::endl;
        }
    }

    // Log a message at the specified level.
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
    // Initialize the process logger.
    static void init(const std::string& logFilePath = "logs/process_log.txt") {
        std::lock_guard<std::mutex> guard(mutex_);
        createDirectory("logs");
        instance().logFile_.open(logFilePath, std::ios::app);
        if (!instance().logFile_.is_open()) {
            std::cerr << "Error: Could not open process log file: " << logFilePath << std::endl;
        }
    }

    // Updates the process log with the current list of processes in table format.
    static void update(const std::vector<struct Process>& processes) {
        std::ostringstream oss;
        int pidWidth = 5, nameWidth = 25, statusWidth = 12, priorityWidth = 8;
        
        // Helper lambda to center align a string.
        auto centerString = [](const std::string &s, int width) -> std::string {
            int len = s.length();
            if(width <= len) return s;
            int pad = width - len;
            int padLeft = pad / 2;
            int padRight = pad - padLeft;
            return std::string(padLeft, ' ') + s + std::string(padRight, ' ');
        };
        
        // Helper lambda to create a horizontal line.
        auto horizontalLine = [&]() -> std::string {
            return "+" + std::string(pidWidth, '-') + "+" + std::string(nameWidth, '-') +
                   "+" + std::string(statusWidth, '-') + "+" + std::string(priorityWidth, '-') + "+\n";
        };
        
        oss << horizontalLine();
        oss << "|" << centerString("PID", pidWidth)
            << "|" << centerString("Name", nameWidth)
            << "|" << centerString("Status", statusWidth)
            << "|" << centerString("Priority", priorityWidth)
            << "|\n";
        oss << horizontalLine();
        for(const auto &proc : processes) {
            std::string displayName = proc.name;
            if(displayName.length() > nameWidth) {
                displayName = displayName.substr(0, nameWidth - 3) + "...";
            }
            oss << "|" << centerString(std::to_string(proc.pid), pidWidth)
                << "|" << centerString(displayName, nameWidth)
                << "|" << centerString(proc.status, statusWidth)
                << "|" << centerString(std::to_string(proc.priority), priorityWidth)
                << "|\n";
        }
        oss << horizontalLine();
        
        logTable(oss.str());
    }
    
    // Logs a table string to the process log file.
    static void logTable(const std::string &tableStr) {
        std::lock_guard<std::mutex> guard(mutex_);
        if (!instance().logFile_.is_open()) {
            std::cerr << "Process log file not open!" << std::endl;
            return;
        }
        instance().logFile_ << tableStr << std::endl;
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
