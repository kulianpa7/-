#ifndef PUBLIC_USER_H
#define PUBLIC_USER_H
#include "BasePage.h"
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
namespace Ui {
class public_user;
}

namespace Ui {
class public_user;
}

class public_user : public BasePage  // 繼承 BasePage
{
    Q_OBJECT

public:
    explicit public_user(BasePage *parent = nullptr);
    ~public_user();

protected:
    void closeEvent(QCloseEvent *event) override;  // 重載 closeEvent

private slots:
    void onCellChanged(int row);
    void deleteRow(int id);

private:
    Ui::public_user *ui;
    // QSqlDatabase db;  // 資料庫連接

    void loadDataFromDatabase();
    void updateUserRole(int userId, int roleId);
    void saveDataToDatabase(int row, int id);
    void addrow();
};

#endif // PUBLIC_USER_H
