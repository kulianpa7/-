/********************************************************************************
** Form generated from reading UI file 'public_menu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUBLIC_MENU_H
#define UI_PUBLIC_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_public_menu
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *role_button;
    QPushButton *user_button;
    QPushButton *driver_car_button;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *driver_scheduling_button;
    QPushButton *order_arrange_button;
    QPushButton *order_list_button;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *public_menu)
    {
        if (public_menu->objectName().isEmpty())
            public_menu->setObjectName("public_menu");
        public_menu->resize(678, 498);
        public_menu->setMinimumSize(QSize(600, 200));
        public_menu->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-family: Arial;\n"
"    color: white;\n"
"    background-color: #007BFF;\n"
"    border-radius: 8px;\n"
"    border: 1px solid #0056b3;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #0056b3;\n"
"}\n"
""));
        gridLayout_3 = new QGridLayout(public_menu);
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        role_button = new QPushButton(public_menu);
        role_button->setObjectName("role_button");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(role_button->sizePolicy().hasHeightForWidth());
        role_button->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(role_button);

        user_button = new QPushButton(public_menu);
        user_button->setObjectName("user_button");
        sizePolicy.setHeightForWidth(user_button->sizePolicy().hasHeightForWidth());
        user_button->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(user_button);

        driver_car_button = new QPushButton(public_menu);
        driver_car_button->setObjectName("driver_car_button");
        sizePolicy.setHeightForWidth(driver_car_button->sizePolicy().hasHeightForWidth());
        driver_car_button->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(driver_car_button);


        horizontalLayout_2->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        driver_scheduling_button = new QPushButton(public_menu);
        driver_scheduling_button->setObjectName("driver_scheduling_button");
        sizePolicy.setHeightForWidth(driver_scheduling_button->sizePolicy().hasHeightForWidth());
        driver_scheduling_button->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(driver_scheduling_button);

        order_arrange_button = new QPushButton(public_menu);
        order_arrange_button->setObjectName("order_arrange_button");
        sizePolicy.setHeightForWidth(order_arrange_button->sizePolicy().hasHeightForWidth());
        order_arrange_button->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(order_arrange_button);

        order_list_button = new QPushButton(public_menu);
        order_list_button->setObjectName("order_list_button");
        sizePolicy.setHeightForWidth(order_list_button->sizePolicy().hasHeightForWidth());
        order_list_button->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(order_list_button);


        gridLayout_2->addLayout(horizontalLayout_6, 1, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout_2);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout_3->addItem(verticalSpacer_2, 0, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout_3->addItem(verticalSpacer_3, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);


        retranslateUi(public_menu);

        QMetaObject::connectSlotsByName(public_menu);
    } // setupUi

    void retranslateUi(QWidget *public_menu)
    {
        public_menu->setWindowTitle(QCoreApplication::translate("public_menu", "\351\240\220\347\264\204\346\216\222\347\217\255\347\263\273\347\265\261", nullptr));
        role_button->setText(QCoreApplication::translate("public_menu", "\350\247\222\350\211\262", nullptr));
        user_button->setText(QCoreApplication::translate("public_menu", "\345\276\214\345\217\260\344\272\272\345\223\241", nullptr));
        driver_car_button->setText(QCoreApplication::translate("public_menu", "\345\217\270\346\251\237 \350\273\212\350\274\233", nullptr));
        driver_scheduling_button->setText(QCoreApplication::translate("public_menu", "\345\217\270\346\251\237\346\216\222\347\217\255", nullptr));
        order_arrange_button->setText(QCoreApplication::translate("public_menu", "\350\250\202\345\226\256\345\256\211\346\216\222", nullptr));
        order_list_button->setText(QCoreApplication::translate("public_menu", "\350\250\202\345\226\256\345\210\227\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class public_menu: public Ui_public_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUBLIC_MENU_H
