#include "doctest.h"
#include "../../src/parsers/DnevnikScoreParser.hpp"

TEST_CASE("DnevnikScoreParser - базовая компиляция") {
    SUBCASE("класс компилируется") {
        (void)DnevnikScoreParser::parseScore("");
        CHECK(true); // Если скомпилировалось - уже хорошо
    }
}
