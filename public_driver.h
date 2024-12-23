#ifndef PUBLIC_DRIVER_H
#define PUBLIC_DRIVER_H

#include <QWidget>
#include "BasePage.h"
namespace Ui {
class public_driver;
}

class public_driver : public BasePage
{
    Q_OBJECT
public:
    explicit public_driver(BasePage *parent = nullptr);
    ~public_driver();
protected:
    void closeEvent(QCloseEvent *event) override;  // 重載 closeEvent
private:
    Ui::public_driver *ui;
};

#endif // PUBLIC_DRIVER_H
