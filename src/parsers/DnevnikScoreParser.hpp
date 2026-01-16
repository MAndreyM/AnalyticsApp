#pragma once
#include <string>

class DnevnikScoreParser {
public:
    static double parseScore(const std::string& scoreStr);
    static std::string normalizeString(const std::string& scoreStr);

};
