#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginBt_clicked(); // 按鈕槽函數

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;  // 資料庫連接
};
#endif // MAINWINDOW_H
