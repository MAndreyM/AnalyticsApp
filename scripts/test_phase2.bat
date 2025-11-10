@echo off
setlocal enabledelayedexpansion

echo =========================================
echo    Phase 2 Verification Script
echo =========================================
echo.

echo [1/7] Checking build directory...
if not exist build (
    echo Creating build directory...
    mkdir build
)

cd build

echo [2/7] Configuring project...
cmake -G Ninja ..
if !errorlevel! neq 0 (
    echo ERROR: CMake configuration failed
    exit /b 1
)

echo [3/7] Building project...
ninja
if !errorlevel! neq 0 (
    echo ERROR: Build failed
    exit /b 1
)

echo [4/7] Running DataModels tests...
test_datamodels.exe
if !errorlevel! neq 0 (
    echo ERROR: DataModels tests failed
    exit /b 1
)

echo [5/7] Running GradeCalculator tests...
test_gradecalculator.exe
if !errorlevel! neq 0 (
    echo ERROR: GradeCalculator tests failed
    exit /b 1
)

echo [6/7] Running FileSystem tests...
test_filesystem.exe
if !errorlevel! neq 0 (
    echo ERROR: FileSystem tests failed
    exit /b 1
)

echo [7/7] Testing demo program...
bin\demo_datamodels.exe > nul
if !errorlevel! neq 0 (
    echo ERROR: Demo program failed
    exit /b 1
)

echo.
echo =========================================
echo    PHASE 2 VERIFICATION COMPLETED SUCCESSFULLY!
echo =========================================
echo.
echo Available executables:
echo    bin\analytics_app.exe    - Main application
echo    bin\demo_datamodels.exe  - Demonstration program
echo    test_datamodels.exe      - Data models tests
echo    test_gradecalculator.exe - Grade calculator tests
echo    test_filesystem.exe      - File system tests
echo.
echo All Phase 2 components are working correctly!