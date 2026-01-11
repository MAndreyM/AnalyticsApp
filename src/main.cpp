#include <iostream>
#include <QApplication>

int main(int argc, char* argv[]) {
    std::cout << "AnalyticsApp успешно скомпилирован с Qt6!" << std::endl;

    QApplication app(argc, argv);
    std::cout << "Qt Application создана" << std::endl;

    return 0;  // Не запускаем event loop для теста
}
