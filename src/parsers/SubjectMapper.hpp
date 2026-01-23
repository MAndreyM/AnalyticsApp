#pragma once

#include <unordered_map>
#include <string>

class SubjectMapper {
public:
    SubjectMapper();
    std::string getFullName(const std::string& shortName) const;
private:
    std::unordered_map<std::string, std::string> subjectMap;
    void initializeMap();
};