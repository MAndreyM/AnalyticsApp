#include <iostream>
#include "Utils/Logger.h"
#include "Utils/Config.h"

int main(int argc, char** argv) {
    try {
        Logger::info("Starting Analytics App");

        // Парсинг аргументов командной строки
        Config config;
        if (!config.parseArguments(argc, argv)) {
            return 1;
        }

        // Валидация конфигурации
        if (!config.validate()) {
            Logger::error("Configuration validation failed");
            return 1;
        }

        Logger::setVerbose(config.verbose);

        Logger::info("Analytics App started successfully");
        Logger::info("Input directory: " + config.inputDirectory);
        Logger::info("Output directory: " + config.outputDirectory);

        // TODO: Реализация основной логики на следующих этапах
        Logger::info("Main functionality to be implemented in next stages");

        Logger::info("Analytics App finished successfully");
        return 0;

    } catch (const std::exception& e) {
        Logger::error("Fatal error: " + std::string(e.what()));
        return 1;
    }
}