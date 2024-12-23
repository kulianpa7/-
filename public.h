#ifndef PUBLIC_H
#define PUBLIC_H

#include <QWidget>

namespace Ui {
class public;
}

class public : public QWidget
{
    Q_OBJECT

public:
    explicit public(QWidget *parent = nullptr);
    ~public();

private:
    Ui::public *ui;
};

#endif // PUBLIC_H
