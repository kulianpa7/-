#include "mainlist.h"
#include "ui_mainlist.h"
#include "mainwindow.h"
#include "TimeUpdater.h"
#include "ScrollAreaWidget.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#include <remoteint.h>

MainList::MainList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainList)
{
    ui->setupUi(this);

    ui->b_1Today->setEnabled(false);
    ui->b_2History->setEnabled(true);

    scrollAreaWidget = new ScrollAreaWidget(this);
    ui->c_List->setWidget(scrollAreaWidget);

    timeUpdater = new TimeUpdater(ui->a_3TimeLabel, this);

    updateLabelsFromDatabase();
    scrollAreaWidget->updateContent(0); // 初始化為 Today 頁面
}

MainList::~MainList()
{
    delete ui;
    delete timeUpdater;
    delete scrollAreaWidget;
}

void MainList::updateLabelsFromDatabase()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "資料庫未開啟：" << db.lastError().text();
        return;
    }

    QString queryString = R"(
        SELECT
            driver."name",
            car.car_number
        FROM driver_car_scheduling AS dcs
        LEFT JOIN "time"
            ON time.time_code = dcs.time_code
        LEFT JOIN "driver"
            ON driver.id = dcs.driver_id
        LEFT JOIN "car"
            ON car.id = dcs.car_id
        WHERE
            driver_id = :driver_id AND
            "date" = :current_date AND
            time.start_time <= :current_time AND
            time.end_time >= :current_time
    )";

    QSqlQuery query;
    query.prepare(queryString);

    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
    QString currentTime = QTime::currentTime().toString("HH:mm:ss");

    remoteint remoteid;
    query.bindValue(":driver_id", remoteid.return_id());
    qDebug() << "mainlist id：" << remoteid.return_id();

    query.bindValue(":current_date", currentDate);
    query.bindValue(":current_time", currentTime);

    if (!query.exec()) {
        qDebug() << "查詢失敗：" << query.lastError().text();
        return;
    }

    if (query.next()) {
        ui->a_1NameLabel->setText(query.value("name").toString());
        ui->a_2CarLabel->setText(query.value("car_number").toString());
    } else {
        ui->a_1NameLabel->setText("未找到駕駛員");
        ui->a_2CarLabel->setText("未找到車輛編號");
    }
}

void MainList::on_a_4LogOut_clicked()
{
    ui->b_1Today->setEnabled(false);
    ui->b_2History->setEnabled(true);
    MainWindow *mainWindowPage = new MainWindow();
    mainWindowPage->show();
    this->close();
}

void MainList::on_b_1Today_clicked()
{
    ui->b_1Today->setEnabled(false);
    ui->b_2History->setEnabled(true);
    scrollAreaWidget->updateContent(0); // 更新為 Today 頁面
}

void MainList::on_b_2History_clicked()
{
    ui->b_1Today->setEnabled(true);
    ui->b_2History->setEnabled(false);
    scrollAreaWidget->updateContent(1); // 更新為 History 頁面
}
