#ifndef PUBLIC_ORDER_LIST_H
#define PUBLIC_ORDER_LIST_H

#include <QWidget>
#include <BasePage.h>
#include <QSqlQuery>

namespace Ui {
class public_order_list;
}

class public_order_list : public BasePage
{
    Q_OBJECT

public:
    explicit public_order_list(BasePage *parent = nullptr);
    ~public_order_list();
protected:
    void closeEvent(QCloseEvent *event) override;  // 重載 closeEvent
private slots:
    void onCellChanged(int row);
    void deleteRow(int id);

private:
    Ui::public_order_list *ui;
    // QSqlDatabase db;  // 資料庫連接

    void loadDataFromDatabase();
    void updateUserRole(int userId, int roleId);
    void saveDataToDatabase(int row, int id);
    void addrow();
};

#endif // PUBLIC_ORDER_LIST_H
