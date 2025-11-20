#pragma once
#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>

class Logger {
public:
    static void info(const std::string& message);
    static void error(const std::string& message);
    static void debug(const std::string& message);
    static void setVerbose(bool verbose);

private:
    static bool verboseMode;
    static std::string getCurrentTime();
    static void log(const std::string& level, const std::string& message);
};