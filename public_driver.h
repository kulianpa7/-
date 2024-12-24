#ifndef PUBLIC_DRIVER_H
#define PUBLIC_DRIVER_H

#include <QWidget>
#include "BasePage.h"
#include <QSqlQuery>

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
    QSqlDatabase db;  // 資料庫連接
private slots:
    void loadDataFromDatabase();
    void onCellChanged(int row);
    void deleteRow(int id);
    void saveDataToDatabase(int row, int id);
    void addrow();
};

#endif // PUBLIC_DRIVER_H
