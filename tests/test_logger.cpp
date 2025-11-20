#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../src/Utils/Logger.h"

TEST_CASE("Logger basic functionality") {
    SUBCASE("Verbose mode control") {
        Logger::setVerbose(false);
        Logger::setVerbose(true);
        // Проверка, что не падает при вызове методов
        CHECK_NOTHROW(Logger::info("Test info message"));
        CHECK_NOTHROW(Logger::error("Test error message"));
        CHECK_NOTHROW(Logger::debug("Test debug message"));
    }

    SUBCASE("Log levels work without exceptions") {
        // Проверяем, что все уровни логирования работают без исключений
        CHECK_NOTHROW(Logger::info("Info test"));
        CHECK_NOTHROW(Logger::error("Error test"));
        CHECK_NOTHROW(Logger::debug("Debug test"));
    }
}