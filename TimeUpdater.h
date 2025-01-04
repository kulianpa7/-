#ifndef TIMEUPDATER_H
#define TIMEUPDATER_H

#include <QObject>
#include <QTimer>
#include <QLabel>

class TimeUpdater : public QObject
{
    Q_OBJECT

public:
    explicit TimeUpdater(QLabel *label, QObject *parent = nullptr);
    ~TimeUpdater();

private slots:
    void updateTime();  // 槽函數，用於更新時間

private:
    QTimer *timer;  // 定時器
    QLabel *timeLabel;  // 顯示時間的 QLabel
};

#endif // TIMEUPDATER_H
