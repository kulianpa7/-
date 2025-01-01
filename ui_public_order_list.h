/********************************************************************************
** Form generated from reading UI file 'public_order_list.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUBLIC_ORDER_LIST_H
#define UI_PUBLIC_ORDER_LIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_public_order_list
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *refresh_button;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *tableWidget;

    void setupUi(QWidget *public_order_list)
    {
        if (public_order_list->objectName().isEmpty())
            public_order_list->setObjectName("public_order_list");
        public_order_list->resize(544, 427);
        public_order_list->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	font-size:24px;\n"
"    font-family: Arial;\n"
"    color: white;\n"
"    background-color: #007BFF;\n"
"    border-radius: 8px;\n"
"    border: 1px solid #0056b3;\n"
"    /* \350\250\255\345\256\232\346\214\211\351\210\225\347\232\204\346\234\200\345\260\217\345\260\272\345\257\270 */\n"
"    min-width: 100px;\n"
"    min-height: 50px; /* \345\217\257\351\201\270\357\274\214\350\250\255\347\275\256\346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #0056b3;\n"
"}\n"
"1"));
        gridLayout_2 = new QGridLayout(public_order_list);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        refresh_button = new QPushButton(public_order_list);
        refresh_button->setObjectName("refresh_button");
        refresh_button->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(refresh_button);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        horizontalLayout->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        tableWidget = new QTableWidget(public_order_list);
        tableWidget->setObjectName("tableWidget");

        gridLayout->addWidget(tableWidget, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(public_order_list);

        QMetaObject::connectSlotsByName(public_order_list);
    } // setupUi

    void retranslateUi(QWidget *public_order_list)
    {
        public_order_list->setWindowTitle(QCoreApplication::translate("public_order_list", "\350\250\202\345\226\256\346\237\245\347\234\213\347\263\273\347\265\261", nullptr));
        refresh_button->setText(QCoreApplication::translate("public_order_list", "\351\207\215\346\226\260\346\225\264\347\220\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class public_order_list: public Ui_public_order_list {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUBLIC_ORDER_LIST_H
