#include "Logger.h"

bool Logger::verboseMode = false;

void Logger::info(const std::string& message) {
    log("INFO", message);
}

void Logger::error(const std::string& message) {
    log("ERROR", message);
}

void Logger::debug(const std::string& message) {
    if (verboseMode) {
        log("DEBUG", message);
    }
}

void Logger::setVerbose(bool verbose) {
    verboseMode = verbose;
}

std::string Logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void Logger::log(const std::string& level, const std::string& message) {
    std::cout << "[" << getCurrentTime() << "] "
              << "[" << level << "] "
              << message << std::endl;
}
