#pragma once

#include <string>

class SubjectMapper {
public:
    SubjectMapper();
    std::string getFullName(const std::string& shortName) const;
};