#include "public_vehicle.h"
#include "ui_public_vehicle.h"
#include "BasePage.h"
public_velicle::public_velicle(BasePage *parent)
    : BasePage(parent)
    , ui(new Ui::public_velicle)
{
    ui->setupUi(this);
}

void public_velicle::closeEvent(QCloseEvent *event)
{
    // 當窗口被關閉時，使用 deleteLater() 推遲銷毀
    this->deleteLater();  // 確保在事件循環後銷毀視窗

    // 可以添加額外的處理邏輯（例如發送信號等）
    QWidget::closeEvent(event);  // 呼叫基類的 closeEvent，執行正常的關閉操作
}

public_velicle::~public_velicle()
{
    delete ui;
}
