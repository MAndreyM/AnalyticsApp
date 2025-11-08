#include <iostream>
#include <string>

struct CommandLineOptions {
    std::string inputDirectory;
    std::string outputDirectory = ".";
    bool verbose = false;
    bool helpRequested = false;
};

class CommandLineParser {
public:
    CommandLineOptions parse(int argc, char* argv[]) {
        CommandLineOptions options;
        
        if (argc < 2) {
            options.helpRequested = true;
            return options;
        }
        
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-h" || arg == "--help") {
                options.helpRequested = true;
                return options;
            } else if (arg == "-v" || arg == "--verbose") {
                options.verbose = true;
            } else if (arg == "-o" || arg == "--output") {
                if (i + 1 < argc) {
                    options.outputDirectory = argv[++i];
                }
            } else {
                if (options.inputDirectory.empty()) {
                    options.inputDirectory = arg;
                }
            }
        }
        
        return options;
    }
    
    void printHelp(const std::string& programName) {
        std::cout << "Usage: " << programName << " [OPTIONS] INPUT_DIRECTORY\n\n"
                  << "Analyze student performance data from Excel files\n\n"
                  << "Arguments:\n"
                  << "  INPUT_DIRECTORY    Path to directory containing .xls files\n\n"
                  << "Options:\n"
                  << "  -o, --output DIR   Output directory for reports\n"
                  << "  -v, --verbose      Enable verbose output\n"
                  << "  -h, --help         Show this help message\n";
    }
};

int main(int argc, char* argv[]) {
    CommandLineParser parser;
    CommandLineOptions options = parser.parse(argc, argv);
    
    if (options.helpRequested) {
        parser.printHelp(argv[0]);
        return 0;
    }
    
    if (options.inputDirectory.empty()) {
        std::cerr << "Error: Input directory not specified\n";
        parser.printHelp(argv[0]);
        return 1;
    }
    
    std::cout << "Processing directory: " << options.inputDirectory << std::endl;
    std::cout << "Output directory: " << options.outputDirectory << std::endl;
    
    if (options.verbose) {
        std::cout << "Verbose mode enabled" << std::endl;
    }
    
    return 0;
}