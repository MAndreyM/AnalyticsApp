#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
//#include <doctest/doctest.h>
#include "../src/Utils/Config.h"
#include <filesystem>

TEST_CASE("Config argument parsing") {
    SUBCASE("Help argument") {
        Config config;
        const char* argv[] = {"app", "--help"};
        CHECK(config.parseArguments(2, const_cast<char**>(argv)) == false);
    }

    SUBCASE("Version argument") {
        Config config;
        const char* argv[] = {"app", "--version"};
        CHECK(config.parseArguments(2, const_cast<char**>(argv)) == false);
    }

    SUBCASE("Input directory argument") {
        Config config;
        const char* argv[] = {"app", "/tmp"};
        CHECK(config.parseArguments(2, const_cast<char**>(argv)) == true);
        CHECK(config.inputDirectory == "/tmp");
    }

    SUBCASE("Output directory argument") {
        Config config;
        const char* argv[] = {"app", "-o", "/output", "/input"};
        CHECK(config.parseArguments(4, const_cast<char**>(argv)) == true);
        CHECK(config.outputDirectory == "/output");
        CHECK(config.inputDirectory == "/input");
    }

    SUBCASE("Verbose flag") {
        Config config;
        const char* argv[] = {"app", "--verbose", "/input"};
        CHECK(config.parseArguments(3, const_cast<char**>(argv)) == true);
        CHECK(config.verbose == true);
        CHECK(config.inputDirectory == "/input");
    }
}