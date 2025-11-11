#include <doctest/doctest.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include "FileProcessor/DirectoryScanner.h"
#include "Utils/FileSystemUtils.h"
#include "FileProcessor/ExcelFileFilter.h"

/**
 * @brief Вспомогательные утилиты для тестов
 */
namespace TestUtils {
    /**
     * @brief Создает тестовый файл с заданным содержимым
     */
    void createTestFile(const std::string& path, const std::string& content = "test content") {
        std::ofstream file(path);
        file << content;
        file.close();
    }
    
    /**
     * @brief Создает тестовую структуру директорий с разными типами файлов
     */
    void createTestDirectoryStructure(const std::string& basePath) {
        std::filesystem::create_directories(basePath + "/subdir1");
        std::filesystem::create_directories(basePath + "/subdir2/deep");
        std::filesystem::create_directories(basePath + "/empty_dir");
        
        // Excel файлы
        createTestFile(basePath + "/file1.xls");
        createTestFile(basePath + "/file2.XLS");  // uppercase
        createTestFile(basePath + "/file3.xls", "excel data");
        
        // Другие файлы
        createTestFile(basePath + "/file4.txt");
        createTestFile(basePath + "/file5.xlsx");  // wrong extension
        createTestFile(basePath + "/file6");       // no extension
        
        // Файлы в поддиректориях
        createTestFile(basePath + "/subdir1/file7.xls");
        createTestFile(basePath + "/subdir1/file8.doc");
        createTestFile(basePath + "/subdir2/file9.xls");
        createTestFile(basePath + "/subdir2/deep/file10.xls");
        createTestFile(basePath + "/subdir2/deep/file11.csv");
    }
    
    /**
     * @brief Рекурсивно удаляет директорию
     */
    void removeTestDirectory(const std::string& path) {
        std::filesystem::remove_all(path);
    }
    
    /**
     * @brief Проверяет содержит ли вектор определенный файл
     */
    bool containsFile(const std::vector<std::string>& files, const std::string& filename) {
        // Нормализуем путь для сравнения
        std::string normalized = std::filesystem::path(filename).string();
        return std::find(files.begin(), files.end(), normalized) != files.end();
    }
}

TEST_CASE("DirectoryScanner basic functionality") {
    DirectoryScanner scanner;
    
    SUBCASE("scan non-existent directory throws exception") {
        CHECK_THROWS_AS(scanner.findExcelFiles("/non/existent/path/12345"), std::runtime_error);
    }
    
    SUBCASE("scan file instead of directory throws exception") {
        // Создаем временный файл
        std::string tempFile = "test_temp_file.txt";
        TestUtils::createTestFile(tempFile);
        
        CHECK_THROWS_AS(scanner.findExcelFiles(tempFile), std::runtime_error);
        
        // Убираем за собой
        TestUtils::removeTestDirectory(tempFile);
    }
    
    SUBCASE("empty directory path throws exception") {
        CHECK_THROWS_AS(scanner.findExcelFiles(""), std::runtime_error);
    }
}

