/********************************************************************************
** Form generated from reading UI file 'role.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROLE_H
#define UI_ROLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_role
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *refresh;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer;
    QTableView *tableView;

    void setupUi(QWidget *role)
    {
        if (role->objectName().isEmpty())
            role->setObjectName("role");
        role->resize(776, 533);
        gridLayout_2 = new QGridLayout(role);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        refresh = new QPushButton(role);
        refresh->setObjectName("refresh");

        horizontalLayout_4->addWidget(refresh);

        pushButton_2 = new QPushButton(role);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_4->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(role);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout_4->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(role);
        pushButton_4->setObjectName("pushButton_4");

        horizontalLayout_4->addWidget(pushButton_4);


        horizontalLayout->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        tableView = new QTableView(role);
        tableView->setObjectName("tableView");

        gridLayout->addWidget(tableView, 2, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(role);

        QMetaObject::connectSlotsByName(role);
    } // setupUi

    void retranslateUi(QWidget *role)
    {
        role->setWindowTitle(QCoreApplication::translate("role", "Form", nullptr));
        refresh->setText(QCoreApplication::translate("role", "\351\207\215\346\226\260\346\225\264\347\220\206", nullptr));
        pushButton_2->setText(QCoreApplication::translate("role", "\346\267\273\345\212\240", nullptr));
        pushButton_3->setText(QCoreApplication::translate("role", "\346\270\233\345\260\221", nullptr));
        pushButton_4->setText(QCoreApplication::translate("role", "\345\210\252\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class role: public Ui_role {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROLE_H
