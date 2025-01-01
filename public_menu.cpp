#include "public_menu.h"
#include "ui_public_menu.h"

#include "public_role.h"
#include "public_user.h"
#include "public_vehicle.h"
#include "public_driver.h"
#include "public_order_list.h"
#include "public_driver_arrange.h"
#include "public_order_arrange.h"

#include <QPushButton>
#include <QResizeEvent>
#include <BasePage.h>
#include <QSqlError>
#include <QMessageBox>

#include <logger.h>

public_menu::public_menu(const QString &userName,QWidget *parent)
    : QWidget(parent)
    , m_userName(userName)// Initialize m_userName with userName
    , ui(new Ui::public_menu)
{
    ui->setupUi(this);
    // 將所有按鈕添加到 QVector 中
    buttons.append(ui->user_button);  // 假設有 pushButton_1, pushButton_2, ..., pushButton_6
    buttons.append(ui->role_button);
    buttons.append(ui->driver_car_button);
    buttons.append(ui->driver_scheduling_button);
    buttons.append(ui->order_arrange_button);
    buttons.append(ui->order_list_button);
    logger log_instance;
    qDebug() <<"E2:"<<log_instance.return_username();
    // 手動連接信號與槽
    connect(ui->role_button, &QPushButton::clicked, this, [this]() {on_buttons_click("role");});
    connect(ui->user_button, &QPushButton::clicked, this, [this]() {on_buttons_click("user");});
    connect(ui->driver_car_button, &QPushButton::clicked, this, [this]() {on_buttons_click("velicle");});
    connect(ui->driver_car_button, &QPushButton::clicked, this, [this]() {on_buttons_click("driver");});
    connect(ui->order_list_button, &QPushButton::clicked, this, [this]() {on_buttons_click("order_list");});
    connect(ui->driver_scheduling_button, &QPushButton::clicked, this, [this]() {on_buttons_click("driver_arrange");});
    connect(ui->order_arrange_button, &QPushButton::clicked, this, [this]() {on_buttons_click("order_arrangement");});
    // connect(ui->user_button, &QPushButton::clicked, this, &public_menu::on_user_click);
}

public_menu::~public_menu()
{
    qDebug() << "public_menu destroyed"; // 打印調試信息，確認析構函數是否被調用
    delete ui;
}

