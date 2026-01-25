#pragma once

#include <unordered_map>
#include <string>

class SubjectMapper {
public:
    SubjectMapper();
    std::string getFullName(const std::string& shortName) const;
    bool contains(const std::string& shortName) const;
    size_t size() const;
    void addMapping(const std::string& shortName, const std::string& fullName);

private:
    std::unordered_map<std::string, std::string> subjectMap;
    void initializeMap();
};