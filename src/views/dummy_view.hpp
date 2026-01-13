#pragma once
#include <QWidget>

// Простой Qt виджет для теста
class DummyView : public QWidget {
    Q_OBJECT
public:
    explicit DummyView(QWidget* parent = nullptr);

    // Простой метод без сложных сигналов/слотов
    void testMethod() { /* тест */
    }
};
