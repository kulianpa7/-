#include "public_driver_arrange.h"
#include "ui_public_driver_arrange.h"
#include "BasePage.h"
#include "QMessageBox"
#include "QSqlError"
#include <functional>

#include <logger.h>

public_driver_arrange::public_driver_arrange(BasePage *parent)
    : BasePage(parent)
    , ui(new Ui::public_driver_arrange)
{
    ui->setupUi(this);
    // 連接 QDateEdit 的 dateChanged 信號到 onDateChanged 槽
    // 設定為目前的日期和時間
    ui->dateEdit->setDate(QDate(QDate::currentDate().year(), QDate::currentDate().month(), 1));
    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &public_driver_arrange::onDateChanged);
    connect(ui->comboBox_driver,&QComboBox::currentTextChanged,this,&public_driver_arrange::on_driver_changed);
    connect(ui->save_button ,&QPushButton::clicked,this,&public_driver_arrange::save);
    connect(ui->clear_button,&QPushButton::clicked,this,&public_driver_arrange::clear_check);
    QVector<QVector<int>> vec={{},{},{},{},{},{},{}};
    for(int i = 0;i<7;i++){
        for(int j = 0;j<6;j++){
            vec[i].push_back(j*7+i+1);
        }
    }
    // weekday 0 to 6
    for (int i = 0; i <= 6; ++i) {
        QPushButton* button = findChild<QPushButton*>(QString("weekday_%1").arg(i));
        if (button) {connect(button, &QPushButton::clicked, std::bind(&public_driver_arrange::push_button_checkboxANDcombobox, this, vec, i));}
    }
    // weekday_1to5
    for (int i = 1; i <= 5; ++i) {connect(ui->weekday_1to5,&QPushButton::clicked,std::bind(&public_driver_arrange::push_button_checkboxANDcombobox,this, vec, i));}
    combo_driver();
    combo_car();
    on_driver_changed();
    combo_box_car();

    QString comboBoxName = QString("comboBox_time_code");
    QComboBox* comboBox = findChild<QComboBox*>(comboBoxName);
    comboBox->addItem("早班", 1);
    comboBox->addItem("午班", 2);
    comboBox->addItem("晚班", 3);

    onDateChanged(ui->dateEdit->date());
}

public_driver_arrange::~public_driver_arrange()
{
    delete ui;
}
void public_driver_arrange::push_button_checkboxANDcombobox(QVector<QVector<int>> vec, int weekday) {
    QDate selectedDate = ui->dateEdit->date();  // Assume dateEdit is the date picker
    qDebug() << "Selected Date: " << selectedDate;
    int dayOfWeek = selectedDate.dayOfWeek();
    int first_day = 0;

    // Set the first day value (week start day)
    switch (dayOfWeek) {
    case 1: first_day = 2; break; // Monday
    case 2: first_day = 3; break; // Tuesday
    case 3: first_day = 4; break; // Wednesday
    case 4: first_day = 5; break; // Thursday
    case 5: first_day = 6; break; // Friday
    case 6: first_day = 7; break; // Saturday
    case 7: first_day = 1; break; // Sunday
    default: break;
    }

    int daysInMonth = selectedDate.daysInMonth();
    int lastDay = first_day + daysInMonth - 1; // Correct the range check

    if (vec.size() > weekday && !vec[weekday].isEmpty()) {
        for (int i = 0; i < vec[weekday].size(); ++i) {
            if (vec[weekday][i] >= first_day && vec[weekday][i] <= lastDay) {
                int carid = ui->comboBox_car->currentData().toInt();
                int codeid = ui->comboBox_time_code->currentData().toInt();

                // Handle checkbox
                QString checkBoxName = QString("checkBoxs_%1_%2").arg(vec[weekday][i]).arg(codeid);
                QCheckBox* checkBox = findChild<QCheckBox*>(checkBoxName);
                if (checkBox) {
                    checkBox->setChecked(true);
                } else {
                    qDebug() << "CheckBox not found: " << checkBoxName;
                }

                // Handle combo box
                QString comboBoxName = QString("comboBox_%1_%2").arg(vec[weekday][i]).arg(codeid);
                QComboBox* comboBox = findChild<QComboBox*>(comboBoxName);
                if (comboBox) {
                    int index = comboBox->findData(carid);
                    if (index != -1) {
                        comboBox->setCurrentIndex(index);
                    } else {
                        comboBox->setCurrentIndex(0); // Default selection
                    }
                } else {
                    qDebug() << "ComboBox not found or has no items: " << comboBoxName;
                }
            }
        }
    } else {
        qDebug() << "Invalid weekday or empty vector for the given weekday.";
    }
}

