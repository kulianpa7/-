/********************************************************************************
** Form generated from reading UI file 'public_vehicle.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUBLIC_VEHICLE_H
#define UI_PUBLIC_VEHICLE_H

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

class Ui_public_velicle
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *refresh_button_3;
    QPushButton *add_button_3;
    QSpacerItem *horizontalSpacer_6;
    QTableWidget *tableWidget_3;

    void setupUi(QWidget *public_velicle)
    {
        if (public_velicle->objectName().isEmpty())
            public_velicle->setObjectName("public_velicle");
        public_velicle->resize(583, 464);
        public_velicle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        gridLayout = new QGridLayout(public_velicle);
        gridLayout->setObjectName("gridLayout");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        refresh_button_3 = new QPushButton(public_velicle);
        refresh_button_3->setObjectName("refresh_button_3");
        refresh_button_3->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_6->addWidget(refresh_button_3);

        add_button_3 = new QPushButton(public_velicle);
        add_button_3->setObjectName("add_button_3");

        horizontalLayout_6->addWidget(add_button_3);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        horizontalLayout_3->addLayout(horizontalLayout_6);


        verticalLayout_3->addLayout(horizontalLayout_3);


        gridLayout_3->addLayout(verticalLayout_3, 0, 0, 1, 1);

        tableWidget_3 = new QTableWidget(public_velicle);
        tableWidget_3->setObjectName("tableWidget_3");

        gridLayout_3->addWidget(tableWidget_3, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 0, 0, 1, 1);


        retranslateUi(public_velicle);

        QMetaObject::connectSlotsByName(public_velicle);
    } // setupUi

    void retranslateUi(QWidget *public_velicle)
    {
        public_velicle->setWindowTitle(QCoreApplication::translate("public_velicle", "\350\273\212\350\274\233\350\250\255\345\256\232\347\263\273\347\265\261", nullptr));
        refresh_button_3->setText(QCoreApplication::translate("public_velicle", "\351\207\215\346\226\260\346\225\264\347\220\206", nullptr));
        add_button_3->setText(QCoreApplication::translate("public_velicle", "\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class public_velicle: public Ui_public_velicle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUBLIC_VEHICLE_H
