#include "public_role.h"
#include "qlineedit.h"
#include "ui_public_role.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>

#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QString>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

#include <BasePage.h>

std::unordered_map<int,bool> is_first_role;

public_role::public_role(BasePage *parent)
    : BasePage(parent)
    , ui(new Ui::public_role)
{
    ui->setupUi(this);
    // 連接 cellChanged 信號到槽函數
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &public_role::onCellChanged);
    // 連接 cellChanged 信號到槽函數
    connect(ui->refresh_button, &QPushButton::clicked, this, &public_role::loadDataFromDatabase);
    connect(ui->add_button, &QPushButton::clicked, this, &public_role::addrow);
    ui->tableWidget->setColumnCount(8);  // 8 列（角色名稱、角色、後台人員...）

    // 設置表格標題
    ui->tableWidget->setHorizontalHeaderLabels({
        "角色名稱", "角色", "後台人員", "司機與車輛", "司機排班", "訂單安排", "訂單列表","刪除按鈕"
    });
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // 初始化資料庫
    db = QSqlDatabase::addDatabase("QPSQL"); // 使用 PostgreSQL 驅動
    db.setHostName("localhost");            // 資料庫伺服器地址
    db.setDatabaseName("postgres");        // 資料庫名稱
    db.setUserName("postgres");             // 使用者名稱
    db.setPassword("password");             // 密碼

    if (!db.open()) {
        QMessageBox::critical(this, "資料庫錯誤", db.lastError().text());
        return;
    }

    // 從資料庫載入資料
    loadDataFromDatabase();
}
// 儲存特定行資料到資料庫
void public_role::saveDataToDatabase(int row,int id)
{
    if (row < 0 || row >= ui->tableWidget->rowCount()) {qDebug()<<"ERROR:"<< row<< '\n';return;};

    QString name = ui->tableWidget->item(row, 0)->text();
    bool role = qobject_cast<QCheckBox *>(ui->tableWidget->cellWidget(row, 1))->isChecked();
    bool backendStaff = qobject_cast<QCheckBox *>(ui->tableWidget->cellWidget(row, 2))->isChecked();
    bool driver = qobject_cast<QCheckBox *>(ui->tableWidget->cellWidget(row, 3))->isChecked();
    bool driverSchedule = qobject_cast<QCheckBox *>(ui->tableWidget->cellWidget(row, 4))->isChecked();
    bool orderArrangement = qobject_cast<QCheckBox *>(ui->tableWidget->cellWidget(row, 5))->isChecked();
    bool orderList = qobject_cast<QCheckBox *>(ui->tableWidget->cellWidget(row, 6))->isChecked();
    qDebug()<<"LOGGGG:"<< id<<role<<backendStaff<<driver<<driverSchedule<<orderArrangement<<orderList;
    QSqlQuery query;
    query.prepare("UPDATE roles SET "
                  "name = :name, "
                  "role = :role, "
                  "backend_staff = :backendStaff, "
                  "driver = :driver, "
                  "driver_schedule = :driverSchedule, "
                  "order_arrangement = :orderArrangement, "
                  "order_list = :orderList "
                  "WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":role", role);
    query.bindValue(":backendStaff", backendStaff);
    query.bindValue(":driver", driver);
    query.bindValue(":driverSchedule", driverSchedule);
    query.bindValue(":orderArrangement", orderArrangement);
    query.bindValue(":orderList", orderList);
    qDebug() <<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    if (query.exec()) {
        qDebug() << "Row updated successfully!";
    } else {
        qDebug() << "Failed to update row:" << query.lastError();
    }
}

void public_role::loadDataFromDatabase()
{
    //清空 hashmap
    is_first_role.clear();
    // 執行資料庫查詢，選取所有角色資料
    QSqlQuery query("SELECT * FROM roles order by id desc");

    // 清除表格中的現有行
    ui->tableWidget->setRowCount(0);

    int row = 0; // 用於記錄目前插入的行索引
    while (query.next()) {
        // 在 TableWidget 插入一行
        ui->tableWidget->insertRow(row);
        qDebug() << row << " ------------------------------------ \n";
        // 插入文本資料到第一列
        QString name = query.value("name").toString(); // 假設資料表中有 name 欄位
        QTableWidgetItem *item = new QTableWidgetItem(name);
        item->setTextAlignment(Qt::AlignCenter); // 設置文本居中
        item->setData(Qt::UserRole, query.value("id")); // 將資料庫中的 id 附加作為隱藏資料
        ui->tableWidget->setItem(row, 0, item);
        ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        // 為其餘列設置 QCheckBox，假設表中這些欄位為布林值
        for (int col = 1; col < ui->tableWidget->columnCount() - 1; ++col) {
            QCheckBox *checkBox = new QCheckBox();
            checkBox->setStyleSheet("margin-left: 25%; margin-right: 25%;"); // 設置 QCheckBox 居中
            checkBox->setChecked(query.value(col + 1).toBool()); // 根據資料庫值設置是否選中

            // 連接 QCheckBox 的 stateChanged 信號
            connect(checkBox, &QCheckBox::stateChanged, this, [this, row, col]() {
                qDebug() << "Row" << row << ", Column" << col << "state changed!";
                this->onCellChanged(row); // 呼叫行改變槽函式
            });

            ui->tableWidget->setCellWidget(row, col, checkBox);
        }

        // 插入刪除按鈕到最後一列
        QPushButton *deleteButton = new QPushButton("刪除");
        deleteButton->setStyleSheet(
            "font-size: 12px; "
            "height: 30px; "
            "width: 20px; "
            "min-height:30px;"
            "min-width:40px;"
            "max-height:30px;"
            "max-width:40px;"
            "margin-left: 25%;"
            "margin-right: 25%;"
            );
        deleteButton->setProperty("rowId", query.value("id")); // 將資料庫中的 id 附加作為屬性
        // 連接按鈕的點擊信號到 deleteRow 槽函式
        connect(deleteButton, &QPushButton::clicked, this, [this,deleteButton]() {
            int id = deleteButton->property("rowId").toInt(); // 取得隱藏的 id
            this->deleteRow(id);
        });
        qDebug() << row << " ------------------------------------ \n";
        ui->tableWidget->setCellWidget(row, ui->tableWidget->columnCount() - 1, deleteButton);
        row++;
    }
    // 設置列和行的自動調整大小
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

    // 計算某一行的寬度
    int rowWidth = 0;
    int rowIndex = 0;  // 假設要計算第 0 行的寬度
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        rowWidth += ui->tableWidget->columnWidth(col);  // 獲取該列的寬度
    }

    // 增加額外的 20 寬度來調整窗口
    int currentWidth = this->width();  // 獲取當前窗口寬度
    this->resize(rowWidth + 25, this->height());  // 設定新寬度並保持高度不變
}


