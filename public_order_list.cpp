#include "public_order_list.h"
#include "ui_public_order_list.h"

#include <BasePage.h>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <Qstring>
#include <QCryptographicHash>
#include <QByteArray>
#include <QMessageBox>
#include <QComboBox>

#include <logger.h>

public_order_list::public_order_list(BasePage *parent)
    : BasePage(parent)
    , ui(new Ui::public_order_list)
{
    ui->setupUi(this);

    connect(ui->refresh_button, &QPushButton::clicked, this, &public_order_list::loadDataFromDatabase);

    ui->tableWidget->setColumnCount(9);  // 8 列
    // 設置表格標題
    ui->tableWidget->setHorizontalHeaderLabels({
        "乘客名稱", "電話", "乘客數量","地址","司機","車牌號碼","時間","狀態","刪除按鈕"
    });
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &public_order_list::onCellChanged);
    // 從資料庫載入資料
    loadDataFromDatabase();
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

void public_order_list::loadDataFromDatabase()
{
    disconnect(ui->tableWidget, &QTableWidget::cellChanged, this, &public_order_list::onCellChanged);
    // 执行数据库查询，选取所有角色数据
    QSqlQuery query(
        "SELECT "
        "    o.id, "
        "    o.passenger_name, "
        "    o.phone, "
        "    o.how_many, "
        "    o.date_time, "
        "    o.driver_id,"
        "    o.car_id,"
        "    o.position,"
        "    o.order_status,"
        "    d.\"name\" AS driver_name, "
        "    car.car_number AS car_number, "
        "    os.\"status\" AS now_status "
        "FROM orders AS o "
        "LEFT JOIN driver d ON o.driver_id = d.id "
        "LEFT JOIN car ON o.car_id = car.id "
        "LEFT JOIN driver_car_scheduling dcs ON o.driver_car_scheduling_id = dcs.id "
        "LEFT JOIN order_status os ON o.order_status = os.id "
        "WHERE o.is_del = 0;"
        );
    // 查询角色数据并缓存，以便以后使用
    QSqlQuery roleQuery("SELECT id, \"status\" FROM order_status");
    QMap<int, QString> rolesMap;
    while (roleQuery.next()) {
        int roleId = roleQuery.value("id").toInt();
        QString roleName = roleQuery.value("status").toString();
        rolesMap.insert(roleId, roleName);
    }
    // 清除表格中的现有行
    ui->tableWidget->setRowCount(0);

    int row = 0;  // 用于记录当前插入的行索引

    // 遍历查询结果并填充表格
    while (query.next()) {
        // 在 TableWidget 插入一行
        ui->tableWidget->insertRow(row);
        QVector<QString>
            strs ={
                "passenger_name",
                "phone",
                "how_many",
                "position",
                "driver_name",
                "car_number",
                "date_time",
            };
        for (int i = 0; i < strs.length(); ++i) {
            QTableWidgetItem* item = new QTableWidgetItem(query.value(strs[i]).toString());
            if (i == 0) item->setData(Qt::UserRole, query.value("id"));
            if (i == 4 || i == 5 || i==6) item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            item->setTextAlignment(Qt::AlignCenter);  // 置中對齊
            ui->tableWidget->setItem(row, i, item);  // 插入到表格中
        }

        // 创建下拉框 (QComboBox) 并填充角色名称
        QComboBox *comboBox = new QComboBox();
        // 将角色列表添加到下拉框
        for (auto it = rolesMap.begin(); it != rolesMap.end(); ++it) {
            comboBox->addItem(it.value(), it.key());  // 角色名作为显示值，id作为隐藏数据
        }

        // 设置下拉框默认选中的值为当前用户的角色
        int currentRoleId = query.value("order_status").toInt();
        int index = comboBox->findData(currentRoleId);
        if (index >= 0) {
            comboBox->setCurrentIndex(index);
        }
        // 将下拉框放入第二列
        ui->tableWidget->setCellWidget(row, 7, comboBox);
        // // 连接 QComboBox 的 currentIndexChanged 信号
        connect(comboBox, &QComboBox::currentIndexChanged, this, [this, row](int index) {
            qDebug() << "Row" << row << ", Column 1 (Role) index changed!";
            this->onCellChanged(row); // 呼叫行改變槽函式
        });

        // 插入删除按钮到最后一列
        QPushButton *deleteButton = new QPushButton("删除");
        deleteButton->setStyleSheet(
            "font-size: 12px; "
            "height: 30px; "
            "width: 20px; "
            "min-height:30px; "
            "min-width:40px; "
            "max-height:30px; "
            "max-width:40px; "
            "margin-left: 25%; "
            "margin-right: 25%;"
            );
        deleteButton->setProperty("rowId", query.value("id"));
        // 连接按钮的点击信号到 deleteRow 槽函数
        connect(deleteButton, &QPushButton::clicked, this, [this, deleteButton]() {
            int id = deleteButton->property("rowId").toInt();  // 获取隐藏的 id
            this->deleteRow(id);
        });

        // 将删除按钮添加到表格
        ui->tableWidget->setCellWidget(row, ui->tableWidget->columnCount() - 1, deleteButton);
        qDebug() << row << " ------------------------------------ \n";
        row++;  // 增加行索引
    }

    // 设置列和行的自动调整大小
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

    // 计算某一行的宽度
    int rowWidth = 0;
    int rowIndex = 0;  // 假设要计算第 0 行的宽度
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        rowWidth += ui->tableWidget->columnWidth(col);  // 获取该列的宽度
    }
    // 增加额外的 20 宽度来调整窗口
    int currentWidth = this->width();  // 获取当前窗口宽度
    this->resize(rowWidth + 45, this->height());  // 设置新宽度并保持高度不
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &public_order_list::onCellChanged);
}
void public_order_list::onCellChanged(int row) {
    int id = ui->tableWidget->item(row, 0)->data(Qt::UserRole).toInt();
    // 檢查行號是否有效
    if (row < 0 || row >= ui->tableWidget->rowCount()) {
        qDebug() << "Invalid row number:" << row;
        return;
    }

    qDebug() << "Row changed:" << row;

    // 遍歷該行的所有列，輸出狀態
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        QWidget *widget = ui->tableWidget->cellWidget(row, col);

        if (widget && qobject_cast<QComboBox *>(widget)) {
            // 檢查是否是 QComboBox
            QComboBox *comboBox = qobject_cast<QComboBox *>(widget);
            int selectedRoleId = comboBox->currentData().toInt();
            qDebug() << "Column" << col << ": QComboBox selected Role ID:" << selectedRoleId;
        } else if (ui->tableWidget->item(row, col)) {
            // 如果是普通的 QTableWidgetItem，直接輸出文本和隱藏數據
            QTableWidgetItem *item = ui->tableWidget->item(row, col);
            qDebug() << "Column" << col
                     << ": Text:" << item->text()
                     << ": data:" << item->data(Qt::UserRole).toString();
        } else {
            qDebug() << "Column" << col << ": Empty";
        }
    }

    // 從第一列取得資料庫中記錄的 ID
    if (ui->tableWidget->item(row, 0)) {
        int id = ui->tableWidget->item(row, 0)->data(Qt::UserRole).toInt();
        // 保存數據到資料庫
        saveDataToDatabase(row, id);
        loadDataFromDatabase();  // 重新加載數據，更新顯示
    } else {
        qDebug() << "Row" << row << "does not have a valid ID in column 0.";
    }
}
void public_order_list::deleteRow(int id) {
    // 使用 sender() 獲取信號的發送者
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) {
        qDebug() << "Error: Sender is not a QPushButton.";
        return;
    }
    // 獲取按鈕所在的行
    int row = -1;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        if (ui->tableWidget->cellWidget(i, ui->tableWidget->columnCount() - 1) == button) {
            row = i;
            break;
        }
    }
    // 檢查行號是否有效
    if (row < 0 || row >= ui->tableWidget->rowCount()) {
        qDebug() << "Invalid row number:" << row;
        return;
    }
    // 彈出確認對話框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        "確認刪除",
        QString("您確定要刪除第 %1 行嗎？").arg(row + 1),
        QMessageBox::Yes | QMessageBox::No
        );
    // 如果用戶點擊 "Yes"，刪除行
    if (reply == QMessageBox::Yes) {
        QSqlQuery deleteQuery;
        deleteQuery.prepare("UPDATE orders SET is_del = 1 WHERE id = :id");
        deleteQuery.bindValue(":id", id);
        if (deleteQuery.exec()) {
            qDebug() << "Row deleted successfully!";
        }
        logger log_ins;
        QString logMessage = QString("%1 刪除了一筆訂單，訂單編號: %2")
                                 .arg(log_ins.return_username())
                                 .arg(id);
        log_ins.save_logger(logMessage);
        loadDataFromDatabase();
        qDebug() << "Row" << row << "deleted successfully!";
    } else {
        qDebug() << "Row deletion canceled.";
    }
}

