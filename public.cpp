#include "public.h"
#include "ui_public.h"

public::public(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::public)
{
    ui->setupUi(this);
}

public::~public()
{
    delete ui;
}
