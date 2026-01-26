#include "SubjectMapper.hpp"

#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>

void SubjectMapper::initializeMap() {
    // Основные школьные предметы
    subjectMap = {
        // Математические дисциплины
        {"Алгеб", "Алгебра"},
        {"Геоме", "Геометрия"},
        {"Матем", "Математика"},
        {"Вероя", "Вероятность и статистика"},

        // Филологические дисциплины
        {"Русск", "Русский язык"},
        {"Литер", "Литература"},
        {"Англи", "Английский язык"},
        {"Немец", "Немецкий язык"},
        {"Франц", "Французский язык"},
        {"Испан", "Испанский язык"},
        {"Родно", "Родной язык"},

        // Естественные науки
        {"Биоло", "Биология"},
        {"Физик", "Физика"},
        {"Химия", "Химия"},
        {"Геогр", "География"},
        {"Астро", "Астрономия"},
        {"Эколо", "Экология"},
        {"Окруж", "Окружающий мир"},

        // Гуманитарные дисциплины
        {"Истор", "История"},
        {"Общес", "Обществознание"},
        {"Право", "Право"},
        {"Эконо", "Экономика"},

        // Технические дисциплины
        {"Инфор", "Информатика"},
        {"Техно", "Технология"},
        {"Черче", "Черчение"},
        {"Робот", "Робототехника"},

        // Физкультура и искусство
        {"Физич", "Физическая культура"},
        {"Музык", "Музыка"},
        {"Изобр", "Изобразительное искусство"},
        {"Искус", "Искусство"},
        {"Миров", "Мировая художественная культура (МХК)"},

        // Прочие дисциплины
        {"Основ", "Основы безопасности жизнедеятельности (ОБЖ)"},
        {"Проек", "Проектная деятельность"},
        {"Индив", "Индивидуальный проект"},
        {"Труд", "Труд"},
        {"Речи", "Развитие речи"},
        {"Псих", "Психология"},
        {"Логик", "Логика"},

        // Религиоведение и этика
        {"ОДНКР", "Основы духовно-нравственной культуры народов России"},
        {"ОРКСЭ", "Основы религиозных культур и светской этики"},

        // Вторые иностранные языки
        {"2инз", "Второй иностранный язык"},

        // Специальные курсы
        {"Крае", "Краеведение"},
        {"Консу", "Консультация"},
        {"Элект", "Элективный курс"},

        // Стандартные сокращения для оценок
        {"СБП", "Средний балл по предмету"},
        {"Кач", "% качества знаний"},
        {"СОУ", "СОУ (%) по предмету"}
    };

    // Добавляем также варианты с точками (если они встречаются)
    subjectMap["Алгеб."] = "Алгебра";
    subjectMap["Геоме."] = "Геометрия";
    subjectMap["Матем."] = "Математика";
    subjectMap["Физик."] = "Физика";
    subjectMap["Химия."] = "Химия";
    subjectMap["Биоло."] = "Биология";
    subjectMap["Инфор."] = "Информатика";
    subjectMap["Истори"] = "История";
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

size_t SubjectMapper::size() const {
    return subjectMap.size();
}

void SubjectMapper::addMapping(const std::string& shortName, const std::string& fullName) {
    if (!shortName.empty() && !fullName.empty()) {
        subjectMap[shortName] = fullName;
    }
}

std::vector<std::string> SubjectMapper::getAllShortNames() const {
    std::vector<std::string> result;
    result.reserve(subjectMap.size());

    for (const auto& pair : subjectMap) {
        result.push_back(pair.first);
    }

    std::sort(result.begin(), result.end());
    return result;
}

void SubjectMapper::clear() {
    subjectMap.clear();
}