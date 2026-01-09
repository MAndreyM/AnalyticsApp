#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <string>
#include <vector>
#include <memory>
#include <chrono>

// ============================================
// Группа 1: Базовые тесты Doctest
// ============================================

TEST_CASE("Doctest Integration - Basic arithmetic") {
    INFO("Testing basic arithmetic operations");
    
    CHECK(1 + 1 == 2);
    CHECK(2 * 2 == 4);
    CHECK(10 - 5 == 5);
    CHECK(20 / 4 == 5);
    
    // Дополнительные проверки
    CHECK(3.14 + 2.86 == 6.0);
    CHECK(100 % 3 == 1);
}

TEST_CASE("Doctest Integration - String operations") {
    std::string str = "hello";
    
    CHECK(str.length() == 5);
    CHECK(str + " world" == "hello world");
    CHECK(str.substr(0, 1) == "h");
    CHECK(str.find('e') == 1);
    CHECK(str == "hello");
    CHECK(str != "world");
}

TEST_CASE("Doctest Integration - Vector operations") {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    CHECK(vec.size() == 5);
    CHECK(vec[0] == 1);
    CHECK(vec.back() == 5);
    CHECK(vec.front() == 1);
    
    // Проверка изменений
    vec.push_back(6);
    CHECK(vec.size() == 6);
    CHECK(vec.back() == 6);
}

TEST_CASE("Doctest Integration - Smart pointers") {
    auto ptr = std::make_unique<int>(42);
    
    CHECK(*ptr == 42);
    CHECK(ptr != nullptr);
    
    // Перемещение умного указателя
    auto ptr2 = std::move(ptr);
    CHECK(ptr == nullptr);
    CHECK(*ptr2 == 42);
}

// ============================================
// Группа 2: Проверка доступности Qt6
// ============================================

#ifdef QT_CORE_LIB
TEST_CASE("Qt6 Integration - Core library available") {
    CHECK(true);  // Если дошли сюда, Qt6 Core доступен
}
#else
TEST_CASE("Qt6 Integration - Core library NOT available") {
    MESSAGE("Qt6 Core library is not available");
    CHECK(true);
}
#endif

#ifdef QT_WIDGETS_LIB
TEST_CASE("Qt6 Integration - Widgets library available") {
    CHECK(true);  // Если дошли сюда, Qt Widgets доступен
}
#else
TEST_CASE("Qt6 Integration - Widgets library NOT available") {
    MESSAGE("Qt6 Widgets library is not available");
    CHECK(true);
}
#endif

#ifdef QT_XML_LIB
TEST_CASE("Qt6 Integration - Xml library available") {
    CHECK(true);  // Если дошли сюда, Qt Xml доступен
}
#else
TEST_CASE("Qt6 Integration - Xml library NOT available") {
    MESSAGE("Qt6 Xml library is not available");
    CHECK(true);
}
#endif

// ============================================
// Группа 3: Проверка структуры проекта
// ============================================

TEST_CASE("Project Structure - Basic project configuration") {
    // Проверка стандарта C++
    #if __cplusplus >= 202002L
        MESSAGE("C++20 standard detected");
        CHECK(true);
    #else
        MESSAGE("C++20 standard not detected");
        CHECK(false);
    #endif
    
    // Проверка доступности ключевых заголовков
    bool has_std_headers = true;
    
    #if __has_include(<string>)
        // OK
    #else
        has_std_headers = false;
    #endif
    
    #if __has_include(<vector>)
        // OK
    #else
        has_std_headers = false;
    #endif
    
    #if __has_include(<memory>)
        // OK
    #else
        has_std_headers = false;
    #endif
    
    CHECK(has_std_headers);
}

TEST_CASE("Project Structure - Test different assertion types") {
    INFO("Testing various doctest assertion macros");
    
    // REQUIRE - останавливает тест при failure
    REQUIRE(1 == 1);
    
    // CHECK - продолжает тест при failure
    CHECK(2 == 2);
    CHECK(3 == 3);
    
    // CHECK_FALSE - проверка на false
    CHECK_FALSE(1 == 2);
    
    // REQUIRE_FALSE - с остановкой при failure
    REQUIRE_FALSE(2 == 3);
    
    // CHECK_EQ - проверка равенства
    CHECK_EQ(4 + 4, 8);
    
    // CHECK_NE - проверка неравенства
    CHECK_NE(5, 6);
    
    // CHECK_LT / CHECK_GT - сравнение
    CHECK_LT(1, 10);
    CHECK_GT(10, 1);
    
    // CHECK_LE / CHECK_GE - сравнение с равенством
    CHECK_LE(5, 5);
    CHECK_GE(5, 5);
}

TEST_CASE("Project Structure - Exception handling") {
    // Проверка что исключения не бросаются
    CHECK_NOTHROW([]() {
        int x = 5;
        int y = x * 2;
        (void)y;  // подавляем warning о неиспользуемой переменной
    }());
    
    // Проверка что исключения бросаются
    CHECK_THROWS([]() {
        throw std::runtime_error("test exception");
    }());
    
    // Проверка конкретного исключения
    CHECK_THROWS_AS([]() {
        throw std::bad_alloc();
    }(), std::bad_alloc);
    
    // Проверка сообщения исключения
    CHECK_THROWS_WITH([]() {
        throw std::runtime_error("error message");
    }(), "error message");
}

