#pragma once

/**
 * @struct SchoolSummaryView
 * @brief Структура для представления сводной статистики по школе
 * 
 * Используется для отображения агрегированных данных в UI.
 * Содержит количество учеников по каждой категории для всей школы.
 */
struct SchoolSummaryView {
    int totalStudents;               ///< Общее количество учеников в школе
    int studentsWithZero;            ///< Ученики без оценок (имеют 0)
    int studentsWithTwos;            ///< Ученики с двойками
    int studentsWithSingleThree;     ///< Ученики с одной тройкой
    int studentsWithSingleFour;      ///< Ученики с одной четверкой
    int studentsWithFoursAndFives;   ///< Ученики с оценками 4 и 5
    int excellentStudents;           ///< Отличники (все оценки 5)

    /**
     * @brief Оператор сравнения для тестирования
     * @param other Другой объект SchoolSummaryView
     * @return true если все поля равны, иначе false
     */
    bool operator==(const SchoolSummaryView& other) const {
        return totalStudents == other.totalStudents &&
               studentsWithZero == other.studentsWithZero &&
               studentsWithTwos == other.studentsWithTwos &&
               studentsWithSingleThree == other.studentsWithSingleThree &&
               studentsWithSingleFour == other.studentsWithSingleFour &&
               studentsWithFoursAndFives == other.studentsWithFoursAndFives &&
               excellentStudents == other.excellentStudents;
    }

    /**
     * @brief Оператор неравенства
     * @param other Другой объект SchoolSummaryView
     * @return true если объекты не равны, иначе false
     */
    bool operator!=(const SchoolSummaryView& other) const {
        return !(*this == other);
    }
};