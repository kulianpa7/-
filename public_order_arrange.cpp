#include "public_order_arrange.h"
#include "ui_public_order_arrange.h"
#include <BasePage.h>
order_arrange::order_arrange(BasePage *parent)
    : BasePage(parent)
    , ui(new Ui::order_arrange)
{
    ui->setupUi(this);
}

order_arrange::~order_arrange()
{
    delete ui;
}
order_arrange::save(){

}
void order_arrange::closeEvent(QCloseEvent *event)
{
    // 當窗口被關閉時，使用 deleteLater() 推遲銷毀
    this->deleteLater();  // 確保在事件循環後銷毀視窗

    // 可以添加額外的處理邏輯（例如發送信號等）
    QWidget::closeEvent(event);  // 呼叫基類的 closeEvent，執行正常的關閉操作
}
