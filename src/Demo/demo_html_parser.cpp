#include <iostream>
#include "../Utils/Logger.h"

int main(int argc, char** argv) {
    Logger::info("Starting Demo HTML Parser");

    if (argc < 2) {
        std::cerr << "Usage: demo_html_parser HTML_FILE" << std::endl;
        return 1;
    }

    std::string htmlFile = argv[1];
    Logger::info("Processing file: " + htmlFile);

    // TODO: Реализация парсера будет на следующих этапах
    Logger::info("Demo HTML Parser - functionality to be implemented");

    return 0;
}