void public_driver_arrange::combo_box_car() {
    // 获取用户选择的日期
    QDate selectedDate = ui->dateEdit->date();
    qDebug() << "Selected Date: " << selectedDate;

    // 查询车辆数据
    QSqlQuery query;
    query.prepare("SELECT id, car_number FROM car WHERE is_del = 0 AND car_situation_id = 1");
    if (!query.exec()) {
        qDebug() << "Failed to query cars:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "無法加載車輛數據：" + query.lastError().text());
        return;
    }

    // 清空所有 QComboBox 的内容并填充车辆数据
    for (int row = 1; row <= 42; ++row) { // 遍历所有 42 行
        for (int col = 1; col <= 3; ++col) { // 遍历 3 列
            QString comboBoxName = QString("comboBox_%1_%2").arg(row).arg(col);
            QComboBox* comboBox = findChild<QComboBox*>(comboBoxName);
            if (comboBox) {
                comboBox->clear(); // 清空旧数据

                // 填充车辆数据
                int carId = -1;
                QString carNumber = "--------";
                comboBox->addItem(carNumber, carId); // 添加到 ComboBox，ID 作为数据项
                while (query.next()) {
                    int carId = query.value("id").toInt();
                    QString carNumber = query.value("car_number").toString();
                    comboBox->addItem(carNumber, carId); // 添加到 ComboBox，ID 作为数据项
                }

                // 重置查询游标，确保车辆数据可以重复使用
                query.first();
                query.previous();
            } else {
                qDebug() << "ComboBox not found for name:" << comboBoxName;
            }
        }
    }
}
void public_driver_arrange::closeEvent(QCloseEvent *event)
{
    // 當窗口被關閉時，使用 deleteLater() 推遲銷毀
    this->deleteLater();  // 確保在事件循環後銷毀視窗

    // 可以添加額外的處理邏輯（例如發送信號等）
    QWidget::closeEvent(event);  // 呼叫基類的 closeEvent，執行正常的關閉操作
}
void public_driver_arrange::on_driver_changed() {
    QDate selectedDate = ui->dateEdit->date();  // 假设 dateEdit 是日期选择控件
    qDebug() << "Selected Date: " << selectedDate;
    int dayOfWeek = selectedDate.dayOfWeek();
    int first_day = 0;
    // 設定第一天的值（第一天為星期幾）
    switch (dayOfWeek) {
    case 1: first_day = 2;break;// Monday
    case 2: first_day = 3;break;// Tuesday
    case 3: first_day = 4;break;// Wednesday
    case 4: first_day = 5;break;// Thursday
    case 5: first_day = 6;break;// Friday
    case 6: first_day = 7;break;// Saturday
    case 7: first_day = 1;break;// Sunday
    default:break;
    }
    // 计算当前月份的第一天和最后一天
    QDate firstDayOfMonth(selectedDate.year(), selectedDate.month(), 1);
    QDate lastDayOfMonth = firstDayOfMonth.addMonths(1).addDays(-1);

    qDebug() << "Month Range: " << firstDayOfMonth << " to " << lastDayOfMonth;

    // 查询数据库以获取整个 12 月的 driver_car_scheduling 数据
    QSqlQuery query;
    query.prepare("SELECT id, date, time_id, driver_id, car_id, time_code "
                  "FROM driver_car_scheduling "
                  "WHERE date BETWEEN :start_date AND :end_date AND driver_id = :driverId");
    query.bindValue(":start_date", firstDayOfMonth);
    query.bindValue(":end_date", lastDayOfMonth);
    query.bindValue(":driverId", ui->comboBox_driver->currentData().toInt());
    // 执行查询并检查结果
    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "無法加載排程數據：" + query.lastError().text());
        return;
    }

    // 清空所有复选框状态
    for (int row = 1; row <= 42; ++row) {  // 遍历所有 42 行
        for (int col = 1; col <= 3; ++col) {  // 遍历 3 列
            QString checkBoxName = QString("checkBoxs_%1_%2").arg(row).arg(col);
            QCheckBox* checkBox = findChild<QCheckBox*>(checkBoxName);
            if (checkBox) {
                checkBox->setChecked(false);  // 重置复选框状态
            }
            QString comboBoxName = QString("comboBox_%1_%2").arg(row).arg(col);
            QComboBox* comboBox = findChild<QComboBox*>(comboBoxName);
            int index = comboBox->findData(-1);
            if (index != -1)    comboBox->setCurrentIndex(index);  // 设置为当前选中项
            else                comboBox->setCurrentIndex(0);  // 如果找不到，设置默认值
        }
    }
    // 遍历查询结果并设置对应的复选框状态
    while (query.next()) {
        int timeCode = query.value("time_code").toInt();  // 获取 time_code
        int row = query.value("date").toString().split('-')[2].toInt();  // 假设 date 对应的是行号
        int col = (timeCode % 3) + 1;  // 假设 time_code 与列号相关，0 -> 1, 1 -> 2, 2 -> 3
        QString checkBoxName = QString("checkBoxs_%1_%2").arg(first_day+row-1).arg(col);
        QCheckBox* checkBox = findChild<QCheckBox*>(checkBoxName);

        QString comboBoxName = QString("comboBox_%1_%2").arg(first_day+row-1).arg(col);
        QComboBox* comboBox = findChild<QComboBox*>(comboBoxName);

        if (checkBox) {
            checkBox->setChecked(true);  // 设置复选框为选中
        } else {
            qDebug() << "CheckBox not found for name:" << checkBoxName;
        }
        int index = comboBox->findData(query.value("car_id").toInt());
        if (index != -1)    comboBox->setCurrentIndex(index);  // 设置为当前选中项
        else                comboBox->setCurrentIndex(0);  // 如果找不到，设置默认值
    }
}
void public_driver_arrange::combo_driver() {
    // 清空已有的 QComboBox 条目（假设 QComboBox 名为 driverComboBox）
    ui->comboBox_driver->clear();

    // 查询数据库以获取未删除的司机
    QSqlQuery query;
    query.prepare("SELECT id, name FROM driver WHERE is_del = 0");

    // 执行查询并检查是否成功
    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "無法加載司機數據：" + query.lastError().text());
        return;
    }

    // 遍历查询结果，将司机数据添加到 QComboBox
    while (query.next()) {
        int driverId = query.value("id").toInt();         // 获取司机 ID
        QString driverName = query.value("name").toString(); // 获取司机姓名

        // 将司机的名字作为显示文本，ID 作为 UserRole 数据存储
        ui->comboBox_driver->addItem(driverName, driverId);
    }

    // 可选：设置默认选项（例如：提示选择）
    if (ui->comboBox_driver->count() == 0) {
        ui->comboBox_driver->addItem("無司機可選", QVariant()); // 当无数据时添加占位提示
    } else {
        ui->comboBox_driver->setCurrentIndex(0); // 默认选择第一个条目
    }
}
void public_driver_arrange::clear_check(){
    // 清空所有复选框状态
    for (int row = 1; row <= 42; ++row) {  // 遍历所有 42 行
        for (int col = 1; col <= 3; ++col) {  // 遍历 3 列
            QString checkBoxName = QString("checkBoxs_%1_%2").arg(row).arg(col);
            QCheckBox* checkBox = findChild<QCheckBox*>(checkBoxName);
            if (checkBox) {
                checkBox->setChecked(false);  // 重置复选框状态
            }
            QString comboBoxName = QString("comboBox_%1_%2").arg(row).arg(col);
            QComboBox* comboBox = findChild<QComboBox*>(comboBoxName);
            int index = comboBox->findData(-1);
            if (index != -1)    comboBox->setCurrentIndex(index);  // 设置为当前选中项
            else                comboBox->setCurrentIndex(0);  // 如果找不到，设置默认值
        }
    }
}

