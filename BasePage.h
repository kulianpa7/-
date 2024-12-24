#ifndef BASEPAGE_H
#define BASEPAGE_H
#include <QMainWindow>
class BasePage : public QWidget {
    Q_OBJECT
public:
    explicit BasePage(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual ~BasePage() {}
};

enum ButtonType {
    Role,
    User,
    Driver,
    Vehicle,
    Order_list,
    Driver_Arrange,
    Order_arrange,
    Unknown
};


#endif // BASEPAGE_H
