#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Analytics App - Starting..." << std::endl;
    
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " INPUT_DIRECTORY" << std::endl;
        return 1;
    }
    
    std::string inputDir = argv[1];
    std::cout << "Processing directory: " << inputDir << std::endl;
    
    return 0;
}