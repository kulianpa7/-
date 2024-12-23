#include "public_order_list.h"
#include "ui_public_order_list.h"

#include <BasePage.h>

public_order_list::public_order_list(BasePage *parent)
    : BasePage(parent)
    , ui(new Ui::public_order_list)
{
    ui->setupUi(this);
}


void public_order_list::closeEvent(QCloseEvent *event)
{
    // 當窗口被關閉時，使用 deleteLater() 推遲銷毀
    this->deleteLater();  // 確保在事件循環後銷毀視窗

    // 可以添加額外的處理邏輯（例如發送信號等）
    QWidget::closeEvent(event);  // 呼叫基類的 closeEvent，執行正常的關閉操作
}

public_order_list::~public_order_list()
{
    delete ui;
}
