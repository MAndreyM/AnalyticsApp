@echo off
setlocal enabledelayedexpansion

echo ========================================
echo    AnalyticsApp - Complete Test Suite
echo ========================================
echo.

echo [1/4] Running Phase 3 verification...
call scripts\test_phase3.bat
if !errorlevel! neq 0 (
    echo ERROR: Phase 3 verification failed
    exit /b 1
)

echo [2/4] Running integration tests...
call scripts\test_integration.bat
if !errorlevel! neq 0 (
    echo ERROR: Integration tests failed
    exit /b 1
)

echo [3/4] Running all unit tests with ctest...
cd build
ctest --output-on-failure
if !errorlevel! neq 0 (
    echo ERROR: Some unit tests failed
    exit /b 1
)

echo [4/4] Testing demo programs functionality...
bin\demo_directory_scanner.exe . > nul
if !errorlevel! neq 0 (
    echo ERROR: Demo directory scanner test failed
    exit /b 1
)

bin\demo_datamodels.exe > nul
if !errorlevel! neq 0 (
    echo ERROR: Demo datamodels test failed
    exit /b 1
)

echo.
echo ========================================
echo    🎉 ALL TESTS PASSED SUCCESSFULLY!
echo ========================================
echo.
echo 📋 Test Summary:
echo    ✅ Phase 3 verification
echo    ✅ Integration tests  
echo    ✅ All unit tests (ctest)
echo    ✅ Demo programs
echo.
echo 🚀 Application is fully functional and ready for use!