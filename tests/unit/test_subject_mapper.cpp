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

    TEST_CASE("Маппинг нескольких предметов") {
        SubjectMapper mapper;

        CHECK(mapper.getFullName("Алгеб") == "Алгебра");
        CHECK(mapper.getFullName("Матем") == "Математика");
        CHECK(mapper.getFullName("Русск") == "Русский язык");
    }

    TEST_CASE("Неизвестное сокращение возвращается как есть") {
        SubjectMapper mapper;
        CHECK(mapper.getFullName("Неизвестный") == "Неизвестный");
    }

    TEST_CASE("Метод contains проверяет наличие") {
        SubjectMapper mapper;

        CHECK(mapper.contains("Алгеб") == true);
        CHECK(mapper.contains("Матем") == true);
        CHECK(mapper.contains("Неизвестный") == false);
        CHECK(mapper.contains("") == false);
    }

    TEST_CASE("Обрезка пробелов в начале и конце") {
        SubjectMapper mapper;

        CHECK(mapper.getFullName("  Алгеб  ") == "Алгебра");
        CHECK(mapper.getFullName("\tРусск\n") == "Русский язык");
        CHECK(mapper.contains("  Матем  ") == true);
    }

    TEST_CASE("Размер словаря корректный") {
        SubjectMapper mapper;
        CHECK(mapper.size() == 3); // Три предмета добавлено
    }

    TEST_CASE("Добавление нового маппинга") {
        SubjectMapper mapper;
        size_t originalSize = mapper.size();

        mapper.addMapping("НовП", "Новый предмет");

        CHECK(mapper.size() == originalSize + 1);
        CHECK(mapper.contains("НовП") == true);
        CHECK(mapper.getFullName("НовП") == "Новый предмет");
    }

    TEST_CASE("Пустые строки не добавляются") {
        SubjectMapper mapper;
        size_t originalSize = mapper.size();

        mapper.addMapping("", "Пустое сокращение");
        mapper.addMapping("Сокр", "");

        CHECK(mapper.size() == originalSize); // Размер не изменился
    }
}