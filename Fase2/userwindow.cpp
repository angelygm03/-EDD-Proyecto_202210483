#include "userwindow.h"
#include "ui_userwindow.h"
#include "publicacioneswindow.h"
#include <QMessageBox>

Userwindow::Userwindow(QWidget *parent, AVLTree *usuariosAVL)
    : QMainWindow(parent)
    , ui(new Ui::Userwindow)
    , usuariosAVL(usuariosAVL)
{
    ui->setupUi(this);
}

Userwindow::~Userwindow()
{
    delete ui;
}

void Userwindow::on_actionIr_a_publicaciones_triggered()
{
    Publicarwindow *publicarwindow = new Publicarwindow();
    publicarwindow->show();
    this->hide();
}


void Userwindow::on_pushButton_2_buscar_clicked()
{
    QString correo = ui->lineEdit_buscar->text();

    // Mensaje de depuración para verificar si usuariosAVL está inicializado
    if (!usuariosAVL) {
        QMessageBox::warning(this, "Error", "La estructura de usuarios no está inicializada.");
        qDebug() << "usuariosAVL es nulo.";
        return;
    }

    Node* usuarioBuscado = usuariosAVL->buscarPorCorreo(correo.toStdString());

    if (usuarioBuscado) {
        // Mensajes de depuración para verificar el usuario encontrado
        qDebug() << "Usuario encontrado:";
        qDebug() << "Nombres:" << QString::fromStdString(usuarioBuscado->nombres);
        qDebug() << "Apellidos:" << QString::fromStdString(usuarioBuscado->apellidos);
        qDebug() << "Correo:" << QString::fromStdString(usuarioBuscado->correo);
        qDebug() << "Fecha de Nacimiento:" << QString::fromStdString(usuarioBuscado->fechaNacimiento);

        ui->lineEdit_2_nombres->setText(QString::fromStdString(usuarioBuscado->nombres));
        ui->lineEdit_3_apellidos->setText(QString::fromStdString(usuarioBuscado->apellidos));
        ui->lineEdit_4_correo->setText(QString::fromStdString(usuarioBuscado->correo));
        ui->lineEdit_5_fechanac->setText(QString::fromStdString(usuarioBuscado->fechaNacimiento));
    } else {
        QMessageBox::information(this, "Usuario no encontrado", "El usuario con el correo ingresado no existe.");
        qDebug() << "Usuario con correo" << correo << "no encontrado.";
    }
}
