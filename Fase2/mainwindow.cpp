#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "avltree.h"

MainWindow::MainWindow(QWidget *parent, AVLTree *usuarios, DoubleList* publicacionesList, BinarySearchTree *existingBST)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , usuariosAVL(usuarios)
    , publicacionesList(publicacionesList)
    , bst(existingBST)
{
    ui->setupUi(this);
    qDebug() << "Dirección de usuariosAVL en MainWindow:" << usuariosAVL;
    qDebug() << "MainWindow inicializado con usuariosAVL:" << usuariosAVL;
    adminwindow = new AdminWindow(nullptr, usuariosAVL, bst);
    userwindow = nullptr;
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
        Node* usuarioBuscado = usuariosAVL->buscarPorCorreo(correo);
        if(usuarioBuscado) {
            QMessageBox::information(this, "Alerta", "Inicio de sesión como usuario exitoso");
            userwindow = new Userwindow(this, usuariosAVL, usuarioBuscado, publicacionesList, bst, adminwindow->comentariosTree);
            userwindow->show();
            this->hide();
        }
    }
    // Credenciales inválidas
    else {
        QMessageBox::warning(this, "Alerta", "Credenciales inválidas. Inténtalo nuevamente");
    }
}


void MainWindow::on_pushButton_Registro_clicked() {
    if (!usuariosAVL) {
        QMessageBox::critical(this, "Error", "El árbol AVL no está inicializado.");
        return;
    }
    SignUp *signupWindow = new SignUp(this, usuariosAVL, this);
    signupWindow->show();
    this->hide();
}
