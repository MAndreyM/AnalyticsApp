@echo off
echo 📚 Generating Doxygen documentation...

:: Проверка CMake
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ CMake not found. Please install CMake.
    exit /b 1
)

:: Сборка документации
if not exist build mkdir build
cd build

echo 🔨 Configuring project...
cmake ..

echo 📖 Generating documentation...
cmake --build . --target docs

echo.
echo ✅ Documentation generated successfully!
echo 📂 Location: %CD%\docs\html\index.html
echo.
echo To view documentation: start docs\html\index.html

cd ..