void public_driver_arrange::save(){
    QDate selectedDate = ui->dateEdit->date();  // 假设 dateEdit 是日期选择控件
    qDebug() << "Selected Date: " << selectedDate;
    int dayOfWeek = selectedDate.dayOfWeek();
    int daysInMonth = selectedDate.daysInMonth();
    int first_day = 0;
    // 設定第一天的值（第一天為星期幾）
    switch (dayOfWeek) {
    case 1: first_day = 2;break;// Monday
    case 2: first_day = 3;break;// Tuesday
    case 3: first_day = 4;break;// Wednesday
    case 4: first_day = 5;break;// Thursday
    case 5: first_day = 6;break;// Friday
    case 6: first_day = 7;break;// Saturday
    case 7: first_day = 1;break;// Sunday
    default:break;
    }
    QVector<QMap<QString, QString>> results;
    QString driverid = ui->comboBox_driver->currentData().toString();
    QMap<int,int> code_to_id;
    // 查询数据库以获取整个 12 月的 driver_car_scheduling 数据
    QSqlQuery query;
    query.prepare("SELECT id, time_code FROM \"time\" ");
    // 执行查询并检查结果
    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "無法加載排程數據：" + query.lastError().text());
        return;
    }
    while (query.next()) {code_to_id[query.value("time_code").toInt()] = query.value("id").toInt();}
    deleteAllForMonth();
    for (int i = 1; i <= 42; ++i) {
        if (i >= first_day && i < first_day + daysInMonth) {
            QString frameName = QString("frames_%1").arg(i);
            QWidget *frame = findChild<QWidget*>(frameName);
            QString lineEditName = QString("lineEdits_%1").arg(i);
            QLineEdit *lineEdit = frame->findChild<QLineEdit*>(lineEditName);
            // Initialize check maps for each row (1, 2, 3)
            QMap<QString, QString> check1, check2, check3;
            // Iterate over columns (1, 2, 3)
            for (int col = 1; col <= 3; ++col) {
                QString checkBoxName = QString("checkBoxs_%1_%2").arg(i).arg(col);
                QCheckBox* checkBox = findChild<QCheckBox*>(checkBoxName);
                QString comboBoxName = QString("comboBox_%1_%2").arg(i).arg(col);
                QComboBox* comboBox = findChild<QComboBox*>(comboBoxName);
                // Use different check maps for each column
                if (checkBox && comboBox) {
                    QString checkState = (checkBox->checkState() == Qt::Checked) ? comboBox->currentData().toString() : QString();
                    if (col == 1) check1["check1"] = checkState;
                    if (col == 2) check2["check2"] = checkState;
                    if (col == 3) check3["check3"] = checkState;
                }
            }
            // Create a QMap and populate it
            QMap<QString, QString> resultMap;
            resultMap["day"] = lineEdit->text();
            resultMap["check1"] = check1.value("check1", QString());
            resultMap["check2"] = check2.value("check2", QString());
            resultMap["check3"] = check3.value("check3", QString());
            // Now push the map into the results vector
            results.push_back(resultMap);
        }
    }
    qDebug() << results << '\n';
    QString date = ui->dateEdit->text();
    for (const auto& mapc : results) {
        QString check1 = mapc.value("check1");
        QString check2 = mapc.value("check2");
        QString check3 = mapc.value("check3");
        if(!check1.isEmpty()){
            query.prepare("INSERT INTO driver_car_scheduling "
                          "(\"date\", time_id, driver_id, car_id, time_code) "
                          "VALUES (:date, :time_id, :driver_id, :car_id, :time_code)");

            query.bindValue(":date"         , date.replace('/','-')+"-"+mapc.value("day"));
            query.bindValue(":time_id"      , code_to_id[0]);
            query.bindValue(":driver_id"    , driverid);
            query.bindValue(":car_id"       , check1);
            query.bindValue(":time_code"    , 0);
            // 执行查询并检查结果
            if (!query.exec()) {
                qDebug() << "Failed to execute query:" << query.lastError().text();
                QMessageBox::critical(this, "Database Error", "無法加載排程數據：" + query.lastError().text());
                return;
            }
        }
        if(!check2.isEmpty()){
            query.prepare("INSERT INTO driver_car_scheduling "
                          "(\"date\", time_id, driver_id, car_id, time_code) "
                          "VALUES (:date, :time_id, :driver_id, :car_id, :time_code)");

            query.bindValue(":date"         , date.replace('/','-')+"-"+mapc.value("day"));
            query.bindValue(":time_id"      , code_to_id[1]);
            query.bindValue(":driver_id"    , driverid);
            query.bindValue(":car_id"       , check2);
            query.bindValue(":time_code"    , 1);
            // 执行查询并检查结果
            if (!query.exec()) {
                qDebug() << "Failed to execute query:" << query.lastError().text();
                QMessageBox::critical(this, "Database Error", "無法加載排程數據：" + query.lastError().text());
                return;
            }
        }
        if(!check3.isEmpty()){
            query.prepare("INSERT INTO driver_car_scheduling "
                          "(\"date\", time_id, driver_id, car_id, time_code) "
                          "VALUES (:date, :time_id, :driver_id, :car_id, :time_code)");

            query.bindValue(":date"         , date.replace('/','-')+"-"+mapc.value("day"));
            query.bindValue(":time_id"      , code_to_id[2]);
            query.bindValue(":driver_id"    , driverid);
            query.bindValue(":car_id"       , check3);
            query.bindValue(":time_code"    , 2);
            // 执行查询并检查结果
            if (!query.exec()) {
                qDebug() << "Failed to execute query:" << query.lastError().text();
                QMessageBox::critical(this, "Database Error", "無法加載排程數據：" + query.lastError().text());
                return;
            }
        }
    }
    logger log_ins;
    QString logMessage = QString("%1 修改了單月的排班資料，月份:%2 司機編號: %3")
                             .arg(log_ins.return_username())
                             .arg(selectedDate.toString()).arg(driverid);
    log_ins.save_logger(logMessage);
    onDateChanged(ui->dateEdit->date());

}

