// src/parsers/DnevnikScoreParser.cpp
#include "DnevnikScoreParser.hpp"

#include <string>
#include <cstdlib>
#include <stdexcept>
#include <regex>
#include <sstream>

double DnevnikScoreParser::parseScore(const std::string& scoreStr) {
    if (scoreStr.empty()) {
        return 0.0;
    }

    // Проверяем, что строка состоит только из цифр и, возможно, знака минус в начале
    std::regex integerRegex("^-?\\d+$");
    if (!std::regex_match(scoreStr, integerRegex)) {
        return 0.0;
    }

    try {
        int intValue = std::stoi(scoreStr);
        return static_cast<double>(intValue) / 1000.0;

    } catch (const std::exception&) {
        return 0.0;
    }
}