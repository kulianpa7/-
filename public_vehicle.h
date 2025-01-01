#ifndef PUBLIC_VEHICLE_H
#define PUBLIC_VEHICLE_H

#include <QWidget>
#include "BasePage.h"
#include <QSqlQuery>
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
private slots:
    void onCellChanged(int row);
    void deleteRow(int id);

private:
    // QSqlDatabase db;  // 資料庫連接

    void loadDataFromDatabase();
    void updateUserRole(int userId, int roleId);
    void saveDataToDatabase(int row, int id);
    void addrow();
    Ui::public_velicle *ui;
};

#endif // PUBLIC_VEHICLE_H
