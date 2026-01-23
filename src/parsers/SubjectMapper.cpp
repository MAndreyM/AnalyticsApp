#include "SubjectMapper.hpp"

#include <string>

SubjectMapper::SubjectMapper() {
}

std::string SubjectMapper::getFullName(const std::string& shortName) const {
    if (shortName.empty()) {
        return "";
    }
    return shortName;
}