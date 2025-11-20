#include "Config.h"
#include <iostream>
#include <filesystem>

bool Config::parseArguments(int argc, char** argv) {
    if (argc < 2) {
        showHelp();
        return false;
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            showHelp();
            return false;
        } else if (arg == "-v" || arg == "--version") {
            showVersion();
            return false;
        } else if (arg == "--verbose") {
            verbose = true;
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                outputDirectory = argv[++i];
            } else {
                std::cerr << "Error: Output directory not specified" << std::endl;
                return false;
            }
        } else {
            // Первый не-флаг аргумент - входная директория
            if (inputDirectory.empty()) {
                inputDirectory = arg;
            }
        }
    }

    return true;
}

bool Config::validate() {
    if (inputDirectory.empty()) {
        std::cerr << "Error: Input directory not specified" << std::endl;
        return false;
    }

    if (!std::filesystem::exists(inputDirectory)) {
        std::cerr << "Error: Input directory does not exist: " << inputDirectory << std::endl;
        return false;
    }

    // Создание выходной директории, если не существует
    if (!std::filesystem::exists(outputDirectory)) {
        std::filesystem::create_directories(outputDirectory);
    }

    return true;
}

void Config::showHelp() {
    std::cout << "Analytics App - Analysis of student performance\n\n"
              << "Usage: analytics_app [OPTIONS] INPUT_DIRECTORY\n\n"
              << "Options:\n"
              << "  -h, --help           Show this help message\n"
              << "  -v, --version        Show version information\n"
              << "  -o, --output DIR     Set output directory (default: current directory)\n"
              << "  --verbose            Enable verbose logging\n\n"
              << "Examples:\n"
              << "  analytics_app /path/to/reports\n"
              << "  analytics_app -o /path/to/output --verbose /path/to/reports\n";
}

void Config::showVersion() {
    std::cout << "Analytics App version 0.1.0\n";
}