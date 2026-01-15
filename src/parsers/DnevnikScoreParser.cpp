// src/parsers/DnevnikScoreParser.cpp
#include "DnevnikScoreParser.hpp"

#include <string>
#include <cstdlib>
#include <stdexcept>
#include <regex>
#include <sstream>

double DnevnikScoreParser::parseScore(const std::string& scoreStr) {
    std::string normalized = normalizeString(scoreStr);

    if (normalized.empty()) {
        return 0.0;
    }

    // Проверяем, что строка состоит только из цифр и, возможно, знака минус в начале
    std::regex integerRegex("^-?\\d+$");
    if (!std::regex_match(normalized, integerRegex)) {
        return 0.0;
    }

    try {
        int intValue = std::stoi(normalized);
        return static_cast<double>(intValue) / 1000.0;
    } catch (const std::exception&) {
        return 0.0;
    }
}

std::string DnevnikScoreParser::normalizeString(const std::string& scoreStr) {
    std::string result;
    std::copy_if(scoreStr.begin(), scoreStr.end(),
                 std::back_inserter(result),
                 [](char c) { return !std::isspace(c); });
    return result;
}