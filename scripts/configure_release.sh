#!/bin/bash
# Файл: scripts/configure_release.sh
# Скрипт для настройки релизной сборки

#!/bin/bash
echo "Настройка релизной сборки..."

# Создание каталога сборки если не существует
mkdir -p build-release
cd build-release

# Конфигурация CMake для релиза
cmake .. \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DENABLE_IPO=ON \
    -DBUILD_TESTING=ON

echo "Релизная сборка настроена. Для компиляции выполните:"
echo "cd build-release && ninja"