/**
 * @file DnevnikScoreParser.cpp
 * @brief Реализация парсера для преобразования баллов из формата "Дневник.ру"
 * 
 * Этот файл содержит реализацию методов класса DnevnikScoreParser,
 * который преобразует строковые представления баллов из формата "Дневник.ру"
 * в десятичные числа. Формат "Дневник.ру" представляет баллы как целые числа
 * от 0 до 5000, где 5000 соответствует оценке 5.0.
 * 
 * @see DnevnikScoreParser
 */

#include "DnevnikScoreParser.hpp"

#include <string>
#include <cstdlib>
#include <stdexcept>
#include <regex>
#include <sstream>
#include <algorithm>
#include <cctype>

/**
 * @brief Преобразует строку с баллом в десятичное число
 * 
 * @param scoreStr Строка с баллом в формате "Дневник.ру"
 * @return double Десятичное значение от 0.0 до 5.0
 * 
 * @details
 * Метод выполняет следующие шаги:
 * 1. Нормализация строки (удаление пробелов)
 * 2. Проверка формата строки (только цифры, возможно со знаком минус)
 * 3. Преобразование в целое число
 * 4. Ограничение значения диапазоном 0-5000
 * 5. Деление на 1000.0 для получения десятичного значения
 * 
 * @exception std::invalid_argument Если строка содержит нечисловые символы
 * @exception std::out_of_range Если число выходит за пределы int
 * 
 * @note
 * - При некорректных данных возвращается 0.0
 * - Отрицательные значения преобразуются в 0.0
 * - Значения больше 5000 ограничиваются до 5000
 * - Исключения перехватываются и возвращается значение по умолчанию
 * 
 * @warning
 * Метод использует статические проверки через регулярные выражения,
 * что может влиять на производительность при обработке больших объемов данных.
 * 
 * @test
 * Примеры корректных преобразований:
 * - "3690" → 3.69
 * - "5000" → 5.0
 * - "0" → 0.0
 * - "2500" → 2.5
 * 
 * Примеры обработки некорректных данных:
 * - "" → 0.0
 * - "abc" → 0.0
 * - "12a34" → 0.0
 * - "12345" → 5.0 (ограничение до 5000)
 * - "-100" → 0.0 (отрицательные значения)
 */
double DnevnikScoreParser::parseScore(const std::string& scoreStr) {
    // Нормализуем строку (удаляем пробелы)
    std::string normalized = normalizeString(scoreStr);

    // Проверяем, не пуста ли строка после нормализации
    if (normalized.empty()) {
        return 0.0;
    }

    // Проверяем, что строка состоит только из цифр и, возможно, знака минус в начале
    std::regex integerRegex("^-?\\d+$");
    if (!std::regex_match(normalized, integerRegex)) {
        return 0.0;
    }

    try {
        // Используем long long для предотвращения переполнения
        long long longValue = std::stoll(normalized);

        // Ограничиваем значение допустимым диапазоном 0-5000
        if (longValue < 0) longValue = 0;
        if (longValue > 5000) longValue = 5000;

        // Преобразуем в десятичный формат: делим на 1000
        return static_cast<double>(longValue) / 1000.0;
    } catch (const std::exception&) {
        // В случае ошибки преобразования возвращаем значение по умолчанию
        return 0.0;
    }
}

/**
 * @brief Нормализует строку, удаляя пробельные символы
 * 
 * @param scoreStr Исходная строка для нормализации
 * @return std::string Нормализованная строка без пробелов
 * 
 * @details
 * Метод удаляет все пробельные символы из строки, включая:
 * - Пробелы (' ')
 * - Табуляции ('\t')
 * - Переводы строк ('\n', '\r')
 * 
 * @note
 * - Использует алгоритм std::copy_if для эффективного копирования
 * - Проверяет символы с помощью std::isspace
 * - Сохраняет порядок не-пробельных символов
 * 
 * @example
 * Примеры нормализации:
 * - "3 690" → "3690"
 * - "5 000" → "5000"
 * - "  2500  " → "2500"
 * - "1 234 567" → "1234567"
 */
std::string DnevnikScoreParser::normalizeString(const std::string& scoreStr) {
    std::string result;
    
    // Используем std::copy_if для копирования только не-пробельных символов
    std::copy_if(scoreStr.begin(), scoreStr.end(),
                 std::back_inserter(result),
                 [](char c) { 
                     return !std::isspace(static_cast<unsigned char>(c)); 
                 });
    
    return result;
}

/**
 * @example Пример использования класса DnevnikScoreParser
 * @code
 * // Пример 1: Нормальный балл
 * double score1 = DnevnikScoreParser::parseScore("3690");
 * // score1 = 3.69
 * 
 * // Пример 2: Балл с пробелами
 * double score2 = DnevnikScoreParser::parseScore("3 690");
 * // score2 = 3.69
 * 
 * // Пример 3: Максимальный балл
 * double score3 = DnevnikScoreParser::parseScore("5000");
 * // score3 = 5.0
 * 
 * // Пример 4: Нулевой балл
 * double score4 = DnevnikScoreParser::parseScore("0");
 * // score4 = 0.0
 * 
 * // Пример 5: Некорректные данные
 * double score5 = DnevnikScoreParser::parseScore("abc");
 * // score5 = 0.0
 * 
 * double score6 = DnevnikScoreParser::parseScore("");
 * // score6 = 0.0
 * @endcode
 */

/**
 * @test Тестовые случаи для DnevnikScoreParser
 * @code
 * // Test 1: Корректные значения
 * assert(DnevnikScoreParser::parseScore("3690") == 3.69);
 * assert(DnevnikScoreParser::parseScore("5000") == 5.0);
 * assert(DnevnikScoreParser::parseScore("0") == 0.0);
 * 
 * // Test 2: Значения с пробелами
 * assert(DnevnikScoreParser::parseScore("3 690") == 3.69);
 * assert(DnevnikScoreParser::parseScore("5 000") == 5.0);
 * 
 * // Test 3: Граничные значения
 * assert(DnevnikScoreParser::parseScore("1") == 0.001);
 * assert(DnevnikScoreParser::parseScore("4999") == 4.999);
 * 
 * // Test 4: Некорректные значения
 * assert(DnevnikScoreParser::parseScore("abc") == 0.0);
 * assert(DnevnikScoreParser::parseScore("12a34") == 0.0);
 * assert(DnevnikScoreParser::parseScore("") == 0.0);
 * assert(DnevnikScoreParser::parseScore("   ") == 0.0);
 * 
 * // Test 5: Отрицательные значения (преобразуются в 0)
 * assert(DnevnikScoreParser::parseScore("-100") == 0.0);
 * 
 * // Test 6: Значения вне диапазона (ограничиваются)
 * assert(DnevnikScoreParser::parseScore("6000") == 5.0); // Ограничено до 5000
 * assert(DnevnikScoreParser::parseScore("10000") == 5.0); // Ограничено до 5000
 * @endcode
 */