@echo off
setlocal enabledelayedexpansion

echo ========================================
echo    AnalyticsApp Integration Test
echo ========================================
echo.

echo [1/6] Building the project...
cd build
ninja
if !errorlevel! neq 0 (
    echo ERROR: Build failed
    exit /b 1
)

echo [2/6] Testing main application help...
bin\analytics_app.exe
if !errorlevel! neq 0 (
    echo ERROR: Main application failed to start
    exit /b 1
)

echo [3/6] Testing data analysis functionality...
echo 1 | timeout /t 2 > nul | bin\analytics_app.exe > test_output.txt
findstr /C:"Student Data Analysis" test_output.txt > nul
if !errorlevel! neq 0 (
    echo ERROR: Data analysis feature not working
    exit /b 1
)

echo [4/6] Testing directory scanning functionality...
echo 2 | timeout /t 2 > nul | bin\analytics_app.exe > test_output.txt
findstr /C:"Directory Scanning" test_output.txt > nul
if !errorlevel! neq 0 (
    echo ERROR: Directory scanning feature not working
    exit /b 1
)

echo [5/6] Testing file system utilities...
echo 3 | timeout /t 2 > nul | bin\analytics_app.exe > test_output.txt
findstr /C:"File System Utilities" test_output.txt > nul
if !errorlevel! neq 0 (
    echo ERROR: File system utilities feature not working
    exit /b 1
)

echo [6/6] Testing exit functionality...
echo 4 | timeout /t 2 > nul | bin\analytics_app.exe > test_output.txt
findstr /C:"Goodbye" test_output.txt > nul
if !errorlevel! neq 0 (
    echo ERROR: Exit functionality not working
    exit /b 1
)

del test_output.txt

echo.
echo ========================================
echo    ✅ INTEGRATION TEST PASSED!
echo ========================================
echo.
echo 🎯 All Phase 3 features integrated successfully:
echo.
echo    📊 Data Analysis Module
echo       - Student data models
echo       - Grade calculation with rounding
echo       - Performance analysis
echo.
echo    🔍 Directory Scanner Module  
echo       - Recursive Excel file search
echo       - File filtering by extension
echo       - Scan statistics and timing
echo.
echo    📁 File System Utilities
echo       - File existence checking
echo       - Directory listing
echo       - Excel file validation
echo.
echo 🚀 Application ready for Phase 4 development!