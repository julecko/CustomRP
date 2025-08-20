#include "pch/pch.h"
#include "Logger.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdarg>
#include <filesystem>

namespace fs = std::filesystem;

Logger logger;

static const char* levelNames[] = {
    "\x1b[36mDEBUG ULTRA\x1b[0m",
    "\x1b[36mDEBUG\x1b[0m",
    "\x1b[32mINFO\x1b[0m",
    "\x1b[33mWARN\x1b[0m",
    "\x1b[31mERROR\x1b[0m"
};

Logger::Logger() : currentLevel(LogLevel::LOG_DEBUG_ULTRA), loggerFlags(LOG_FLAG_NONE) {}

Logger::~Logger() {
    if (logNormal.is_open()) logNormal.close();
    if (logError.is_open()) logError.close();
}

void Logger::init(const std::string& normalFile, const std::string& errorFile, LogLevel level, int flags) {
    std::lock_guard<std::mutex> lock(mtx);

    try {
        if (!normalFile.empty())
            fs::create_directories(fs::path(normalFile).parent_path());
        if (!errorFile.empty())
            fs::create_directories(fs::path(errorFile).parent_path());
    }
    catch (...) {
        std::cerr << "Failed to create log directories\n";
    }

    logNormal.open(normalFile, std::ios::app);
    logError.open(errorFile, std::ios::app);
    currentLevel = level;
    loggerFlags = flags;

    if (!logNormal.is_open() || !logError.is_open()) {
        std::cerr << "Failed to open log files\n";
    }
}

void Logger::setLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(mtx);
    currentLevel = level;
}

void Logger::log(LogLevel level, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    if (level >= currentLevel) {
        std::lock_guard<std::mutex> lock(mtx);
        if (level == LogLevel::LOG_ERROR || level == LogLevel::LOG_WARN)
            logInternal(logError, level, fmt, args);
        else
            logInternal(logNormal, level, fmt, args);
    }
    va_end(args);
}

void Logger::debug(const char* fmt, ...) {
#ifdef DEBUG_MODE
    va_list args;
    va_start(args, fmt);
    std::lock_guard<std::mutex> lock(mtx);
    logInternal(logNormal, LogLevel::DEBUG, fmt, args);
    va_end(args);
#endif
}

void Logger::debugUltra(const char* fmt, ...) {
#ifdef DEBUG_MODE
    va_list args;
    va_start(args, fmt);
    std::lock_guard<std::mutex> lock(mtx);
    logInternal(logNormal, LogLevel::DEBUG_ULTRA, fmt, args);
    va_end(args);
#endif
}

void Logger::info(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::lock_guard<std::mutex> lock(mtx);
    logInternal(logNormal, LogLevel::LOG_INFO, fmt, args);
    va_end(args);
}

void Logger::warn(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::lock_guard<std::mutex> lock(mtx);
    logInternal(logError, LogLevel::LOG_WARN, fmt, args);
    va_end(args);
}

void Logger::error(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::lock_guard<std::mutex> lock(mtx);
    logInternal(logError, LogLevel::LOG_ERROR, fmt, args);
    va_end(args);
}

void Logger::logInternal(std::ofstream& stream, LogLevel level, const char* fmt, va_list args) {
    if (!stream.is_open()) return;

    std::ostringstream oss;

    if (!(loggerFlags & LOG_FLAG_NO_TIMESTAMP)) {
        oss << "[" << getTimestamp() << "] ";
    }
    if (!(loggerFlags & LOG_FLAG_NO_LEVEL)) {
        oss << "[" << levelNames[static_cast<int>(level)] << "] ";
    }

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    oss << buffer << "\n";

    stream << oss.str();
    stream.flush();
}

std::string Logger::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#if defined(_MSC_VER)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
