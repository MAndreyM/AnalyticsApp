// src/parsers/DnevnikScoreParser.cpp
#include "DnevnikScoreParser.hpp"

#include <string>
#include <cstdlib>

double DnevnikScoreParser::parseScore(const std::string& scoreStr) {
    if (scoreStr.empty()) {
        return 0.0;
    }
    // Простейшая реализация - парсинг числа
    try {
        return std::stod(scoreStr);
    } catch (...) {
        return 0.0; // или NAN, если нужно
    }
}