// logger.h
#ifndef LOGGER_H
#define LOGGER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

class logger
{
public:
    logger();

    static QString username;  // 靜態變數

    // 保存日志
    void save_logger(QString description);
    // 保存用戶名
    static void save_username(QString usernames);  // 靜態方法
    static QString return_username();
    void print_logger_toCSV();
};

#endif // LOGGER_H
