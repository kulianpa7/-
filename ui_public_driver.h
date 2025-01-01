/********************************************************************************
** Form generated from reading UI file 'public_driver.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUBLIC_DRIVER_H
#define UI_PUBLIC_DRIVER_H

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

class Ui_public_driver
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *refresh_button_2;
    QPushButton *add_button_2;
    QSpacerItem *horizontalSpacer_4;
    QTableWidget *tableWidget_2;

    void setupUi(QWidget *public_driver)
    {
        if (public_driver->objectName().isEmpty())
            public_driver->setObjectName("public_driver");
        public_driver->resize(598, 474);
        public_driver->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        gridLayout = new QGridLayout(public_driver);
        gridLayout->setObjectName("gridLayout");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        refresh_button_2 = new QPushButton(public_driver);
        refresh_button_2->setObjectName("refresh_button_2");
        refresh_button_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_5->addWidget(refresh_button_2);

        add_button_2 = new QPushButton(public_driver);
        add_button_2->setObjectName("add_button_2");

        horizontalLayout_5->addWidget(add_button_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        horizontalLayout_2->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

        tableWidget_2 = new QTableWidget(public_driver);
        tableWidget_2->setObjectName("tableWidget_2");

        gridLayout_2->addWidget(tableWidget_2, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(public_driver);

        QMetaObject::connectSlotsByName(public_driver);
    } // setupUi

    void retranslateUi(QWidget *public_driver)
    {
        public_driver->setWindowTitle(QCoreApplication::translate("public_driver", "\345\217\270\346\251\237\350\250\255\345\256\232", nullptr));
        refresh_button_2->setText(QCoreApplication::translate("public_driver", "\351\207\215\346\226\260\346\225\264\347\220\206", nullptr));
        add_button_2->setText(QCoreApplication::translate("public_driver", "\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class public_driver: public Ui_public_driver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUBLIC_DRIVER_H
