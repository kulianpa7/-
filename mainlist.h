#ifndef MAINLIST_H
#define MAINLIST_H

#include <QMainWindow>
#include "ScrollAreaWidget.h"
#include "TimeUpdater.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainList;
}
QT_END_NAMESPACE

class MainList : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainList(QWidget *parent = nullptr);
    ~MainList();

private slots:
    void on_a_4LogOut_clicked();
    void on_b_1Today_clicked();
    void on_b_2History_clicked();

private:
    Ui::MainList *ui;
    TimeUpdater *timeUpdater;           // 時間更新器對象
    ScrollAreaWidget *scrollAreaWidget; // 滾動區域小部件
    void updateLabelsFromDatabase();
};

#endif // MAINLIST_H
