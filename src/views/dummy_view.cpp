// Заглушка для AnalyticsViews
#include <QWidget>

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr) : QWidget(parent) {}
};
