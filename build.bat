@echo off
echo Building Analytics App...
if not exist build mkdir build
cd build
cmake -G Ninja ..
ninja
if %errorlevel% equ 0 (
    echo Build successful!
) else (
    echo Build failed!
)
cd ..