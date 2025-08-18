#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <cstdarg>

enum class LogLevel {
    LOG_DEBUG_ULTRA,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
};

enum LoggerFlags {
    LOG_FLAG_NONE = 0,
    LOG_FLAG_NO_TIMESTAMP = 1 << 0,
    LOG_FLAG_NO_LEVEL = 1 << 1
};

class Logger {
public:
    Logger();
    ~Logger();

    void init(const std::string& normalFile, const std::string& errorFile,
        LogLevel level = LogLevel::LOG_INFO, int flags = LOG_FLAG_NONE);

    void setLevel(LogLevel level);
    void log(LogLevel level, const char* fmt, ...);

    // Convenience wrappers
    void debug(const char* fmt, ...);
    void debugUltra(const char* fmt, ...);
    void info(const char* fmt, ...);
    void warn(const char* fmt, ...);
    void error(const char* fmt, ...);

private:
    void logInternal(std::ofstream& stream, LogLevel level, const char* fmt, va_list args);
    std::string getTimestamp() const;
    std::ofstream logNormal;
    std::ofstream logError;
    LogLevel currentLevel;
    int loggerFlags;
    std::mutex mtx;

    // ANSI colors
    static constexpr const char* COLOR_RESET = "\x1b[0m";
    static constexpr const char* COLOR_RED = "\x1b[31m";
    static constexpr const char* COLOR_YELLOW = "\x1b[33m";
    static constexpr const char* COLOR_GREEN = "\x1b[32m";
    static constexpr const char* COLOR_CYAN = "\x1b[36m";
};

extern Logger logger;
