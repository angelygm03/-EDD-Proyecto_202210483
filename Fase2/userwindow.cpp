#include "userwindow.h"
#include "ui_userwindow.h"

Userwindow::Userwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Userwindow)
{
    ui->setupUi(this);
}

Userwindow::~Userwindow()
{
    delete ui;
}
