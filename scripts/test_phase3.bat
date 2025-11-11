@echo off
setlocal enabledelayedexpansion

echo =========================================
echo    Phase 3 Verification Script
echo =========================================
echo.

echo [1/8] Checking build directory...
if not exist build (
    echo Creating build directory...
    mkdir build
)

cd build

echo [2/8] Configuring project...
cmake -G Ninja ..
if !errorlevel! neq 0 (
    echo ERROR: CMake configuration failed
    exit /b 1
)

echo [3/8] Building project...
ninja
if !errorlevel! neq 0 (
    echo ERROR: Build failed
    exit /b 1
)

echo [4/8] Running DataModels tests...
test_datamodels.exe
if !errorlevel! neq 0 (
    echo ERROR: DataModels tests failed
    exit /b 1
)

echo [5/8] Running GradeCalculator tests...
test_gradecalculator.exe
if !errorlevel! neq 0 (
    echo ERROR: GradeCalculator tests failed
    exit /b 1
)

echo [6/8] Running FileSystem tests...
test_filesystem.exe
if !errorlevel! neq 0 (
    echo ERROR: FileSystem tests failed
    exit /b 1
)

echo [7/8] Running DirectoryScanner tests...
test_directory_scanner.exe
if !errorlevel! neq 0 (
    echo ERROR: DirectoryScanner tests failed
    exit /b 1
)

echo [8/8] Testing demo programs...
bin\demo_datamodels.exe > nul
if !errorlevel! neq 0 (
    echo ERROR: Demo datamodels failed
    exit /b 1
)

bin\demo_directory_scanner.exe --help > nul
if !errorlevel! neq 0 (
    echo ERROR: Demo directory scanner failed
    exit /b 1
)

echo.
echo =========================================
echo    PHASE 3 VERIFICATION COMPLETED SUCCESSFULLY!
echo =========================================
echo.
echo 📊 Available executables:
echo    bin\analytics_app.exe         - Main application
echo    bin\demo_datamodels.exe       - Data models demonstration
echo    bin\demo_directory_scanner.exe - Directory scanner demonstration
echo.
echo 🧪 Test executables:
echo    test_datamodels.exe          - Data models tests
echo    test_gradecalculator.exe     - Grade calculator tests
echo    test_filesystem.exe          - File system tests
echo    test_directory_scanner.exe   - Directory scanner tests
echo.
echo 🚀 All Phase 3 components are working correctly!