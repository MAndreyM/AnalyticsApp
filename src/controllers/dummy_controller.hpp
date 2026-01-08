#pragma once
#include <QObject>

// Простой класс без сложных сигналов/слотов для теста
class DummyController : public QObject {
    Q_OBJECT
public:
    explicit DummyController(QObject* parent = nullptr);
};
