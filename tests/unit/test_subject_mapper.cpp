#include "doctest.h"
#include "../../src/parsers/SubjectMapper.hpp"

TEST_SUITE("SubjectMapper") {
    TEST_CASE("Конструктор создает объект") {
        SubjectMapper mapper;
        // SUCCEED("Объект создан успешно");
        // Просто создаем объект, если не было исключения - тест пройден
        CHECK(true); // Альтернатива SUCCEED
    }

    TEST_CASE("Пустая строка возвращает пустую строку") {
        SubjectMapper mapper;
        CHECK(mapper.getFullName("") == "");
    }
}