// 儲存特定行資料到資料庫
void public_order_list::saveDataToDatabase(int row, int id)
{
    if (row < 0 || row >= ui->tableWidget->rowCount()) {
        qDebug() << "ERROR: Invalid row:" << row;
        return;
    }
    int currentUserId = 0; // 初始化当前用户 ID
    // 检查第 0 列的 QTableWidgetItem 是否存在
    if (ui->tableWidget->item(row, 0) != nullptr) {
        QVariant idData = ui->tableWidget->item(row, 0)->data(Qt::UserRole);
        if (idData.isValid()) {
            currentUserId = idData.toInt();
        } else {
            qDebug() << "Error: ID data not found in Qt::UserRole.";
        }
    }
    // 取得該行的用戶名，並檢查是否為空
    QVector<QString> strs;
    for(int i = 0 ;i<=3;++i){
        if (ui->tableWidget->item(row, i) != nullptr) {
            strs.push_back(ui->tableWidget->item(row, i)->text());
        }
    }
    qDebug() <<"data = "<<strs<< '\n';
    // strs ={
    //     "passenger_name",
    //     "phone",
    //     "how_many",
    //     "position",
    // };
    QString order_status_id = "";
    // 确保单元格内确实有一个小部件（假设在第 7 列）
    if (ui->tableWidget->cellWidget(row, 7) != nullptr) {
        QComboBox* comboBox = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(row, 7));
        if (comboBox != nullptr) {
            order_status_id = comboBox->currentData().toString(); // 获取与当前选项关联的Data
        } else {
            qDebug() << "Error: The widget in the cell is not a QComboBox.";
        }
    } else {
        qDebug() << "Error: No widget in the specified cell.";
    }
    // 先初始化 SQL 查询
    QString sql =
        "UPDATE orders SET "
        "passenger_name   = :passenger_name,"
        "phone            = :phone,"
        "how_many         = :how_many,"
        "position         = :position,"
        "order_status     = :order_status";
    sql += " WHERE id = :id";  // 添加 WHERE 子句

    // 创建 SQL 查询并准备执行
    QSqlQuery query;
    query.prepare(sql);

    // 绑定查询参数
    query.bindValue(":id", id);
    query.bindValue(":passenger_name", strs[0]);        // "passenger_name",
    query.bindValue(":phone", strs[1]);                 // "phone",
    query.bindValue(":how_many", strs[2]);              // "how_many",
    query.bindValue(":position", strs[3]);              // "position"
    query.bindValue(":order_status", order_status_id);  // "order_status_id"
    // 执行查询
    if (query.exec()) {
        qDebug() << "User updated successfully!";
    } else {
        qDebug() << "Failed to update user:" << query.lastError();
    }
    logger log_ins;
    QString logMessage = QString("%1 修改了一筆訂單，訂單編號: %2 資料 passenger_name = phone = how_many = position = order_status_id = ")
                             .arg(log_ins.return_username())
                             .arg(id).arg(strs[0]).arg(strs[1]).arg(strs[2]).arg(strs[3]).arg(order_status_id);
    log_ins.save_logger(logMessage);
    qDebug() << "Executing update query for User ID:" << id;
}
