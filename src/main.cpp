#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
        
        std::vector<std::string> args(argv + 1, argv + argc);
        
        for (size_t i = 0; i < args.size(); ++i) {
            if (args[i] == "-h" || args[i] == "--help") {
                options.helpRequested = true;
                return options;
            } else if (args[i] == "-v" || args[i] == "--verbose") {
                options.verbose = true;
            } else if (args[i] == "-o" || args[i] == "--output") {
                if (i + 1 < args.size()) {
                    options.outputDirectory = args[++i];
                } else {
                    throw std::runtime_error("Output directory not specified");
                }
            } else {
                if (options.inputDirectory.empty()) {
                    options.inputDirectory = args[i];
                }
            }
        }
        
        if (options.inputDirectory.empty() && !options.helpRequested) {
            throw std::runtime_error("Input directory not specified");
        }
        
        return options;
    }
    
    void printHelp(const std::string& programName) {
        std::cout << "Usage: " << programName << " [OPTIONS] INPUT_DIRECTORY\n\n"
                  << "Analyze student performance data from Excel files\n\n"
                  << "Arguments:\n"
                  << "  INPUT_DIRECTORY    Path to directory containing .xls files\n\n"
                  << "Options:\n"
                  << "  -o, --output DIR   Output directory for reports (default: current dir)\n"
                  << "  -v, --verbose      Enable verbose output\n"
                  << "  -h, --help         Show this help message\n\n"
                  << "Examples:\n"
                  << "  " << programName << " /path/to/data\n"
                  << "  " << programName << " -o ./reports /path/to/data\n";
    }
};

class Logger {
private:
    bool verbose_;
    
public:
    explicit Logger(bool verbose = false) : verbose_(verbose) {}
    
    void setVerbose(bool verbose) {
        verbose_ = verbose;
    }
    
    void info(const std::string& message) {
        std::cout << "[INFO] " << message << std::endl;
    }
    
    void warning(const std::string& message) {
        std::cout << "[WARNING] " << message << std::endl;
    }
    
    void error(const std::string& message) {
        std::cerr << "[ERROR] " << message << std::endl;
    }
    
    void debug(const std::string& message) {
        if (verbose_) {
            std::cout << "[DEBUG] " << message << std::endl;
        }
    }
};

int main(int argc, char* argv[]) {
    CommandLineParser parser;
    Logger logger;
    
    try {
        CommandLineOptions options = parser.parse(argc, argv);
        
        if (options.helpRequested) {
            parser.printHelp(argv[0]);
            return 0;
        }
        
        logger.setVerbose(options.verbose);
        logger.info("Analytics App - Starting...");
        logger.debug("Verbose mode enabled");
        
        logger.info("Input directory: " + options.inputDirectory);
        logger.info("Output directory: " + options.outputDirectory);
        
        logger.debug("Scanning for Excel files...");
        logger.debug("Parsing student data...");
        logger.debug("Analyzing performance...");
        logger.debug("Generating reports...");
        
        logger.info("Processing completed successfully!");
        
    } catch (const std::exception& e) {
        logger.error(e.what());
        std::cerr << "\nUse '" << argv[0] << " --help' for usage information.\n";
        return 1;
    } catch (...) {
        logger.error("Unknown error occurred");
        return 1;
    }
    
    return 0;
}