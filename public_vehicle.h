#ifndef PUBLIC_VEHICLE_H
#define PUBLIC_VEHICLE_H

#include <QWidget>
#include "BasePage.h"
namespace Ui {
class public_velicle;
}

class public_velicle : public BasePage
{
    Q_OBJECT

public:
    explicit public_velicle(BasePage *parent = nullptr);
    ~public_velicle();
protected:
    void closeEvent(QCloseEvent *event) override;  // 重載 closeEvent
private:

    Ui::public_velicle *ui;
};

#endif // PUBLIC_VEHICLE_H
