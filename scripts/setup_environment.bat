@echo off
setlocal

echo ========================================
echo    Analytics App - MinGW-w64 Setup
echo ========================================
echo.

echo [1/3] Checking for MinGW-w64...
where g++ >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: MinGW-w64 g++ compiler not found in PATH
    exit /b 1
)

echo [2/3] Checking compiler version...
g++ --version

echo [3/3] Creating development shortcuts...
echo @echo off > build.bat
echo mkdir build 2^>nul >> build.bat
echo cd build >> build.bat
echo cmake -G Ninja .. >> build.bat
echo ninja >> build.bat
echo cd .. >> build.bat

echo @echo off > clean.bat
echo if exist build rmdir /s /q build >> clean.bat

echo.
echo ========================================
echo    SETUP COMPLETED SUCCESSFULLY!
echo ========================================
echo.

endlocal