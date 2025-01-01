#ifndef PUBLIC_DRIVER_ARRANGE_H
#define PUBLIC_DRIVER_ARRANGE_H

#include <QWidget>
#include <BasePage.h>
#include <QSqlQuery>
namespace Ui {
class public_driver_arrange;
}

class public_driver_arrange : public BasePage
{
    Q_OBJECT

public:
    explicit public_driver_arrange(BasePage *parent = nullptr);
    ~public_driver_arrange();
protected:
    void closeEvent(QCloseEvent *event) override;  // 重載 closeEvent
private:
    Ui::public_driver_arrange *ui;
    // QSqlDatabase db;  // 資料庫連接
private slots:
    void onDateChanged(const QDate &date);
    void combo_driver();
    void combo_car();
    void on_driver_changed();
    void combo_box_car();
    void push_button_checkboxANDcombobox(QVector<QVector<int>>vec,int weekday);
    void save();
    void deleteAllForMonth();
    void clear_check();
};

#endif // PUBLIC_DRIVER_ARRANGE_H
