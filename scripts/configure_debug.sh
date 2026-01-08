#!/bin/bash
# Файл: scripts/configure_debug.sh
# Скрипт для настройки отладочной сборки

#!/bin/bash
echo "Настройка отладочной сборки..."

# Создание каталога сборки если не существует
mkdir -p build-debug
cd build-debug

# Конфигурация CMake для отладки
cmake .. \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DENABLE_SANITIZERS=ON \
    -DENABLE_COVERAGE=ON \
    -DBUILD_TESTING=ON

echo "Отладочная сборка настроена. Для компиляции выполните:"
echo "cd build-debug && ninja"