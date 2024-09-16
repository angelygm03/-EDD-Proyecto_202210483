#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, AVLTree *usuarios)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , usuariosAVL(usuarios)
{
    ui->setupUi(this);
    adminwindow = new AdminWindow();
    userwindow = new Userwindow();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete adminwindow;
    delete userwindow;
}

void MainWindow::on_pushButton_Login_clicked()
{
    QString qCorreo = ui->lineEdit_Usuario->text();
    QString qPassword = ui->lineEdit_2_Password->text();

    std::string correo = qCorreo.toStdString();
    std::string password = qPassword.toStdString();

    // Verificar si es administrador
    if (correo == "admin@gmail.com" && password == "EDD2S2024") {
        QMessageBox::information(this, "Alerta", "Inicio de sesión como administrador exitoso");
        adminwindow->show();
        this->hide();
    }
    // Verificar si es un usuario regular
    else if (usuariosAVL && usuariosAVL->verificarCredenciales(correo, password)) {
        QMessageBox::information(this, "Alerta", "Inicio de sesión como usuario exitoso");
        userwindow->show();
        this->hide();
    }
    // Credenciales inválidas
    else {
        QMessageBox::warning(this, "Alerta", "Credenciales inválidas. Inténtalo nuevamente");
    }
}

