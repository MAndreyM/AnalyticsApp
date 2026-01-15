#include "doctest.h"
#include "../../src/parsers/DnevnikScoreParser.hpp"

TEST_CASE("DnevnikScoreParser - базовая компиляция") {
    SUBCASE("класс компилируется") {
        (void)DnevnikScoreParser::parseScore("");
        CHECK(true); // Если скомпилировалось - уже хорошо
    }
}

TEST_CASE("DnevnikScoreParser - нормальные значения") {
    SUBCASE("0 → 0.0") {
        CHECK(DnevnikScoreParser::parseScore("0") == doctest::Approx(0.0));
    }

    SUBCASE("1000 → 1.0") {
        CHECK(DnevnikScoreParser::parseScore("1000") == doctest::Approx(1.0));
    }

    SUBCASE("3690 → 3.69") {
        CHECK(DnevnikScoreParser::parseScore("3690") == doctest::Approx(3.69));
    }

    SUBCASE("5000 → 5.0") {
        CHECK(DnevnikScoreParser::parseScore("5000") == doctest::Approx(5.0));
    }
}

TEST_CASE("DnevnikScoreParser - граничные случаи") {
    SUBCASE("пустая строка → 0.0") {
        CHECK(DnevnikScoreParser::parseScore("") == doctest::Approx(0.0));
    }

    SUBCASE("некорректная строка → 0.0") {
        CHECK(DnevnikScoreParser::parseScore("abc") == doctest::Approx(0.0));
        CHECK(DnevnikScoreParser::parseScore("12.34") == doctest::Approx(0.0));
        CHECK(DnevnikScoreParser::parseScore("1000abc") == doctest::Approx(0.0));
    }

    SUBCASE("отрицательные значения") {
        CHECK(DnevnikScoreParser::parseScore("-1000") == doctest::Approx(-1.0));
        CHECK(DnevnikScoreParser::parseScore("-5000") == doctest::Approx(-5.0));
    }
}