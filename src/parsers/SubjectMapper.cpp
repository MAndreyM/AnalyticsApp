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

    // Обрезаем пробелы
    std::string trimmed = shortName;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r\f\v"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r\f\v") + 1);

    auto it = subjectMap.find(trimmed);
    if (it != subjectMap.end()) {
        return it->second;
    }

    return shortName; // Возвращаем оригинал, не trimmed
}

bool SubjectMapper::contains(const std::string& shortName) const {
    if (shortName.empty()) {
        return false;
    }

    // Обрезаем пробелы для поиска
    std::string trimmed = shortName;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r\f\v"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r\f\v") + 1);

    return !trimmed.empty() && subjectMap.find(trimmed) != subjectMap.end();
}