void public_role::closeEvent(QCloseEvent *event)
{
    // 當窗口被關閉時，使用 deleteLater() 推遲銷毀
    this->deleteLater();  // 確保在事件循環後銷毀視窗

    // 可以添加額外的處理邏輯（例如發送信號等）
    QWidget::closeEvent(event);  // 呼叫基類的 closeEvent，執行正常的關閉操作
}

void public_role::onCellChanged(int row) {
    int id = ui->tableWidget->item(row, 0)->data(Qt::UserRole).toInt();
    if(!is_first_role[id])
        is_first_role[id] = true;
    else
        is_first_role[id] = false;
    // 檢查行號是否有效
    if (row < 0 || row >= ui->tableWidget->rowCount()) {
        qDebug() << "Invalid row number:" << row;
        return;
    }

    qDebug() << "Row changed:" << row;

    // 遍歷該行的所有列，輸出狀態
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        QWidget *widget = ui->tableWidget->cellWidget(row, col);

        if (widget && qobject_cast<QCheckBox *>(widget)) {
            // 檢查是否是 QCheckBox
            QCheckBox *checkBox = qobject_cast<QCheckBox *>(widget);
            qDebug() << "Column" << col << ": QCheckBox state:"
                     << (checkBox->isChecked() ? "Checked" : "Unchecked");
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
        qDebug() << "Database ID:" << id << "state :" << is_first_role[id];
        if (!is_first_role[id]) {
            saveDataToDatabase(row, id);
            loadDataFromDatabase();
        }
    } else {
        qDebug() << "Row" << row << "does not have a valid ID in column 0.";
    }
}
// public_role.cpp
// addrow 函式實現
void public_role::addrow() {
    // 創建對話框
    QDialog dialog(this);
    dialog.setWindowTitle("新增角色");

    // 創建控件
    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    QHBoxLayout *label_text = new QHBoxLayout(&dialog);
    // 名稱輸入框
    QLabel *nameLabel = new QLabel("名稱:", &dialog);
    QLineEdit *nameEdit = new QLineEdit(&dialog);

    // 設置垂直布局
    label_text->addWidget(nameLabel);
    label_text->addWidget(nameEdit);
    mainLayout->addLayout(label_text);
    // 設置對話框按鈕
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    mainLayout->addWidget(buttonBox);

    // 連接按鈕信號
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 顯示對話框
    if (dialog.exec() == QDialog::Accepted) {
        // 獲取名稱
        QString name = nameEdit->text();

        if (!name.isEmpty()) {
            // 開始插入資料到資料庫
            QSqlQuery query;
            // 使用 SQL 插入語句
            query.prepare("INSERT INTO roles (name, role, backend_staff, driver, driver_schedule, order_arrangement, order_list) "
                          "VALUES (:name, false, false, false, false, false, false)");

            // 設定綁定參數
            query.bindValue(":name", name);

            // 執行查詢並檢查是否成功
            if (query.exec()) {
                qDebug() << "新增角色成功，名稱：" << name;

                // 重新加載資料庫資料並更新 UI
                loadDataFromDatabase();
            } else {
                qDebug() << "新增角色失敗：" << query.lastError().text();
                QMessageBox::warning(this, "錯誤", "無法新增角色至資料庫！");
            }
        } else {
            // 如果名稱為空，顯示錯誤提示
            QMessageBox::warning(this, "警告", "名稱不能為空！");
        }
    }
}


void public_role::deleteRow(int id) {
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
        deleteQuery.prepare("DELETE FROM roles WHERE id = :id");
        deleteQuery.bindValue(":id", id);
        if (deleteQuery.exec()) {
            qDebug() << "Row deleted successfully!";
        }
        loadDataFromDatabase();
        qDebug() << "Row" << row << "deleted successfully!";
    } else {
        qDebug() << "Row deletion canceled.";
    }
}

public_role::~public_role()
{
    qDebug("public_role DELETE");
    delete ui;
}