// ButtonType at BasePage.h
ButtonType public_menu::stringToButtonType(const QString& buttonType) {
    if (buttonType == "role") return Role;
    if (buttonType == "user") return User;
    if (buttonType == "driver") return Driver;
    if (buttonType == "velicle") return Vehicle;
    if (buttonType == "order_list") return Order_list;
    if (buttonType == "driver_arrange") return Driver_Arrange;
    if (buttonType == "order_arrangement") return Order_arrange;
    return Unknown;
}
void public_menu::on_buttons_click(const QString& buttonType) {
    int type = stringToButtonType(buttonType);

    // 檢查頁面是否已經開啟
    if (isOpens[type]) {
        return; // 如果已經開啟，直接返回
    }
    QSqlQuery query1;
    query1.prepare("SELECT id FROM users WHERE username = :username AND is_del = 0");
    query1.bindValue(":username", m_userName);
    int id=0;
    // Execute the query
    if (query1.exec()) {
        // Check if there is a result
        if (query1.next()) {
            id= query1.value("id").toInt();
            qDebug() << "ID:" << id << "Username:" << m_userName;
        } else {
            qDebug() << "No matching user found for username:" << m_userName;
        }
    } else {
        qDebug() << "Query execution failed:" << query1.lastError().text();
    }
    QSqlQuery query;
    query.prepare(
        "SELECT roles.* "
        "FROM users "
        "LEFT JOIN roles ON users.role_id = roles.id "
        "WHERE users.id = :id"
        );
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return;
    }

    // Map types to database fields
    QMap<int, QString> typeToField = {
        {Role, "role"},
        {User, "backend_staff"},
        {Driver, "driver"},
        {Vehicle, "driver"},
        {Driver_Arrange, "driver_schedule"},
        {Order_arrange, "order_arrangement"},
        {Order_list, "order_list"}
    };
    // // Check conditions in a loop
    if (query.next()) {  // Move to the first record
        if (typeToField.contains(type)) {
            QString field = typeToField[type];
            if (!query.value(field).toBool()) {
                if(type != Vehicle)
                    QMessageBox::critical(this, "Database Error", "您沒有訪問權限");
                qDebug() << "Access denied for type:" << type << ", field:" << field;
                return;
            }
        }
    } else {
        qDebug() << "No records found for user ID:" << id;
    }

    // 如果頁面沒有開啟，創建對應的頁面
    if (Pages[type].isNull()) {
        switch(type){
            case(Role):
                Pages[type] = new public_role();  // 創建角色頁面
                break;
            case(User):
                Pages[type] = new public_user();  // 創建用戶頁面
                break;
            case(Driver):
                Pages[type] = new public_driver();  // 創建司機頁面
                break;
            case(Vehicle):
                Pages[type] = new public_velicle();  // 創建用戶頁面
                break;
            case(Order_list):
                Pages[type] = new public_order_list();  // 創建用戶頁面
                break;
            case(Driver_Arrange):
                Pages[type] = new public_driver_arrange();  // 創建用戶頁面
                break;
            case(Order_arrange):
                Pages[type] = new order_arrange();  // 創建用戶頁面
                break;
            default:
                return;
        }
        // 顯示頁面
        Pages[type]->show();

        // 設置標誌，表明頁面已經開啟
        isOpens[type] = true;

        // 當頁面關閉時，重置標誌
        connect(Pages[type], &QObject::destroyed, this, [this, type]() {
            isOpens[type] = false;    // 重置開啟狀態
            Pages[type] = nullptr;   // 清空指針
        });
    }
}
// void public_menu::on_role_click() {
//     // 檢查是否已經開啟角色頁面
//     if (isRolePageOpen) {
//         return; // 如果已經開啟，直接返回，防止重複開啟
//     }

//     // 如果角色頁面沒有開啟，創建新的 public_role 頁面
//     if (rolePage.isNull()) {
//         rolePage = new public_role;  // 創建角色頁面物件
//         rolePage->show();  // 顯示角色頁面

//         // 設置標誌，表明角色頁面已經開啟
//         isRolePageOpen = true;

//         // 當角色頁面關閉時，重置標誌
//         connect(rolePage, &public_role::destroyed, this, [this]() {
//             isRolePageOpen = false;  // 重置標誌，讓下一次能再次開啟角色頁面
//             rolePage = nullptr;  // 清空 rolePage 指標
//         });
//     }
// }
// void public_menu::on_user_click() {
//     // 檢查是否已經開啟角色頁面
//     if (isUserPageOpen) {
//         return; // 如果已經開啟，直接返回，防止重複開啟
//     }

//     // 如果角色頁面沒有開啟，創建新的 public_role 頁面
//     if (userPage.isNull()) {
//         userPage = new public_user;  // 創建角色頁面物件
//         userPage->show();  // 顯示角色頁面

//         // 設置標誌，表明角色頁面已經開啟
//         isUserPageOpen = true;

//         // 當角色頁面關閉時，重置標誌
//         connect(userPage, &public_user::destroyed, this, [this]() {
//             isUserPageOpen = false;  // 重置標誌，讓下一次能再次開啟角色頁面
//             userPage = nullptr;  // 清空 rolePage 指標
//         });
//     }
// }





// 重寫 resizeEvent 以便動態調整字體大小
void public_menu::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    // 遍歷所有按鈕，根據每個按鈕的大小調整字體大小
    for (QPushButton* button : buttons) {
        double
            Qwidth  = 6,
            Qheight = 3;
        QFont font = button->font();
        int newFontSize = qMin(button->width() / Qwidth, button->height() / Qheight); // 根據寬高計算字體大小
        font.setPointSize(newFontSize);
        button->setFont(font);
    }
}
