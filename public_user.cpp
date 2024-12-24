#include "public_user.h"
#include "ui_public_user.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


#include <Qstring>
#include <QCryptographicHash>
#include <QByteArray>
#include <QMessageBox>
#include <QComboBox>
#include <BasePage.h>
#include <QDebug>
public_user::public_user(BasePage *parent)
    : BasePage(parent)
    , ui(new Ui::public_user)
{
    ui->setupUi(this);
    connect(ui->refresh_button_2, &QPushButton::clicked, this, &public_user::loadDataFromDatabase);
    connect(ui->add_button_2, &QPushButton::clicked, this, &public_user::addrow);

    ui->tableWidget_2->setColumnCount(5);  // 5 列
    // 設置表格標題
    ui->tableWidget_2->setHorizontalHeaderLabels({
        "使用者名稱", "角色", "帳號", "修改密碼","刪除按鈕"
    });
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    connect(ui->tableWidget_2, &QTableWidget::cellChanged, this, &public_user::onCellChanged);
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

public_user::~public_user()
{
    delete ui;
}
void public_user::closeEvent(QCloseEvent *event)
{
    // 當窗口被關閉時，使用 deleteLater() 推遲銷毀
    this->deleteLater();  // 確保在事件循環後銷毀視窗

    // 可以添加額外的處理邏輯（例如發送信號等）
    QWidget::closeEvent(event);  // 呼叫基類的 closeEvent，執行正常的關閉操作
}

void public_user::loadDataFromDatabase()
{
    disconnect(ui->tableWidget_2, &QTableWidget::cellChanged, this, &public_user::onCellChanged);

    // 执行数据库查询，选取所有角色数据
    QSqlQuery query(
        "SELECT "
        "    u.users, "
        "    r.name, "  // 假设 roles 表有 name 这个字段
        "    u.username, "
        "    u.id, "
        "    u.role_id "
        "FROM "
        "    users u "
        "JOIN "
        "    roles r ON u.role_id = r.id "
        "WHERE "
        "    u.is_del = 0 "
        "ORDER BY "
        "    u.id DESC;"
        );

    // 清除表格中的现有行
    ui->tableWidget_2->setRowCount(0);

    // 查询角色数据并缓存，以便以后使用
    QSqlQuery roleQuery("SELECT id, name FROM roles");
    QMap<int, QString> rolesMap;
    while (roleQuery.next()) {
        int roleId = roleQuery.value("id").toInt();
        QString roleName = roleQuery.value("name").toString();
        rolesMap.insert(roleId, roleName);
    }

    int row = 0;  // 用于记录当前插入的行索引

    // 遍历查询结果并填充表格
    while (query.next()) {
        // 在 TableWidget 插入一行
        ui->tableWidget_2->insertRow(row);

        // 遍历数据库列并将值填入每个单元格
        for (int col = 0; col < ui->tableWidget_2->columnCount() - 2; ++col) {
            if(col ==1)continue;
            QString cellText = query.value(col).toString();
            qDebug() <<"CCCCCCCCCCCCT = "<<cellText;
            QTableWidgetItem *item = new QTableWidgetItem(cellText);
            item->setTextAlignment(Qt::AlignCenter);

            // 如果需要，可以附加隐藏数据，例如 ID（仅对第一列进行此操作）
            if (col == 0) {
                item->setData(Qt::UserRole, query.value("id"));
            }
            // 将表格项目添加到表格中
            ui->tableWidget_2->setItem(row, col, item);
        }

        // 创建下拉框 (QComboBox) 并填充角色名称
        QComboBox *comboBox = new QComboBox();
        // 将角色列表添加到下拉框
        for (auto it = rolesMap.begin(); it != rolesMap.end(); ++it) {
            comboBox->addItem(it.value(), it.key());  // 角色名作为显示值，id作为隐藏数据
        }

        // 设置下拉框默认选中的值为当前用户的角色
        int currentRoleId = query.value("role_id").toInt();
        int index = comboBox->findData(currentRoleId);
        if (index >= 0) {
            comboBox->setCurrentIndex(index);
        }

        // 将下拉框放入第二列
        ui->tableWidget_2->setCellWidget(row, 1, comboBox);
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
        ui->tableWidget_2->setCellWidget(row, ui->tableWidget_2->columnCount() - 1, deleteButton);
        qDebug() << row << " ------------------------------------ \n";
        row++;  // 增加行索引
    }

    // 设置列和行的自动调整大小
    ui->tableWidget_2->resizeColumnsToContents();
    ui->tableWidget_2->resizeRowsToContents();

    // 计算某一行的宽度
    int rowWidth = 0;
    int rowIndex = 0;  // 假设要计算第 0 行的宽度
    for (int col = 0; col < ui->tableWidget_2->columnCount(); ++col) {
        rowWidth += ui->tableWidget_2->columnWidth(col);  // 获取该列的宽度
    }

    // 增加额外的 20 宽度来调整窗口
    int currentWidth = this->width();  // 获取当前窗口宽度
    this->resize(rowWidth + 45, this->height());  // 设置新宽度并保持高度不


    connect(ui->tableWidget_2, &QTableWidget::cellChanged, this, &public_user::onCellChanged);
}

void public_user::onCellChanged(int row) {
    int id = ui->tableWidget_2->item(row, 0)->data(Qt::UserRole).toInt();
    // 檢查行號是否有效
    if (row < 0 || row >= ui->tableWidget_2->rowCount()) {
        qDebug() << "Invalid row number:" << row;
        return;
    }

    qDebug() << "Row changed:" << row;

    // 遍歷該行的所有列，輸出狀態
    for (int col = 0; col < ui->tableWidget_2->columnCount(); ++col) {
        QWidget *widget = ui->tableWidget_2->cellWidget(row, col);

        if (widget && qobject_cast<QComboBox *>(widget)) {
            // 檢查是否是 QComboBox
            QComboBox *comboBox = qobject_cast<QComboBox *>(widget);
            int selectedRoleId = comboBox->currentData().toInt();
            qDebug() << "Column" << col << ": QComboBox selected Role ID:" << selectedRoleId;
        } else if (ui->tableWidget_2->item(row, col)) {
            // 如果是普通的 QTableWidgetItem，直接輸出文本和隱藏數據
            QTableWidgetItem *item = ui->tableWidget_2->item(row, col);
            qDebug() << "Column" << col
                     << ": Text:" << item->text()
                     << ": data:" << item->data(Qt::UserRole).toString();
        } else {
            qDebug() << "Column" << col << ": Empty";
        }
    }

    // 從第一列取得資料庫中記錄的 ID
    if (ui->tableWidget_2->item(row, 0)) {
        int id = ui->tableWidget_2->item(row, 0)->data(Qt::UserRole).toInt();
        // 保存數據到資料庫
        saveDataToDatabase(row, id);
        loadDataFromDatabase();  // 重新加載數據，更新顯示
    } else {
        qDebug() << "Row" << row << "does not have a valid ID in column 0.";
    }
}
void public_user::updateUserRole(int userId, int roleId) {
    QSqlQuery query;
    query.prepare("UPDATE users SET role_id = :role_id WHERE id = :id");
    query.bindValue(":role_id", roleId);
    query.bindValue(":id", userId);

    if (!query.exec()) {
        qDebug() << "Error updating user role:" << query.lastError().text();
    } else {
        qDebug() << "User role updated successfully for User ID:" << userId;
    }
}
void public_user::deleteRow(int id) {
    // 使用 sender() 獲取信號的發送者
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) {
        qDebug() << "Error: Sender is not a QPushButton.";
        return;
    }
    // 獲取按鈕所在的行
    int row = -1;
    for (int i = 0; i < ui->tableWidget_2->rowCount(); ++i) {
        if (ui->tableWidget_2->cellWidget(i, ui->tableWidget_2->columnCount() - 1) == button) {
            row = i;
            break;
        }
    }
    // 檢查行號是否有效
    if (row < 0 || row >= ui->tableWidget_2->rowCount()) {
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
        deleteQuery.prepare("UPDATE users SET is_del = 1 WHERE id = :id");
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
// 儲存特定行資料到資料庫
void public_user::saveDataToDatabase(int row, int id)
{

    if (row < 0 || row >= ui->tableWidget_2->rowCount()) {
        qDebug() << "ERROR: Invalid row:" << row;
        return;
    }

    int currentUserId = 0; // 初始化当前用户 ID
    // 检查第 0 列的 QTableWidgetItem 是否存在
    if (ui->tableWidget_2->item(row, 0) != nullptr) {
        QVariant idData = ui->tableWidget_2->item(row, 0)->data(Qt::UserRole);
        if (idData.isValid()) {
            currentUserId = idData.toInt();
        } else {
            qDebug() << "Error: ID data not found in Qt::UserRole.";
        }
    }
    // 取得該行的用戶名，並檢查是否為空
    QString users = "";
    if (ui->tableWidget_2->item(row, 0) != nullptr) {
        users = ui->tableWidget_2->item(row, 0)->text();
    }
    // 取得該行的用戶名，並檢查是否為空

    QString username = "";
    if (ui->tableWidget_2->item(row, 2) != nullptr) {
        username = ui->tableWidget_2->item(row, 2)->text();
    }
    // Query the database to check for duplicate usernames
    QSqlQuery roleQuery;
    roleQuery.prepare("SELECT COUNT(*) FROM users WHERE username = :username AND is_del = 0 AND id != :id");
    roleQuery.bindValue(":username", username);
    roleQuery.bindValue(":id",currentUserId);

    if (roleQuery.exec() && roleQuery.next()) {
        int count = roleQuery.value(0).toInt();
        if (count > 0) {
            QMessageBox::warning(this, "警告", "帳號不能重複！");
            loadDataFromDatabase();
            return;
        }
    } else {
        QMessageBox::critical(this, "錯誤", "無法檢查帳號是否重複：" + roleQuery.lastError().text());
        return;
    }


    // 取得該行的密碼，並檢查是否為空
    QString password = "";
    if (ui->tableWidget_2->item(row, 3) != nullptr) {
        password = ui->tableWidget_2->item(row, 3)->text();
    }
    // 取得角色名稱（從 QComboBox 中選擇的角色 ID）
    QComboBox *roleComboBox = qobject_cast<QComboBox *>(ui->tableWidget_2->cellWidget(row, 1));
    int selectedRoleId = roleComboBox ? roleComboBox->currentData().toInt() : -1; // 获取选中的角色 ID

    // 检查选中的角色是否有效
    if (selectedRoleId == -1) {
        qDebug() << "Invalid Role ID at row:" << row;
        return;
    }

    // 如果有其他需要保存的字段，可以按类似方式获取

    // 例如：获取用户名和角色状态
    qDebug() << "LOGGGG: User ID:" << id << "Username:" << username << "Role ID:" << selectedRoleId;

    // 先初始化 SQL 查询
    QString sql = "UPDATE users SET "
                  "users = :users,"
                  "username = :username, "
                  "role_id = :role_id";

    // 如果有密码，则在 SQL 查询中添加密码字段
    if (!password.isEmpty()) {
        sql += ", password = :password";
    }

    sql += " WHERE id = :id";  // 添加 WHERE 子句

    // 创建 SQL 查询并准备执行
    QSqlQuery query;
    query.prepare(sql);

    // 对密码进行哈希处理
    QByteArray PWD = password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(PWD, QCryptographicHash::Sha256);
    QString hashedPassword = hash.toHex();

    // 绑定查询参数
    query.bindValue(":id", id);
    query.bindValue(":username", username);
    query.bindValue(":role_id", selectedRoleId);
    query.bindValue(":users", users);

    // 如果有密码，则绑定密码字段
    if (!password.isEmpty()) {
        query.bindValue(":password", hashedPassword);
    }

    // 执行查询
    if (query.exec()) {
        qDebug() << "User updated successfully!";
    } else {
        qDebug() << "Failed to update user:" << query.lastError();
    }

    qDebug() << "Executing update query for User ID:" << id;
}

#include <QLabel>
#include <QLineEdit>
// addrow 函式實現
void public_user::addrow() {
    // 創建對話框
    QDialog dialog(this);
    dialog.setWindowTitle("新增人員");

    // 創建控件
    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    QHBoxLayout *label_text = new QHBoxLayout(&dialog);
    // 名稱輸入框
    QLabel *nameLabel = new QLabel("名稱:", &dialog);
    QLineEdit *nameEdit = new QLineEdit(&dialog);
    QLabel *usernameLabel = new QLabel("帳號:", &dialog);
    QLineEdit *usernameEdit = new QLineEdit(&dialog);
    QLabel *passwordLabel = new QLabel("密碼:", &dialog);
    QLineEdit *passwordEdit = new QLineEdit(&dialog);
    // 設置垂直布局
    label_text->addWidget(nameLabel);
    label_text->addWidget(nameEdit);
        mainLayout->addLayout(label_text);
        label_text = new QHBoxLayout(&dialog);
    label_text->addWidget(usernameLabel);
    label_text->addWidget(usernameEdit);
        mainLayout->addLayout(label_text);
        label_text = new QHBoxLayout(&dialog);
    label_text->addWidget(passwordLabel);
    label_text->addWidget(passwordEdit);
        mainLayout->addLayout(label_text);

    // 角色選擇框
    label_text = new QHBoxLayout(&dialog);
    QLabel *roleLabel = new QLabel("角色:", &dialog);
    QComboBox *roleComboBox = new QComboBox(&dialog);

    // 從資料庫加載角色選項
    QSqlQuery roleQuery("SELECT id, name FROM roles");
    while (roleQuery.next()) {
        int roleId = roleQuery.value("id").toInt();
        QString roleName = roleQuery.value("name").toString();
        roleComboBox->addItem(roleName, roleId); // 添加角色名稱，並將角色 ID 設為隱藏值
    }

    label_text->addWidget(roleLabel);
    label_text->addWidget(roleComboBox);
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
        QString username = usernameEdit->text();
        QString password = passwordEdit->text();

        // 对密码进行哈希处理
        QByteArray PWD = password.toUtf8();
        QByteArray hash = QCryptographicHash::hash(PWD, QCryptographicHash::Sha256);
        QString hashedPassword = hash.toHex();

        int selectedRoleId = roleComboBox->currentData().toInt();

        if (!name.isEmpty() && !username.isEmpty() && !password.isEmpty()) {
            // 首先檢查資料庫中是否已存在相同的用戶名
            QSqlQuery checkQuery;
            checkQuery.prepare("SELECT COUNT(*) FROM users WHERE username = :username AND is_del = 0");
            checkQuery.bindValue(":username", username);

            if (checkQuery.exec() && checkQuery.next()) {
                int count = checkQuery.value(0).toInt();
                if (count > 0) {
                    QMessageBox::warning(this, "警告", "該帳號已存在，請使用其他帳號！");
                    return; // 中止插入操作
                }
            } else {
                qDebug() << "檢查用戶名失敗：" << checkQuery.lastError().text();
                QMessageBox::critical(this, "錯誤", "無法檢查帳號是否已存在！");
                return;
            }

            // 開始插入資料到資料庫
            QSqlQuery query;
            // 使用 SQL 插入語句
            query.prepare("INSERT INTO users (users, role_id, username, password) "
                          "VALUES (:users, :role_id, :username, :password)");
            // 設定綁定參數
            query.bindValue(":users", name);
            query.bindValue(":username", username);
            query.bindValue(":password", hashedPassword);
            query.bindValue(":role_id", selectedRoleId);

            // 執行查詢並檢查是否成功
            if (query.exec()) {
                qDebug() << "新增人員成功，名稱：" << name;

                // 重新加載資料庫資料並更新 UI
                loadDataFromDatabase();
            } else {
                qDebug() << "新增人員失敗：" << query.lastError().text();
                QMessageBox::warning(this, "錯誤", "無法新增人員至資料庫！");
            }
        } else {
            // 如果名稱、帳號或密碼為空，顯示錯誤提示
            QMessageBox::warning(this, "警告", "名稱或帳號密碼不能為空！");
        }
    }
}
