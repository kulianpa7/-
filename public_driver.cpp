#include "public_driver.h"
#include "ui_public_driver.h"
#include "BasePage.h"

public_driver::public_driver(BasePage *parent)
    : BasePage(parent)
    , ui(new Ui::public_driver)
{
    ui->setupUi(this);
}
void public_driver::closeEvent(QCloseEvent *event)
{
    // 當窗口被關閉時，使用 deleteLater() 推遲銷毀
    this->deleteLater();  // 確保在事件循環後銷毀視窗

    // 可以添加額外的處理邏輯（例如發送信號等）
    QWidget::closeEvent(event);  // 呼叫基類的 closeEvent，執行正常的關閉操作
}
public_driver::~public_driver()
{
    delete ui;
}
