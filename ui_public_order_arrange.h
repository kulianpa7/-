/********************************************************************************
** Form generated from reading UI file 'public_order_arrange.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUBLIC_ORDER_ARRANGE_H
#define UI_PUBLIC_ORDER_ARRANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_order_arrange
{
public:
    QGridLayout *gridLayout;
    QLabel *label_1;
    QLineEdit *contact;
    QLabel *label_2;
    QLineEdit *contact_phone;
    QLabel *label_3;
    QLineEdit *can_passanger;
    QLabel *label_4;
    QLineEdit *location;
    QLabel *label_5;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_6;
    QComboBox *comboBox;
    QPushButton *save;

    void setupUi(QWidget *order_arrange)
    {
        if (order_arrange->objectName().isEmpty())
            order_arrange->setObjectName("order_arrange");
        order_arrange->resize(775, 372);
        gridLayout = new QGridLayout(order_arrange);
        gridLayout->setObjectName("gridLayout");
        label_1 = new QLabel(order_arrange);
        label_1->setObjectName("label_1");
        QFont font;
        font.setPointSize(20);
        label_1->setFont(font);

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        contact = new QLineEdit(order_arrange);
        contact->setObjectName("contact");
        contact->setMinimumSize(QSize(0, 40));
        QFont font1;
        font1.setPointSize(14);
        contact->setFont(font1);

        gridLayout->addWidget(contact, 0, 1, 1, 1);

        label_2 = new QLabel(order_arrange);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        contact_phone = new QLineEdit(order_arrange);
        contact_phone->setObjectName("contact_phone");
        contact_phone->setMinimumSize(QSize(0, 40));
        contact_phone->setFont(font1);

        gridLayout->addWidget(contact_phone, 1, 1, 1, 1);

        label_3 = new QLabel(order_arrange);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        can_passanger = new QLineEdit(order_arrange);
        can_passanger->setObjectName("can_passanger");
        can_passanger->setMinimumSize(QSize(0, 40));
        can_passanger->setFont(font1);

        gridLayout->addWidget(can_passanger, 2, 1, 1, 1);

        label_4 = new QLabel(order_arrange);
        label_4->setObjectName("label_4");
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        location = new QLineEdit(order_arrange);
        location->setObjectName("location");
        location->setMinimumSize(QSize(0, 40));
        location->setFont(font1);

        gridLayout->addWidget(location, 3, 1, 1, 1);

        label_5 = new QLabel(order_arrange);
        label_5->setObjectName("label_5");
        label_5->setFont(font);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        dateTimeEdit = new QDateTimeEdit(order_arrange);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setMinimumSize(QSize(0, 40));
        dateTimeEdit->setFont(font1);

        gridLayout->addWidget(dateTimeEdit, 4, 1, 1, 1);

        label_6 = new QLabel(order_arrange);
        label_6->setObjectName("label_6");
        label_6->setFont(font);

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        comboBox = new QComboBox(order_arrange);
        comboBox->setObjectName("comboBox");
        comboBox->setMinimumSize(QSize(0, 40));
        comboBox->setFont(font1);

        gridLayout->addWidget(comboBox, 5, 1, 1, 1);

        save = new QPushButton(order_arrange);
        save->setObjectName("save");
        save->setMinimumSize(QSize(0, 40));
        QFont font2;
        font2.setPointSize(24);
        save->setFont(font2);

        gridLayout->addWidget(save, 6, 0, 1, 2);


        retranslateUi(order_arrange);

        QMetaObject::connectSlotsByName(order_arrange);
    } // setupUi

    void retranslateUi(QWidget *order_arrange)
    {
        order_arrange->setWindowTitle(QCoreApplication::translate("order_arrange", "\350\250\202\345\226\256\347\263\273\347\265\261", nullptr));
        label_1->setText(QCoreApplication::translate("order_arrange", "\350\201\257\347\265\241\344\272\272", nullptr));
        label_2->setText(QCoreApplication::translate("order_arrange", "\351\200\243\347\265\241\351\233\273\350\251\261", nullptr));
        label_3->setText(QCoreApplication::translate("order_arrange", "\346\225\270\351\207\217", nullptr));
        label_4->setText(QCoreApplication::translate("order_arrange", "\345\234\260\351\273\236", nullptr));
        label_5->setText(QCoreApplication::translate("order_arrange", "\346\231\202\351\226\223", nullptr));
        label_6->setText(QCoreApplication::translate("order_arrange", "\345\217\270\346\251\237", nullptr));
        save->setText(QCoreApplication::translate("order_arrange", "\345\204\262\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class order_arrange: public Ui_order_arrange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUBLIC_ORDER_ARRANGE_H
