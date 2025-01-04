#include "TimeUpdater.h"
#include <QDateTime>

TimeUpdater::TimeUpdater(QLabel *label, QObject *parent)
    : QObject(parent), timeLabel(label)
{
    // 創建定時器，每秒更新一次時間
    timer = new QTimer(this);

    // 連接定時器的 timeout 信號到槽函數 updateTime()
    connect(timer, &QTimer::timeout, this, &TimeUpdater::updateTime);

    // 開始定時器，每秒觸發一次
    timer->start(1000);

    // 初始化時間顯示
    updateTime();
}

TimeUpdater::~TimeUpdater()
{
    delete timer;
}

void TimeUpdater::updateTime()
{
    // 獲取當前時間並轉換為字符串
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    // 更新時間顯示
    timeLabel->setText(currentTime);
}
