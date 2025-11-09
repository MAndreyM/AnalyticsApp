@echo off
setlocal enabledelayedexpansion

echo ========================================
echo    Analytics App - Build Verification
echo ========================================
echo.

echo [1/4] Checking for CMake...
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: CMake is not installed
    exit /b 1
)

echo [2/4] Checking for Ninja...
where ninja >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: Ninja is not installed
    exit /b 1
)

echo [3/4] Checking MinGW-w64 compiler...
where g++ >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: MinGW-w64 g++ compiler not found
    exit /b 1
)

echo [4/4] Building project...
if not exist build mkdir build
cd build

cmake -G Ninja ..
if %errorlevel% neq 0 (
    echo ERROR: CMake configuration failed
    exit /b 1
)

ninja
if %errorlevel% neq 0 (
    echo ERROR: Build failed
    exit /b 1
)

if exist "bin\analytics_app.exe" (
    echo.
    echo ========================================
    echo    BUILD SUCCESSFUL!
    echo ========================================
    echo Executable: bin\analytics_app.exe
) else (
    echo ERROR: Executable not found
    exit /b 1
)

endlocal