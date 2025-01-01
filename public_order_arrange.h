#ifndef PUBLIC_ORDER_ARRANGE_H
#define PUBLIC_ORDER_ARRANGE_H

#include <QWidget>
#include <BasePage.h>
#include <QSqlQuery>
namespace Ui {
class order_arrange;
}

class order_arrange : public BasePage
{
    Q_OBJECT

public:
    explicit order_arrange(BasePage *parent = nullptr);
    ~order_arrange();
protected:
    void closeEvent(QCloseEvent *event) override;  // 重載 closeEvent
private slots:
    void save();
    void change_driver();
private:
    Ui::order_arrange *ui;
    // QSqlDatabase db;  // 資料庫連接
};

#endif // PUBLIC_ORDER_ARRANGE_H