TEST_CASE("DirectoryScanner file filtering") {
    // Создаем временную директорию для тестов
    std::string testDir = "test_directory_scanner_filter";
    TestUtils::createTestDirectoryStructure(testDir);
    
    DirectoryScanner scanner;
    
    SUBCASE("finds all excel files recursively") {
        auto files = scanner.findExcelFiles(testDir);
        
        // Должны найти 6 Excel файлов: file1.xls, file2.XLS, file3.xls, file7.xls, file9.xls, file10.xls
        CHECK(files.size() == 6);
        
        // Проверяем что все найденные файлы имеют расширение .xls (регистронезависимо)
        for (const auto& file : files) {
            CHECK(FileSystemUtils::isExcelFile(file) == true);
        }
        
        // Проверяем статистику
        auto stats = scanner.getLastScanStatistics();
        CHECK(stats.excelFilesFound == 6);
        CHECK(stats.accessErrors == 0);
        CHECK(stats.isSuccessful() == true);
    }
    
    SUBCASE("correct files are found") {
        auto files = scanner.findExcelFiles(testDir);
        
        // Проверяем конкретные файлы
        CHECK(TestUtils::containsFile(files, testDir + "/file1.xls"));
        CHECK(TestUtils::containsFile(files, testDir + "/file2.XLS"));  // uppercase
        CHECK(TestUtils::containsFile(files, testDir + "/file3.xls"));
        CHECK(TestUtils::containsFile(files, testDir + "/subdir1/file7.xls"));
        CHECK(TestUtils::containsFile(files, testDir + "/subdir2/file9.xls"));
        CHECK(TestUtils::containsFile(files, testDir + "/subdir2/deep/file10.xls"));
        
        // Проверяем что НЕ Excel файлы не найдены
        CHECK_FALSE(TestUtils::containsFile(files, testDir + "/file4.txt"));
        CHECK_FALSE(TestUtils::containsFile(files, testDir + "/file5.xlsx"));
        CHECK_FALSE(TestUtils::containsFile(files, testDir + "/file6"));
        CHECK_FALSE(TestUtils::containsFile(files, testDir + "/subdir1/file8.doc"));
        CHECK_FALSE(TestUtils::containsFile(files, testDir + "/subdir2/deep/file11.csv"));
    }
    
    SUBCASE("empty directory returns empty list") {
        auto files = scanner.findExcelFiles(testDir + "/empty_dir");
        CHECK(files.empty());
        
        auto stats = scanner.getLastScanStatistics();
        CHECK(stats.excelFilesFound == 0);
        CHECK(stats.accessErrors == 0);
    }
    
    // Убираем тестовую директорию
    TestUtils::removeTestDirectory(testDir);
}

TEST_CASE("DirectoryScanner statistics") {
    std::string testDir = "test_directory_scanner_stats";
    TestUtils::createTestDirectoryStructure(testDir);
    
    DirectoryScanner scanner;
    
    SUBCASE("statistics are reset between scans") {
        auto files1 = scanner.findExcelFiles(testDir);
        auto stats1 = scanner.getLastScanStatistics();
        
        CHECK(stats1.excelFilesFound == 6);
        CHECK(stats1.totalFilesScanned > 0);
        CHECK(stats1.directoriesScanned > 0);
        
        // Сканируем пустую директорию
        auto files2 = scanner.findExcelFiles(testDir + "/empty_dir");
        auto stats2 = scanner.getLastScanStatistics();
        
        CHECK(stats2.excelFilesFound == 0);
        CHECK(stats2.totalFilesScanned == 0);
    }
    
    SUBCASE("scan duration is measured") {
        auto files = scanner.findExcelFiles(testDir);
        auto stats = scanner.getLastScanStatistics();
        
        CHECK(stats.scanDuration.count() >= 0);
        CHECK(stats.scanDuration.count() < 10000);  // reasonable time for small dir
    }
    
    SUBCASE("statistics print method works") {
        auto files = scanner.findExcelFiles(testDir);
        auto stats = scanner.getLastScanStatistics();
        
        // Просто проверяем что метод не падает
        CHECK_NOTHROW(stats.print());
    }
    
    TestUtils::removeTestDirectory(testDir);
}