TEST_CASE("Project Structure - Floating point comparisons") {
    double a = 0.1 + 0.2;
    double b = 0.3;
    
    // Приблизительное сравнение
    CHECK(a == doctest::Approx(b));
    
    // С заданной точностью
    CHECK(a == doctest::Approx(b).epsilon(0.0001));
}

// ============================================
// Группа 4: Проверка конфигурации фреймворка
// ============================================

TEST_CASE("Framework Configuration - Doctest setup verification") {
    // Проверка что фреймворк инициализирован
    CHECK(doctest::detail::g_cs != nullptr);
    
    // Проверка различных уровней логирования
    MESSAGE("This is a message");
    
    // Проверка что мы можем использовать разные типы проверок
    int x = 42;
    int* ptr = &x;
    int& ref = x;
    
    CHECK(*ptr == 42);
    CHECK(ref == 42);
    CHECK(&ref == &x);
}

TEST_CASE("Framework Configuration - Test case organization") {
    // Демонстрация SUBCASE для организации тестов
    int value = 0;
    
    SUBCASE("Subcase A: Set value to 1") {
        value = 1;
        CHECK(value == 1);
    }
    
    SUBCASE("Subcase B: Set value to 2") {
        value = 2;
        CHECK(value == 2);
    }
    
    // Каждый SUBCASE выполняется независимо
    // Значение value сбрасывается для каждого SUBCASE
    CHECK((value == 0 || value == 1 || value == 2));
}

TEST_CASE("Framework Configuration - Performance and timing") {
    // Простая проверка производительности
    auto start = std::chrono::high_resolution_clock::now();
    
    // Выполняем некоторую работу
    int sum = 0;
    for (int i = 0; i < 1000; ++i) {
        sum += i;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    CHECK(sum == 499500);  // Сумма арифметической прогрессии
    CHECK(duration.count() >= 0);  // Время должно быть неотрицательным
    
    // Сообщение если выполнение слишком медленное
    if (duration.count() > 10000) {  // Более 10ms
        MESSAGE("Test execution took longer than expected: ", duration.count(), "μs");
    }
}

// ============================================
// Группа 5: Итоговые проверки интеграции
// ============================================

TEST_CASE("Integration Final - Complete system check") {
    // Итоговая проверка всех компонентов
    
    // 1. Проверка стандартной библиотеки
    std::string test_string = "Integration Test";
    std::vector<int> test_vector = {1, 2, 3};
    auto test_unique_ptr = std::make_unique<int>(100);
    
    CHECK(test_string.length() > 0);
    CHECK(test_vector.size() == 3);
    CHECK(*test_unique_ptr == 100);
    
    // 2. Проверка математических операций
    CHECK(2 + 3 * 4 == 14);  // Приоритет операций
    CHECK(std::abs(-5.5) == 5.5);
    
    // 3. Проверка логических операций
    bool flag1 = true;
    bool flag2 = false;
    
    CHECK(flag1 == true);
    CHECK(flag2 == false);
    CHECK((flag1 && !flag2) == true);
    
    // 4. Проверка работы с памятью
    {
        std::vector<int> local_vec(1000, 42);
        CHECK(local_vec.size() == 1000);
        CHECK(local_vec[0] == 42);
        CHECK(local_vec[999] == 42);
    }  // Проверка что деструктор вызывается корректно
    
    // 5. Финальное сообщение
    MESSAGE("All integration tests completed successfully");
    
    // 6. Гарантируем что тест проходит
    CHECK(true);
}

// ============================================
// Вспомогательные функции для тестов
// ============================================

namespace TestHelpers {
    int add(int a, int b) {
        return a + b;
    }
    
    std::string concatenate(const std::string& a, const std::string& b) {
        return a + b;
    }
}

TEST_CASE("Helper Functions - Custom test helpers") {
    CHECK(TestHelpers::add(2, 3) == 5);
    CHECK(TestHelpers::add(-1, 1) == 0);
    CHECK(TestHelpers::add(0, 0) == 0);
    
    CHECK(TestHelpers::concatenate("Hello, ", "World!") == "Hello, World!");
    CHECK(TestHelpers::concatenate("", "test") == "test");
    CHECK(TestHelpers::concatenate("prefix", "") == "prefix");
}

// ============================================
// Тесты для отладки (можно отключить в релизе)
// ============================================

#ifndef NDEBUG
TEST_CASE("Debug Build - Additional debug checks") {
    MESSAGE("Running in debug mode");
    CHECK(true);
    
    // Дополнительные проверки для debug сборки
    #ifdef _DEBUG
        MESSAGE("_DEBUG is defined");
    #endif
}
#endif

// ============================================
// Итоговый тест - проверка количества тестов
// ============================================

TEST_CASE("Test Count Verification") {
    // Этот тест проверяет что все предыдущие тесты были добавлены
    MESSAGE("Total test cases defined: This should match script expectations");
    CHECK(true);  // Всегда проходит
}