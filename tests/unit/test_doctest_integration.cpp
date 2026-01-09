#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <string>

// Простой тест для проверки интеграции Doctest
TEST_SUITE("Doctest Integration") {
    TEST_CASE("Basic arithmetic") {
        CHECK(1 + 1 == 2);
        CHECK(2 * 2 == 4);
        CHECK(10 - 5 == 5);
        CHECK(15 / 3 == 5);
    }
    
    TEST_CASE("String operations") {
        std::string hello = "Hello";
        std::string world = "World";
        
        CHECK(hello + " " + world == "Hello World");
        CHECK(hello.size() == 5);
        CHECK(world.find('o') == 1);
    }
    
    TEST_CASE("Floating point comparison") {
        double a = 1.0 / 3.0;
        double b = 0.333333;
        
        CHECK(a == doctest::Approx(0.333333).epsilon(0.0001));
        CHECK(1.0 + 1e-10 == doctest::Approx(1.0));
    }
    
    TEST_CASE("Boolean operations") {
        CHECK(true == true);
        CHECK(false == false);
        CHECK(true != false);
        
        bool value = true;
        CHECK(value == true);
    }
    
    TEST_CASE("Test exceptions") {
        CHECK_THROWS_AS(throw std::runtime_error("error"), std::runtime_error);
        CHECK_NOTHROW(int x = 5 * 5);
    }
}

// Тест для проверки Qt6 доступности
#ifdef QT_CORE_LIB
TEST_SUITE("Qt6 Integration") {
    TEST_CASE("Qt compilation test") {
        // Просто проверяем, что компилируется с Qt
        CHECK(true);
    }
}
#endif

// Тест для проверки структуры проекта
TEST_SUITE("Project Structure") {
    TEST_CASE("Build configuration") {
        #ifdef DEBUG
            INFO("Сборка Debug");
        #else
            INFO("Сборка Release");
        #endif
        
        CHECK(true); // Всегда true, просто проверяем компиляцию
    }
}
