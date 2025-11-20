#pragma once
#include <string>

class Config {
public:
    std::string inputDirectory;
    std::string outputDirectory = ".";
    bool verbose = false;

    bool parseArguments(int argc, char** argv);
    bool validate();

private:
    void showHelp();
    void showVersion();
};