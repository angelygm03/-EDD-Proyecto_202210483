#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    QString usuario = ui->lineEdit_Usuario->text();
    QString password = ui->lineEdit_2_Password->text();
    if (usuario == "admin@gmail.com" && password == "EDD2S2024")
    {
        QMessageBox::information(this, "Alerta", "Inicio de sesión exitoso");
        this->hide();
        AdminWindow *adminwindow = new AdminWindow();
        adminwindow->show();
    }
    else
    {
        QMessageBox::warning(this, "Alerta", "Credenciales inválidas. Inténtalo nuevamente");
    }
}

