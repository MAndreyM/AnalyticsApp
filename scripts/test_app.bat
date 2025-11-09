@echo off

if not exist "build\bin\analytics_app.exe" (
    echo ERROR: Application not built. Run build.bat first.
    exit /b 1
)

echo Testing application...
build\bin\analytics_app.exe --help
echo.
build\bin\analytics_app.exe || echo Expected error when no input directory
echo.
build\bin\analytics_app.exe -v . || echo Expected error for demo