void public_driver_arrange::combo_car() {
    // 清空已有的 QComboBox 条目（假设 QComboBox 名为 driverComboBox）
    ui->comboBox_car->clear();

    // 查询数据库以获取未删除的司机
    QSqlQuery query;
    query.prepare("SELECT id, car_number as name FROM car WHERE is_del = 0");

    // 执行查询并检查是否成功
    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "無法加載車輛資料庫：" + query.lastError().text());
        return;
    }

    // 遍历查询结果，将司机数据添加到 QComboBox
    while (query.next()) {
        int driverId = query.value("id").toInt();         // 获取car ID
        QString driverName = query.value("name").toString(); // 获取 car name

        // 将司机的名字作为显示文本，ID 作为 UserRole 数据存储
        ui->comboBox_car->addItem(driverName, driverId);
    }

    // 可选：设置默认选项（例如：提示选择）
    if (ui->comboBox_car->count() == 0) {
        ui->comboBox_car->addItem("無車輛可選", QVariant()); // 当无数据时添加占位提示
    } else {
        ui->comboBox_car->setCurrentIndex(0); // 默认选择第一个条目
    }
}

void public_driver_arrange::onDateChanged(const QDate &date)
{
    on_driver_changed();
    // 當 QDateEdit 的日期改變時執行的操作
    qDebug() << "Selected Date: " << date;

    // 獲取這個日期的星期幾（1=星期一，7=星期日）
    int dayOfWeek = date.dayOfWeek();
    int first_day = 0;
    // 設定第一天的值（第一天為星期幾）
    switch (dayOfWeek) {
    case 1: first_day = 2;break;// Monday
    case 2: first_day = 3;break;// Tuesday
    case 3: first_day = 4;break;// Wednesday
    case 4: first_day = 5;break;// Thursday
    case 5: first_day = 6;break;// Friday
    case 6: first_day = 7;break;// Saturday
    case 7: first_day = 1;break;// Sunday
    default:break;
    }

    // 獲取當月的天數
    int daysInMonth = date.daysInMonth();
    qDebug() << "Number of days in this month: " << daysInMonth;

    // 計算最後一天的日子
    int last_day = first_day + daysInMonth - 1;
    qDebug() << "Last day position: " << last_day;

    // 設定 frames 的背景顏色並填充日期
    for (int i = 1; i <= 42; ++i) {
        QString line_editName = QString("lineEdits_%1").arg(i);
        // 查找對應的 QLineEdit
        QLineEdit* lineEdit = this->findChild<QLineEdit*>(line_editName);
        if (lineEdit) {
            lineEdit->clear(); // 清空內容
        } else {
            qDebug() << "QLineEdit not found with object name:" << line_editName;
        }
        // 檢查 frame 是否顯示在該月份的範圍內
        if (i >= first_day && i < first_day + daysInMonth) {
            int day = i - first_day + 1;

            // 設置背景顏色，根據日子設置顏色
            QString color = "background-color: rgba(0, 100, 255, 100);";

            // 設置每個 frame 的背景顏色，確保只影響 QFrame
            QString frameName = QString("frames_%1").arg(i);
            QWidget *frame = findChild<QWidget*>(frameName);
            if (frame) {
                // 設置樣式，僅改變 QFrame 的背景顏色
                frame->setStyleSheet("QFrame { " + color + " border: none; }"
                                     "QComboBox{background-color: rgba(100, 100, 100,100);}");

                // 尋找 QLineEdit，並填入日期
                QString lineEditName = QString("lineEdits_%1").arg(i);
                QLineEdit *lineEdit = frame->findChild<QLineEdit*>(lineEditName);
                if (lineEdit) {
                    // 設置 QLineEdit 內容為當前日期
                    lineEdit->setText(QString::number(day));

                    // 設置 QLineEdit 為只讀，禁止修改
                    lineEdit->setReadOnly(true);
                }
            }
        } else {
            // 將不屬於當月的 frames 設置為透明或其他顏色
            QString frameName = QString("frames_%1").arg(i);
            QWidget *frame = findChild<QWidget*>(frameName);
            if (frame) {
                frame->setStyleSheet("QFrame { background-color: rgba(0, 0, 0, 100); border: none; }");
            }
        }
    }
}

