// ==============================
// ФАЙЛ: tests/unit/test_classdata.cpp
// ==============================
//#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "../src/core/ClassData.hpp"
#include "../src/core/Student.hpp"
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

TEST_SUITE("Phase 1: Basic shared_ptr structure") {
    TEST_CASE("ClassData can be created with default constructor") {
        ClassData classData;
        CHECK(classData.students.empty());
    }

    TEST_CASE("Add student by shared_ptr") {
        ClassData classData;
        auto student = std::make_shared<Student>("10А", "Иванов");
        classData.addStudent(student);
        
        CHECK(classData.students.size() == 1);
        CHECK(classData.students[0] == student);
    }
}