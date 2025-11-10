#include "FileSystemUtils.h"
#include <algorithm>
#include <cctype>

bool FileSystemUtils::exists(const std::string& path) {
    return std::filesystem::exists(path);
}

bool FileSystemUtils::isDirectory(const std::string& path) {
    return std::filesystem::is_directory(path);
}

bool FileSystemUtils::createDirectory(const std::string& path) {
    return std::filesystem::create_directories(path);
}

std::string FileSystemUtils::getFileExtension(const std::string& filename) {
    std::filesystem::path filePath(filename);
    std::string extension = filePath.extension().string();
    
    // Приводим к нижнему регистру
    for (char& c : extension) {
        c = std::tolower(c);
    }
    
    return extension;
}

bool FileSystemUtils::isExcelFile(const std::string& filename) {
    std::string extension = getFileExtension(filename);
    return extension == ".xls";
}

std::vector<std::string> FileSystemUtils::getFilesWithExtension(const std::string& directory, const std::string& extension) {
    std::vector<std::string> result;
    
    if (!exists(directory) || !isDirectory(directory)) {
        return result;
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string fileExtension = getFileExtension(entry.path().string());
            if (fileExtension == extension) {
                result.push_back(entry.path().string());
            }
        }
    }
    
    return result;
}