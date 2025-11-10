#include <doctest/doctest.h>
#include "Utils/FileSystemUtils.h"
#include <fstream>
#include <cstdio>

TEST_CASE("FileSystemUtils basic functionality") {
    SUBCASE("file extension detection") {
        CHECK(FileSystemUtils::getFileExtension("file.xls") == ".xls");
        CHECK(FileSystemUtils::getFileExtension("file.XLS") == ".xls");
        CHECK(FileSystemUtils::getFileExtension("file.docx") == ".docx");
        CHECK(FileSystemUtils::getFileExtension("file") == "");
    }
    
    SUBCASE("Excel file detection") {
        CHECK(FileSystemUtils::isExcelFile("report.xls") == true);
        CHECK(FileSystemUtils::isExcelFile("data.XLS") == true);
        CHECK(FileSystemUtils::isExcelFile("document.pdf") == false);
        CHECK(FileSystemUtils::isExcelFile("spreadsheet.xlsx") == false);
    }
}

TEST_CASE("FileSystemUtils directory operations") {
    std::string testDir = "test_temp_dir";
    
    SUBCASE("directory creation and check") {
        // Удаляем директорию если существует
        if (FileSystemUtils::exists(testDir)) {
            std::filesystem::remove_all(testDir);
        }
        
        CHECK(FileSystemUtils::exists(testDir) == false);
        CHECK(FileSystemUtils::createDirectory(testDir) == true);
        CHECK(FileSystemUtils::exists(testDir) == true);
        CHECK(FileSystemUtils::isDirectory(testDir) == true);
        
        // Cleanup
        std::filesystem::remove_all(testDir);
    }
}

TEST_CASE("FileSystemUtils file operations") {
    std::string testFile = "test_temp_file.txt";
    
    SUBCASE("file existence check") {
        // Создаем временный файл
        std::ofstream file(testFile);
        file << "test content";
        file.close();
        
        CHECK(FileSystemUtils::exists(testFile) == true);
        CHECK(FileSystemUtils::isDirectory(testFile) == false);
        
        // Cleanup
        std::remove(testFile.c_str());
    }
}