TEST_CASE("ExcelFileFilter file validation") {
    SUBCASE("valid excel files") {
        CHECK(ExcelFileFilter::isExcelFile(std::filesystem::path("file.xls")) == true);
        CHECK(ExcelFileFilter::isExcelFile(std::filesystem::path("FILE.XLS")) == true);
        CHECK(ExcelFileFilter::isExcelFile(std::filesystem::path("path/to/file.xls")) == true);
        CHECK(ExcelFileFilter::isExcelFile(std::filesystem::path("file.with.dots.xls")) == true);
    }
    
    SUBCASE("invalid excel files") {
        CHECK(ExcelFileFilter::isExcelFile(std::filesystem::path("file.xlsx")) == false);
        CHECK(ExcelFileFilter::isExcelFile(std::filesystem::path("file.txt")) == false);
        CHECK(ExcelFileFilter::isExcelFile(std::filesystem::path("file")) == false);
        CHECK(ExcelFileFilter::isExcelFile(std::filesystem::path("")) == false);
        CHECK(ExcelFileFilter::isExcelFile(std::filesystem::path("file.doc")) == false);
        CHECK(ExcelFileFilter::isExcelFile(std::filesystem::path("file.xlsx")) == false);
    }
    
    SUBCASE("file extension normalization") {
        CHECK(ExcelFileFilter::normalizeExtension(".xls") == ".xls");
        CHECK(ExcelFileFilter::normalizeExtension(".XLS") == ".xls");
        CHECK(ExcelFileFilter::normalizeExtension(".Xls") == ".xls");
        CHECK(ExcelFileFilter::normalizeExtension("") == "");
        CHECK(ExcelFileFilter::normalizeExtension(".txt") == ".txt");
    }
}

TEST_CASE("DirectoryScanner edge cases") {
    DirectoryScanner scanner;
    
    SUBCASE("directory with only non-excel files") {
        std::string testDir = "test_no_excel_files";
        std::filesystem::create_directories(testDir);
        
        TestUtils::createTestFile(testDir + "/file1.txt");
        TestUtils::createTestFile(testDir + "/file2.pdf");
        TestUtils::createTestFile(testDir + "/file3.docx");
        
        auto files = scanner.findExcelFiles(testDir);
        CHECK(files.empty());
        
        auto stats = scanner.getLastScanStatistics();
        CHECK(stats.excelFilesFound == 0);
        CHECK(stats.totalFilesScanned == 3);
        
        TestUtils::removeTestDirectory(testDir);
    }
    
    SUBCASE("deep directory structure") {
        std::string testDir = "test_deep_structure";
        std::filesystem::create_directories(testDir + "/level1/level2/level3/level4");
        
        TestUtils::createTestFile(testDir + "/level1/level2/level3/level4/deep_file.xls");
        TestUtils::createTestFile(testDir + "/root_file.xls");
        
        auto files = scanner.findExcelFiles(testDir);
        CHECK(files.size() == 2);
        
        CHECK(TestUtils::containsFile(files, testDir + "/level1/level2/level3/level4/deep_file.xls"));
        CHECK(TestUtils::containsFile(files, testDir + "/root_file.xls"));
        
        TestUtils::removeTestDirectory(testDir);
    }
}

TEST_CASE("DirectoryScanner performance and robustness") {
    DirectoryScanner scanner;
    
    SUBCASE("multiple consecutive scans") {
        std::string testDir = "test_multiple_scans";
        TestUtils::createTestDirectoryStructure(testDir);
        
        // Первое сканирование
        auto files1 = scanner.findExcelFiles(testDir);
        auto stats1 = scanner.getLastScanStatistics();
        
        // Второе сканирование (должно работать идентично)
        auto files2 = scanner.findExcelFiles(testDir);
        auto stats2 = scanner.getLastScanStatistics();
        
        CHECK(files1.size() == files2.size());
        CHECK(stats1.excelFilesFound == stats2.excelFilesFound);
        
        TestUtils::removeTestDirectory(testDir);
    }
    
    SUBCASE("scan statistics accuracy") {
        std::string testDir = "test_stats_accuracy";
        std::filesystem::create_directories(testDir);
        
        // Создаем известную структуру
        TestUtils::createTestFile(testDir + "/file1.xls");
        TestUtils::createTestFile(testDir + "/file2.xls");
        TestUtils::createTestFile(testDir + "/file3.txt");
        
        auto files = scanner.findExcelFiles(testDir);
        auto stats = scanner.getLastScanStatistics();
        
        CHECK(stats.excelFilesFound == 2);
        CHECK(stats.totalFilesScanned == 3);  // все файлы, включая .txt
        
        TestUtils::removeTestDirectory(testDir);
    }
}