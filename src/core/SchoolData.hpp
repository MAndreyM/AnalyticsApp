#pragma once

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

#include "ClassData.hpp"
#include "SchoolSummaryView.hpp"

/**
 * @class SchoolData
 * @brief Класс для хранения и управления данными всей школы
 * 
 * Содержит данные по всем классам школы и предоставляет методы
 * для получения агрегированной статистики и работы с параллелями.
 */
class SchoolData {
private:
    std::map<std::string, ClassData> classes; ///< Карта классов по названию
    
public:
    /**
     * @brief Получает список доступных параллелей (2-11)
     * @return Вектор номеров параллелей, представленных в данных
     */
    std::vector<int> getAvailableGrades() const;
    
    /**
     * @brief Получает все классы определенной параллели
     * @param grade Номер параллели
     * @return Вектор данных классов указанной параллели
     */
    std::vector<ClassData> getGradeParallel(int grade) const;
    
    /**
     * @brief Получает список классов в указанной параллели
     * @param grade Номер параллели
     * @return Вектор названий классов
     */
    std::vector<std::string> getClassesInGrade(int grade) const;
    
    /**
     * @brief Получает сводную статистику по всей школе
     * @return Структура SchoolSummaryView с агрегированными данными
     */
    SchoolSummaryView getSchoolSummary() const;

    /**
     * @brief Получает доступ к карте классов (только для чтения)
     * @return Константная ссылка на карту классов
     */
    const std::map<std::string, ClassData>& getClasses() const { return classes; }
    
    /**
     * @brief Добавляет или обновляет данные класса
     * @param className Название класса
     * @param classData Данные класса
     */
    void addOrUpdateClass(const std::string& className, const ClassData& classData) {
        classes[className] = classData;
    }
    
    /**
     * @brief Очищает все данные школы
     */
    void clear() {
        classes.clear();
    }
};