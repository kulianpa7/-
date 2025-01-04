// logger.cpp

#include "logger.h"
#include <QFile>
#include <QSqlError>
#include <QFileDialog>
#include <QMessageBox>
// 初始化靜態成員
QString logger::username = "";

// logger 類的構造函數
logger::logger() {}

void logger::save_logger(QString description) {
    QSqlQuery query;
    query.prepare(R"(
            INSERT INTO logger (description)
            VALUES (:description)
        )");
    query.bindValue(":description", description);
    query.exec();  // 確保執行
}
void logger::print_logger_toCSV() {
    // 讓用戶選擇保存路徑
    QString filePath = QFileDialog::getSaveFileName(
        nullptr,
        "保存日誌為 CSV 文件",
        QDir::homePath() + "/logger_export.csv",
        "CSV Files (*.csv);;All Files (*)"
        );

    if (filePath.isEmpty()) {
        qDebug() << "用戶取消了保存操作。";
        return;
    }

    // 打開資料庫
    QSqlQuery query;
    query.prepare(R"(
        SELECT id, description, time_create
        FROM logger
    )");

    if (!query.exec()) {
        qWarning() << "Failed to retrieve logger data:" << query.lastError().text();
        return;
    }

    // 準備 CSV 文件
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Unable to open file for writing:" << file.errorString();
        return;
    }

    QTextStream out(&file);

    // 寫入 CSV 標題
    out << "ID,Description,Time Created\n";

    // 寫入每一行記錄
    while (query.next()) {
        int id = query.value(0).toInt();
        QString description = query.value(1).toString();
        QString timeCreate = query.value(2).toString();

        // 確保每個值用引號包裹，避免特殊字符造成格式錯誤
        out << "\"" << id << "\","
            << "\"" << description.replace("\"", "\"\"") << "\","
            << "\"" << timeCreate << "\"\n";
    }
    file.close();

    // 成功提示
    QMessageBox::information(nullptr, "輸出成功", "紀錄以輸出到:\n" + filePath);
}

void logger::save_username(QString usernames) {
    username = usernames;  // 設置靜態變數 username
}
QString logger::return_username(){
    return username;
}
