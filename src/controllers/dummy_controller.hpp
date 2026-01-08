#pragma once
#include <QObject>

// Минимальный Qt класс для тестирования CMake структуры
class DummyController : public QObject {
    Q_OBJECT
public:
    explicit DummyController(QObject* parent = nullptr) : QObject(parent) {}
    
    // Простой метод без сложных сигналов/слотов
    void testMethod() { /* тестовая реализация */ }
};
