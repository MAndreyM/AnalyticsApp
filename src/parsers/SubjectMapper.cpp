#include "SubjectMapper.hpp"

#include <string>

SubjectMapper::SubjectMapper() {
}

std::string SubjectMapper::getFullName(const std::string& shortName) const {
    return shortName;
}