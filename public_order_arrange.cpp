#include "public_order_arrange.h"
#include "ui_public_order_arrange.h"
#include <BasePage.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QComboBox>
#include <QDateTime>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QString>
#include <QSqlError>
#include <QMessageBox>

#include <logger.h>

order_arrange::order_arrange(BasePage *parent)
    : BasePage(parent)
    , ui(new Ui::order_arrange)
{

    ui->setupUi(this);
    // 設定為目前的日期和時間
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");

    // 連接 lineEdit 的 textChanged 信號到 change_driver 槽
    connect(ui->can_passanger, &QLineEdit::textChanged, this, &order_arrange::change_driver);
    // 連接 dateTimeEdit 的 dateTimeChanged 信號到 change_driver 槽
    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &order_arrange::change_driver);

    connect(ui->save, &QPushButton::clicked, this, &order_arrange::save);
}

order_arrange::~order_arrange()
{
    delete ui;
}
void order_arrange::closeEvent(QCloseEvent *event)
{
    // 當窗口被關閉時，使用 deleteLater() 推遲銷毀
    this->deleteLater();  // 確保在事件循環後銷毀視窗

    // 可以添加額外的處理邏輯（例如發送信號等）
    QWidget::closeEvent(event);  // 呼叫基類的 closeEvent，執行正常的關閉操作
}

void order_arrange::change_driver() {
    // 獲取 UI 控件中的值
    int canPassenger = ui->can_passanger->text().toInt(); // 從 QLineEdit 獲取 can_passenger 的值
    QDateTime selectedDateTime = ui->dateTimeEdit->dateTime(); // 從 QDateTimeEdit 獲取時間
    QString startTime = selectedDateTime.time().toString("HH:mm:ss");
    QString endTime = selectedDateTime.time().toString("HH:mm:ss");
    QString date = selectedDateTime.date().toString("yyyy/MM/dd");
    // 查詢資料庫
    QSqlQuery query;
    query.prepare(R"(
        SELECT
            dcs.id AS dcs_id,
            car.id AS car_id,
            driver.id AS driver_id,
            driver.name AS driver_name
        FROM driver_car_scheduling AS dcs
        LEFT JOIN driver
            ON driver.id = dcs.driver_id
        LEFT JOIN car
            ON car.id = dcs.car_id
        LEFT JOIN time te
            ON te.id = dcs.time_id
        WHERE
            car.can_passenger >= :can_passenger AND
            car.car_situation_id = 1 AND
            te.start_time <= :start_time AND
            te.end_time >= :end_time AND
            dcs.date = :date;
    )");
    query.bindValue(":can_passenger", canPassenger);
    query.bindValue(":start_time", startTime);
    query.bindValue(":end_time", endTime);
    query.bindValue(":date", date);

    if (!query.exec()) {
        qWarning() << "Database query failed:" << query.lastError().text();
        return;
    }
    // 清空 comboBox
    ui->comboBox->clear();
    // 將結果添加到 comboBox
    while (query.next()) {
        QString driverName = query.value("driver_name").toString();
        int dcsId = query.value("dcs_id").toInt();
        int carId = query.value("car_id").toInt();
        int driverId = query.value("driver_id").toInt();
        // 將資料以 key-value 形式存入 comboBox
        QString displayText = QString("%1 (Driver_id: %2)").arg(driverName).arg(driverId);
        QString dataValue = QString("%1,%2,%3").arg(dcsId).arg(carId).arg(driverId);
        ui->comboBox->addItem(displayText, dataValue);
    }
}
void order_arrange::save() {
    // 從 UI 控件中獲取資料
    QString passengerName = ui->contact->text(); // 乘客姓名
    QString phone = ui->contact_phone->text(); // 聯絡電話
    int howMany = ui->can_passanger->text().toInt(); // 乘客人數
    QDateTime dateTime = ui->dateTimeEdit->dateTime(); // 日期時間
    QString dateTimeStr = dateTime.toString("yyyy-MM-dd HH:mm:ss"); // 格式化日期時間
    QString position = ui->location->text(); // 乘客位置

    // 獲取 comboBox 選中的值
    QStringList comboData = ui->comboBox->currentData().toString().split(",");
    if (comboData.size() != 3) {
        qWarning() << "Invalid comboBox data";
        return;
    }

    int driverCarSchedulingId = comboData[0].toInt(); // dcs_id
    int driverId = comboData[2].toInt();             // driver_id
    int carId = comboData[1].toInt();                // car_id

    // 插入資料到 orders 資料表
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO orders (passenger_name, phone, how_many, date_time, position, driver_car_scheduling_id, driver_id, car_id,order_status)
        VALUES (:passenger_name, :phone, :how_many, :date_time, :position, :driver_car_scheduling_id, :driver_id, :car_id,:order_status)
        RETURNING id;
    )");
    query.bindValue(":passenger_name", passengerName);
    query.bindValue(":phone", phone);
    query.bindValue(":how_many", howMany);
    query.bindValue(":date_time", dateTimeStr);
    query.bindValue(":position", position);
    query.bindValue(":driver_car_scheduling_id", driverCarSchedulingId);
    query.bindValue(":driver_id", driverId);
    query.bindValue(":car_id", carId);
    query.bindValue(":order_status", -1);
    if (!query.exec()) {
        qWarning() << "Insert into orders failed:" << query.lastError().text();
        return;
    }
    // 獲取返回的訂單 ID
    int orderId = -1;
    if (query.next()) {
        orderId = query.value(0).toInt();
    }
    // 插入成功，記錄日志
    logger log_ins;
    QString logMessage = QString("%1 添加了一筆訂單，訂單編號: %2")
                             .arg(log_ins.return_username())
                             .arg(orderId);
    log_ins.save_logger(logMessage);
    // 插入成功的提示
    QMessageBox::information(this, "Save", "Order has been saved successfully!");
}
