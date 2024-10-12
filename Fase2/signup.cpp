#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent, AVLTree *usuariosAVL, QMainWindow *mainWindow) :
    QMainWindow(parent),
    ui(new Ui::SignUp),
    usuariosAVL(usuariosAVL),
    mainWindow(mainWindow)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_aceptar_clicked()
{
    try {
        QString nombres = ui->lineEdit_nombre->text();
        QString apellidos = ui->lineEdit_2_apellido->text();
        QString correo = ui->lineEdit_3_correo->text();
        QString contrasena = ui->lineEdit_4_password->text();
        QString fechaNacimiento = ui->dateEdit_fechaNac->date().toString("dd/MM/yyyy");

        if (nombres.isEmpty() || apellidos.isEmpty() || correo.isEmpty() || contrasena.isEmpty() || fechaNacimiento.isEmpty()) {
            QMessageBox::warning(this, "Error", "Por favor, completa todos los campos.");
            return;
        }

        if (usuariosAVL == nullptr) {
            QMessageBox::critical(this, "Error", "El árbol AVL no está inicializado.");
            return;
        }

        usuariosAVL->insert(nombres.toStdString(), apellidos.toStdString(), fechaNacimiento.toStdString(),
                            correo.toStdString(), contrasena.toStdString());

        QMessageBox::information(this, "Registro exitoso", "Ya puedes iniciar sesión.");

        // Cerrar la ventana de registro y volver a mostrar la ventana principal
        this->close();
        if (mainWindow != nullptr) {
            mainWindow->show();
        }

    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Ocurrió un error: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::critical(this, "Error", "Ocurrió un error inesperado.");
    }
}