void public_driver_arrange::deleteAllForMonth() {
    // Get the selected date from the date edit widget
    QString date = ui->dateEdit->text();
    int DriverId = ui->comboBox_driver->currentData().toInt();

    qDebug() << "Selected Date from UI: " << DriverId;
    qDebug() << "Date:" << date;
    // Convert it to QDate for easier manipulation
    QDate selectedDate = QDate::fromString(date, "yyyy/MM");
    qDebug() << "Selected selectedDate from UI: " << selectedDate;
    // Get the year and month from the selected date
    int year = selectedDate.year();
    int month = selectedDate.month();

    // Construct the start of the month and end of the month in "yyyy-MM-dd" format
    QDate startOfMonth(year, month, 1);
    QDate endOfMonth = startOfMonth.addMonths(1).addDays(-1);  // End date is the last day of the month

    // Convert to string format (e.g., "yyyy-MM-dd")
    QString startDateString = startOfMonth.toString("yyyy-MM-dd");
    QString endDateString = endOfMonth.toString("yyyy-MM-dd");
    qDebug() << "Start Date: " << startDateString;
    qDebug() << "End Date: " << endDateString;

    // Prepare and execute the DELETE query
    QSqlQuery query;
    query.prepare("DELETE FROM driver_car_scheduling "
                  "WHERE \"date\" BETWEEN :start_date AND :end_date AND driver_id = :driver_id");
    query.bindValue(":start_date", startDateString);
    query.bindValue(":end_date", endDateString);
    query.bindValue(":driver_id", DriverId);
    query.exec();
}

