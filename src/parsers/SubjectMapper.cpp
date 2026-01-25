#include "SubjectMapper.hpp"

#include <unordered_map>
#include <string>

void SubjectMapper::initializeMap() {
    subjectMap["Алгеб"] = "Алгебра";
    subjectMap["Матем"] = "Математика";
    subjectMap["Русск"] = "Русский язык";
}

SubjectMapper::SubjectMapper() {
    initializeMap();
}

std::string SubjectMapper::getFullName(const std::string& shortName) const {
    if (shortName.empty()) {
        return "";
    }

    auto it = subjectMap.find(shortName);
    if (it != subjectMap.end()) {
        return it->second;
    }

    return shortName;
}

bool SubjectMapper::contains(const std::string& shortName) const {
    if (shortName.empty()) {
        return false;
    }
    return subjectMap.find(shortName) != subjectMap.end();
}