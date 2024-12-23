#ifndef PUBLIC_ORDER_LIST_H
#define PUBLIC_ORDER_LIST_H

#include <QWidget>
#include <BasePage.h>
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

private:
    Ui::public_order_list *ui;
};

#endif // PUBLIC_ORDER_LIST_H
