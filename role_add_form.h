#ifndef ROLE_ADD_FORM_H
#define ROLE_ADD_FORM_H

#include <QWidget>

namespace Ui {
class role_add_form;
}

class role_add_form : public QWidget
{
    Q_OBJECT

public:
    explicit role_add_form(QWidget *parent = nullptr);
    ~role_add_form();

private:
    Ui::role_add_form *ui;
};

#endif // ROLE_ADD_FORM_H
