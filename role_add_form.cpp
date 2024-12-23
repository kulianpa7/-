#include "role_add_form.h"
#include "ui_role_add_form.h"

role_add_form::role_add_form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::role_add_form)
{
    ui->setupUi(this);
}

role_add_form::~role_add_form()
{
    delete ui;
}
