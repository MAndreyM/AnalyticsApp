#include "DataModels.h"
#include <algorithm>
#include <cctype>
#include <cmath>

// Реализация методов Student
void Student::validateData() const {
    if (className_.empty()) {
        throw DataValidationException("Class name cannot be empty");
    }
    
    if (fullName_.empty()) {
        throw DataValidationException("Full name cannot be empty");
    }
    
    for (const auto& [subject, score] : subjectScores_) {
        if (score < 0.0 || score > 5.0) {
            throw DataValidationException("Subject score must be between 0.0 and 5.0");
        }
        
        if (subject.empty()) {
            throw DataValidationException("Subject name cannot be empty");
        }
    }
}

Student::Student(const std::string& className, const std::string& fullName) 
    : className_(className), fullName_(fullName) {
    setFullName(fullName);
    validateData();
}

void Student::setClassName(const std::string& className) {
    if (className.empty()) {
        throw DataValidationException("Class name cannot be empty");
    }
    className_ = className;
}

void Student::setFullName(const std::string& fullName) {
    if (fullName.empty()) {
        throw DataValidationException("Full name cannot be empty");
    }
    
    fullName_ = fullName;
    auto nameParts = StringUtils::split(fullName, ' ');
    
    if (nameParts.size() >= 1) lastName_ = nameParts[0];
    if (nameParts.size() >= 2) firstName_ = nameParts[1];
    if (nameParts.size() >= 3) middleName_ = nameParts[2];
}

void Student::addSubjectScore(const std::string& subject, double score) {
    if (subject.empty()) {
        throw DataValidationException("Subject name cannot be empty");
    }
    
    if (score < 0.0 || score > 5.0) {
        throw DataValidationException("Score must be between 0.0 and 5.0");
    }
    
    subjectScores_[subject] = score;
}

void Student::setAverageScore(double score) {
    if (score < 0.0) {
        throw DataValidationException("Average score cannot be negative");
    }
    averageScore_ = score;
}

void Student::setRating(int rating) {
    if (rating < 0) {
        throw DataValidationException("Rating cannot be negative");
    }
    rating_ = rating;
}

bool Student::isValid() const {
    try {
        validateData();
        return true;
    } catch (const DataValidationException&) {
        return false;
    }
}

bool Student::hasSubject(const std::string& subject) const {
    return subjectScores_.find(subject) != subjectScores_.end();
}

double Student::getSubjectScore(const std::string& subject) const {
    auto it = subjectScores_.find(subject);
    if (it == subjectScores_.end()) {
        throw DataValidationException("Subject not found: " + subject);
    }
    return it->second;
}

int Student::getSubjectGrade(const std::string& subject) const {
    auto it = subjectGrades_.find(subject);
    if (it == subjectGrades_.end()) {
        throw DataValidationException("Subject grade not found: " + subject);
    }
    return it->second;
}

// Реализация AnalysisResult
void AnalysisResult::addStudentWithSingleThree(const std::string& subject, const Student& student) {
    studentsWithSingleThree_.emplace_back(subject, student);
}

void AnalysisResult::addStudentWithZeroScore(const std::string& subject, const Student& student) {
    studentsWithZeroScore_.emplace_back(subject, student);
}

void AnalysisResult::clear() {
    studentsWithSingleThree_.clear();
    studentsWithZeroScore_.clear();
}

// Реализация StringUtils
std::string StringUtils::trim(const std::string& str) {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        start++;
    }
    
    auto end = str.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    
    return std::string(start, end + 1);
}

std::vector<std::string> StringUtils::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != std::string::npos) {
        tokens.push_back(trim(str.substr(start, end - start)));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    
    tokens.push_back(trim(str.substr(start)));
    return tokens;
}

bool StringUtils::endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

std::string StringUtils::toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

bool StringUtils::isValidName(const std::string& name) {
    return !name.empty() && std::all_of(name.begin(), name.end(), [](char c) {
        return std::isalpha(c) || std::isspace(c);
    });
}