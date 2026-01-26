// ==============================
// ФАЙЛ: test_subject_mapper.cpp
// ==============================
#include "doctest.h"
#include "../../src/parsers/SubjectMapper.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

TEST_SUITE("SubjectMapper") {
    TEST_CASE("Конструктор и базовая функциональность") {
        SubjectMapper mapper;

        SUBCASE("Словарь не пустой после инициализации") {
            CHECK(mapper.size() > 0);
            std::cout << "Количество записей в словаре: " << mapper.size() << std::endl;
        }

        SUBCASE("Содержит основные предметы") {
            CHECK(mapper.contains("Алгеб") == true);
            CHECK(mapper.contains("Матем") == true);
            CHECK(mapper.contains("Русск") == true);
            CHECK(mapper.contains("Физик") == true);
            CHECK(mapper.contains("Биоло") == true);
        }
    }

    TEST_CASE("Маппинг сокращенных названий в полные") {
        SubjectMapper mapper;

        SUBCASE("Основные школьные предметы") {
            CHECK(mapper.getFullName("Алгеб") == "Алгебра");
            CHECK(mapper.getFullName("Матем") == "Математика");
            CHECK(mapper.getFullName("Русск") == "Русский язык");
            CHECK(mapper.getFullName("Англи") == "Английский язык");
            CHECK(mapper.getFullName("Биоло") == "Биология");
            CHECK(mapper.getFullName("Физик") == "Физика");
            CHECK(mapper.getFullName("Химия") == "Химия");
            CHECK(mapper.getFullName("Геогр") == "География");
            CHECK(mapper.getFullName("Истор") == "История");
            CHECK(mapper.getFullName("Общес") == "Обществознание");
        }

        SUBCASE("Математические дисциплины") {
            CHECK(mapper.getFullName("Геоме") == "Геометрия");
            CHECK(mapper.getFullName("Вероя") == "Вероятность и статистика");
        }

        SUBCASE("Филологические дисциплины") {
            CHECK(mapper.getFullName("Литер") == "Литература");
            CHECK(mapper.getFullName("Немец") == "Немецкий язык");
            CHECK(mapper.getFullName("Франц") == "Французский язык");
            CHECK(mapper.getFullName("Испан") == "Испанский язык");
            CHECK(mapper.getFullName("Родно") == "Родной язык");
        }

        SUBCASE("Технические дисциплины") {
            CHECK(mapper.getFullName("Инфор") == "Информатика");
            CHECK(mapper.getFullName("Техно") == "Технология");
        }

        SUBCASE("Физкультура и искусство") {
            CHECK(mapper.getFullName("Физич") == "Физическая культура");
            CHECK(mapper.getFullName("Музык") == "Музыка");
            CHECK(mapper.getFullName("Изобр") == "Изобразительное искусство");
            CHECK(mapper.getFullName("Искус") == "Искусство");
        }

        SUBCASE("Прочие дисциплины") {
            CHECK(mapper.getFullName("Основ") == "Основы безопасности жизнедеятельности (ОБЖ)");
            CHECK(mapper.getFullName("Проек") == "Проектная деятельность");
            CHECK(mapper.getFullName("Индив") == "Индивидуальный проект");
            CHECK(mapper.getFullName("Труд") == "Труд");
            CHECK(mapper.getFullName("Окруж") == "Окружающий мир");
        }

        SUBCASE("Сокращения с точками") {
            CHECK(mapper.getFullName("Алгеб.") == "Алгебра");
            CHECK(mapper.getFullName("Матем.") == "Математика");
            CHECK(mapper.getFullName("Физик.") == "Физика");
        }
    }

    TEST_CASE("Обработка неизвестных сокращений") {
        SubjectMapper mapper;

        SUBCASE("Неизвестное сокращение возвращается как есть") {
            CHECK(mapper.getFullName("НеизвестныйПредмет") == "НеизвестныйПредмет");
            CHECK(mapper.getFullName("Test") == "Test");
            CHECK(mapper.getFullName("123") == "123");
        }

        SUBCASE("Пустая строка") {
            CHECK(mapper.getFullName("") == "");
            CHECK(mapper.contains("") == false);
        }

        SUBCASE("Строка с пробелами") {
            CHECK(mapper.getFullName("  Алгеб  ") == "Алгебра");
            CHECK(mapper.getFullName("\tРусск\n") == "Русский язык");
        }
    }

    TEST_CASE("Метод contains") {
        SubjectMapper mapper;

        SUBCASE("Известные сокращения") {
            CHECK(mapper.contains("Алгеб") == true);
            CHECK(mapper.contains("Русск") == true);
            CHECK(mapper.contains("Физик") == true);
        }

        SUBCASE("Неизвестные сокращения") {
            CHECK(mapper.contains("Unknown") == false);
            CHECK(mapper.contains("") == false);
            CHECK(mapper.contains("   ") == false);
        }

        SUBCASE("Строки с пробелами") {
            CHECK(mapper.contains("  Алгеб  ") == true);  // Проверяет trimmed версию
            CHECK(mapper.contains("Алгеб ") == true);
            CHECK(mapper.contains(" Русск") == true);
        }
    }

    TEST_CASE("Добавление новых соответствий") {
        SubjectMapper mapper;
        size_t originalSize = mapper.size();

        SUBCASE("Добавление нового маппинга") {
            mapper.addMapping("НовП", "Новый предмет");
            CHECK(mapper.size() == originalSize + 1);
            CHECK(mapper.contains("НовП") == true);
            CHECK(mapper.getFullName("НовП") == "Новый предмет");
        }

        SUBCASE("Добавление пустых строк") {
            mapper.addMapping("", "Пустое сокращение");
            mapper.addMapping("Сокр", "");
            CHECK(mapper.size() == originalSize);  // Не должно добавиться
        }

        SUBCASE("Обновление существующего маппинга") {
            mapper.addMapping("Алгеб", "Обновленная Алгебра");
            CHECK(mapper.getFullName("Алгеб") == "Обновленная Алгебра");
        }
    }

    TEST_CASE("Метод getAllShortNames") {
        SubjectMapper mapper;

        SUBCASE("Список не пустой") {
            auto shortNames = mapper.getAllShortNames();
            CHECK(shortNames.empty() == false);

            // Проверяем, что список отсортирован
            bool isSorted = std::is_sorted(shortNames.begin(), shortNames.end());
            CHECK(isSorted == true);

            // Проверяем наличие ключевых предметов
            bool hasAlgebra = std::find(shortNames.begin(), shortNames.end(), "Алгеб") != shortNames.end();
            bool hasMath = std::find(shortNames.begin(), shortNames.end(), "Матем") != shortNames.end();
            bool hasRussian = std::find(shortNames.begin(), shortNames.end(), "Русск") != shortNames.end();

            CHECK(hasAlgebra == true);
            CHECK(hasMath == true);
            CHECK(hasRussian == true);
        }
    }

    TEST_CASE("Метод clear") {
        SubjectMapper mapper;

        SUBCASE("Очистка словаря") {
            size_t originalSize = mapper.size();
            CHECK(originalSize > 0);

            mapper.clear();
            CHECK(mapper.size() == 0);
            CHECK(mapper.getAllShortNames().empty() == true);

            // Проверяем, что маппинг больше не работает
            CHECK(mapper.getFullName("Алгеб") == "Алгеб");
            CHECK(mapper.contains("Русск") == false);
        }

        SUBCASE("Добавление после очистки") {
            mapper.clear();
            mapper.addMapping("Тест", "Тестовый предмет");

            CHECK(mapper.size() == 1);
            CHECK(mapper.getFullName("Тест") == "Тестовый предмет");
        }
    }

    TEST_CASE("Интеграционные тесты - реальные случаи из Дневник.ру") {
        SubjectMapper mapper;

        SUBCASE("Типичные сокращения из файлов Дневник.ру") {
            // Проверяем все основные предметы, которые могут встретиться
            std::vector<std::pair<std::string, std::string>> testCases = {
                {"Алгеб", "Алгебра"},
                {"Геоме", "Геометрия"},
                {"Матем", "Математика"},
                {"Русск", "Русский язык"},
                {"Англи", "Английский язык"},
                {"Биоло", "Биология"},
                {"Физик", "Физика"},
                {"Химия", "Химия"},
                {"Геогр", "География"},
                {"Истор", "История"},
                {"Общес", "Обществознание"},
                {"Инфор", "Информатика"},
                {"Физич", "Физическая культура"},
                {"Музык", "Музыка"},
                {"Основ", "Основы безопасности жизнедеятельности (ОБЖ)"},
                {"Проек", "Проектная деятельность"},
                {"Окруж", "Окружающий мир"},
                {"Родно", "Родной язык"},
                {"Техно", "Технология"},
                {"Изобр", "Изобразительное искусство"}
            };

            for (const auto& testCase : testCases) {
                CAPTURE(testCase.first);
                CHECK(mapper.getFullName(testCase.first) == testCase.second);
            }
        }

        SUBCASE("Проверка минимального требуемого количества предметов") {
            // Требуется 20+ предметов в словаре
            CHECK(mapper.size() >= 20);

            auto shortNames = mapper.getAllShortNames();
            std::cout << "Всего предметов в словаре: " << shortNames.size() << std::endl;
            std::cout << "Примеры предметов:" << std::endl;

            for (size_t i = 0; i < std::min(size_t(10), shortNames.size()); ++i) {
                std::cout << "  " << shortNames[i] << " -> " 
                          << mapper.getFullName(shortNames[i]) << std::endl;
            }
        }
    }

    TEST_CASE("Тесты на граничные случаи") {
        SubjectMapper mapper;

        SUBCASE("Очень длинные строки") {
            std::string longString(1000, 'A');
            CHECK(mapper.getFullName(longString) == longString);
            CHECK(mapper.contains(longString) == false);
        }

        SUBCASE("Специальные символы") {
            CHECK(mapper.getFullName("Алгеб-Геом") == "Алгеб-Геом");
            CHECK(mapper.getFullName("Матем/Алгеб") == "Матем/Алгеб");
            CHECK(mapper.getFullName("Русск(прод)") == "Русск(прод)");
        }

        SUBCASE("Строки только с пробелами") {
            CHECK(mapper.getFullName("   ") == "   ");
            CHECK(mapper.contains("   ") == false);
        }

        SUBCASE("Unicode символы") {
            CHECK(mapper.getFullName("Матемё") == "Матемё");
            CHECK(mapper.getFullName("Русскй") == "Русскй");
        }
    }

    TEST_CASE("Производительность") {
        SubjectMapper mapper;

        SUBCASE("Множественные вызовы getFullName") {
            const int iterations = 10000;

            for (int i = 0; i < iterations; ++i) {
                auto result = mapper.getFullName("Алгеб");
                DOCTEST_CHECK(result == "Алгебра");
            }
        }

        SUBCASE("Смешанные вызовы известных и неизвестных предметов") {
            std::vector<std::string> testSubjects = {
                "Алгеб", "Русск", "Физик", "Неизвестный", "Матем",
                "Биоло", "Химия", "AnotherUnknown", "Геогр"
            };

            for (const auto& subject : testSubjects) {
                auto result = mapper.getFullName(subject);
                // Проверяем только что не падает
                DOCTEST_CHECK(true);
            }
        }
    }
}