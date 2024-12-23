#ifndef PUBLIC_MENU_H
#define PUBLIC_MENU_H

#include <QWidget>
#include <BasePage.h>
#include <QPushButton>
#include <QResizeEvent>
#include <QVector>
#include <QPointer> // 引入 QPointer

namespace Ui {
class public_menu;
}

class public_menu : public QWidget
{
    Q_OBJECT

public:
    explicit public_menu(QWidget *parent = nullptr);
    ~public_menu();
private slots:
    void resizeEvent(QResizeEvent *event) override;
    void on_buttons_click(const QString& buttonType);
    ButtonType stringToButtonType(const QString& buttonType);
private:
    std::unordered_map<int, bool> isOpens = {
        {Role, false},
        {User, false},
        {Driver,false},
        {Vehicle,false},
    };
    std::unordered_map<int, QPointer<BasePage>> Pages = {
        {Role, nullptr},  // 初始化為 nullptr
        {User, nullptr},
        {Driver,nullptr},
        {Vehicle,nullptr},
    };
    Ui::public_menu *ui;
    // 創建一個QVector存儲所有需要調整字體的按鈕
    QVector<QPushButton*> buttons;
    // QPointer<public_role> rolePage;  // 使用 QPointer 管理角色頁面指標
    // bool isRolePageOpen = false; // 用來控制角色頁面是否已經開啟
    // QPointer<public_user> userPage;  // 使用 QPointer 管理角色頁面指標
    // bool isUserPageOpen = false; // 用來控制用戶頁面是否已經開啟

};

#endif // PUBLIC_MENU_H
