#ifndef PUBLIC_ROLE_H
#define PUBLIC_ROLE_H

#include <QWidget>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidget>
#include <BasePage.h>

namespace Ui {
class public_role;
}

class public_role : public BasePage
{
    Q_OBJECT

public:
    explicit public_role(BasePage *parent = nullptr);
    ~public_role();
    // 在 public_role.h 中
protected:
    void closeEvent(QCloseEvent *event) override;  // 重載 closeEvent
private slots:
    void onCellChanged(int row);
    void deleteRow(int id);
    void addrow();

private:
    Ui::public_role *ui;

    QSqlDatabase db;  // 資料庫連接
    void loadDataFromDatabase();  // 從資料庫載入資料到表格
    void saveDataToDatabase(int row,int id); // 將特定行儲存回資料庫
};

#endif // PUBLIC_ROLE_H
