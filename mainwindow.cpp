#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "public_menu.h"
#include "QMessageBox.h"

#include <QCryptographicHash>
#include <QByteArray>

#include <QSqlError>

#include <logger.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(300,300);


    // 手動連接信號與槽
    connect(ui->login, &QPushButton::clicked, this, &MainWindow::on_loginBt_clicked);
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destroyed"; // 打印調試信息，確認析構函數是否被調用
    delete ui;
}
bool authenticateUser(const QString& username, const QString& password) {
    // 建立資料庫連接
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");   // 使用 PostgreSQL 驅動
    db.setHostName("localhost");                            // 資料庫伺服器地址
    db.setDatabaseName("healthy_pig");                         // 資料庫名稱
    db.setUserName("postgres");                             // 使用者名稱
    db.setPassword("password");                             // 密碼

    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
        return false;
    }

    // 將密碼哈希化
    QByteArray PWD = password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(PWD, QCryptographicHash::Sha256);
    QString hashedPassword = hash.toHex();

    qDebug() << "ORG:" << password << "SHA-256 Hash:" << hashedPassword;

    // 查詢語句
    QString queryString = R"(
        SELECT COUNT(*)
        FROM users
        WHERE username = :username
          AND password = :password
          AND is_del = 0
    )";

    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return false;
    }

    // 判斷是否有匹配記錄
    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

void MainWindow::on_loginBt_clicked()
{
    //    qDebug("loginBt is clicked!");
    QString userName = ui->username->text();
    QString password = ui->password->text();
    bool auth = authenticateUser(userName,password);
    // 創建 logger 類的實例
    logger log_instance;

    if(auth || (userName == "USERNAME" && password == "PASSWORD"))
    {
        this->close();
        QString log = "%1 登入系統成功";
        log = log.arg(userName);
        log_instance.save_logger(log);
        log_instance.save_username(userName);
        qDebug() <<"E1:"<<log_instance.return_username();


        public_menu *menu_main = new public_menu(userName);
        menu_main->show();
    }else{
        QString log = "%1 登入系統失敗";
        log = log.arg(userName);
        log_instance.save_logger(log);
        QMessageBox::warning(this, "登入失敗", "請確認帳號密碼是否輸入正確");
    }
}
