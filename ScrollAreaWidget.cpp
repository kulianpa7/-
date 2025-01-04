#include "ScrollAreaWidget.h"
#include <QFile>
#include <QLabel>
#include <QDate>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <remoteint.h>

ScrollAreaWidget::ScrollAreaWidget(QWidget *parent)
    : QWidget(parent)
{
    scrollArea = new QScrollArea(this);
    mainLayout = new QVBoxLayout(this);

    QWidget *containerWidget = new QWidget(this);

    scrollArea->setWidget(containerWidget);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}

ScrollAreaWidget::~ScrollAreaWidget() {}

void ScrollAreaWidget::clear()
{
    QWidget *widget = scrollArea->widget();
    if (widget) {
        QLayout *layout = widget->layout();
        if (layout) {
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != nullptr) {
                if (item->widget()) {
                    delete item->widget();
                }
                delete item;
            }
            delete layout;
        }
    }

    QWidget *newContainerWidget = new QWidget(this);
    scrollArea->setWidget(newContainerWidget);
    QVBoxLayout *newLayout = new QVBoxLayout(newContainerWidget);
    newContainerWidget->setLayout(newLayout);
}

void ScrollAreaWidget::updateContent(int pageType)
{
    clear();
    QWidget *containerWidget = scrollArea->widget();
    QVBoxLayout *containerLayout = qobject_cast<QVBoxLayout *>(containerWidget->layout());
    loadOrdersFromDatabase(containerLayout, pageType);
}

void ScrollAreaWidget::loadOrdersFromDatabase(QVBoxLayout *containerLayout, int pageType)
{
    QSqlQuery query;
    QString queryString;

    if (pageType == 0) {
        queryString = R"(
            SELECT id, date_time, position, passenger_name, phone, order_status
            FROM orders
            WHERE driver_id = :driver_id
              AND order_status IN (-1, 0)
              AND DATE(date_time) = :date
            ORDER BY order_status DESC, date_time ASC;
        )";
    } else {
        queryString = R"(
            SELECT id, date_time, position, passenger_name, phone, order_status
            FROM orders
            WHERE driver_id = :driver_id
            AND order_status IN (1, 2)
            AND DATE(date_time) = :date
            ORDER BY date_time DESC
        )";
    }
    remoteint remoteid;
    query.prepare(queryString);
    query.bindValue(":driver_id", remoteid.return_id());
    qDebug() << "saw id：" << remoteid.return_id();
    query.bindValue(":date", QDate::currentDate().toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "SQL Query Failed: " << query.lastQuery();
        qDebug() << "Error: " << query.lastError().text();
        return;
    }

    bool hasOrders = false;
    while (query.next()) {
        hasOrders = true;
        int orderId = query.value("id").toInt();
        QString dateTime = query.value("date_time").toString();
        qDebug() << dateTime;
        QDateTime date = QDateTime::fromString(dateTime, "yyyy-MM-ddTHH:mm:ss.zzzZ"); // 解析 ISO 8601 格式
        QString formattedDate = date.toString("yyyy年MM月dd日 HH:mm:ss");  // 中文格式：yyyy年MM月dd日 HH:mm:ss
        QString position = query.value("position").toString();
        QString passengerName = query.value("passenger_name").toString();
        QString phone = query.value("phone").toString();
        int orderStatus = query.value("order_status").toInt();

        QVBoxLayout *labelLayout = new QVBoxLayout;
        QLabel *label1 = new QLabel("時間: " + formattedDate, this);
        QLabel *label2 = new QLabel("地址: " + position, this);
        QLabel *label3 = new QLabel("名字: " + passengerName, this);
        QLabel *label4 = new QLabel("電話: " + phone, this);

        labelLayout->addWidget(label1);
        labelLayout->addWidget(label2);
        labelLayout->addWidget(label3);
        labelLayout->addWidget(label4);

        QHBoxLayout *buttonLayout = new QHBoxLayout;
        if (pageType == 0) {
            QPushButton *startButton = new QPushButton("開始", this);
            if (orderStatus == -1) {
                startButton->setText("開始");
                startButton->setObjectName("todaystart");
                connect(startButton, &QPushButton::clicked, [this, orderId]() {
                    updateOrderStatus(orderId, 0);
                });
            } else if (orderStatus == 0) {
                startButton->setText("開始中");
                startButton->setObjectName("todaystarting");
            }

            QPushButton *endButton = new QPushButton("結束", this);
            endButton->setObjectName("todayend");
            connect(endButton, &QPushButton::clicked, [this, orderId]() {
                updateOrderStatus(orderId, 1);
            });

            QPushButton *discardButton = new QPushButton("丟棄", this);
            discardButton->setObjectName("todaydiscard");
            connect(discardButton, &QPushButton::clicked, [this, orderId]() {
                updateOrderStatus(orderId, 2);
            });

            buttonLayout->addWidget(startButton);
            buttonLayout->addWidget(endButton);
            buttonLayout->addWidget(discardButton);
        } else {
            QPushButton *statusButton = new QPushButton(this);
            if (orderStatus == 1) {
                statusButton->setText("已結束");
                statusButton->setObjectName("historyend");
            } else if (orderStatus == 2) {
                statusButton->setText("已丟棄");
                statusButton->setObjectName("historydiscard");
            }

            buttonLayout->addWidget(statusButton);
        }

        QHBoxLayout *itemLayout = new QHBoxLayout;
        itemLayout->addLayout(labelLayout);
        itemLayout->addLayout(buttonLayout);

        containerLayout->addLayout(itemLayout);

        QFrame *separator = new QFrame(this);
        separator->setFrameShape(QFrame::HLine);
        separator->setFrameShadow(QFrame::Sunken);
        containerLayout->addWidget(separator);
    }
    if (!hasOrders) {
        QLabel *noOrdersLabel = new QLabel("目前沒有訂單", this);
        noOrdersLabel->setAlignment(Qt::AlignCenter);
        containerLayout->addWidget(noOrdersLabel);
    }
}

void ScrollAreaWidget::updateOrderStatus(int orderId, int status)
{
    QSqlQuery query;
    query.prepare("UPDATE orders SET order_status = :status WHERE id = :orderId");
    query.bindValue(":status", status);
    query.bindValue(":orderId", orderId);

    if (query.exec()) {
        qDebug() << "Order status updated successfully!";
        updateContent(0);  // 重新加載頁面內容
    } else {
        qDebug() << "Failed to update order status:" << query.lastError();
    }
}
