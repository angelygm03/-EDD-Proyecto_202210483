#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QMessageBox>
#include "mainwindow.h"
#include <iostream>

AdminWindow::AdminWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    usuariosAVL = new AVLTree();
}

AdminWindow::~AdminWindow()
{
    delete usuariosAVL;
    delete ui;
}

void AdminWindow::on_actionCargar_usuarios_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Seleccionar archivo JSON", "", "Archivos JSON (*.json);;Todos los archivos (*)");

    if (fileName.isEmpty()) {
        return; // Si no se selecciona ningún archivo, salir de la función
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo: " + file.errorString());
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    // Asegúrate de que los datos están en UTF-8
    QString jsonData = QString::fromUtf8(fileData);

    // Parsear el contenido JSON
    QJsonDocument doc = QJsonDocument::fromJson(jsonData.toUtf8());

    if (doc.isNull() || !doc.isArray()) {
        QMessageBox::warning(this, "Error", "El archivo no es un JSON válido.");
        return;
    }

    QJsonArray jsonArray = doc.array();

    // Iterar sobre cada objeto en el JSON
    for (QJsonValue value : jsonArray) {
        QJsonObject usuario = value.toObject();

        QString qNombres = usuario["nombres"].toString();
        QString qApellidos = usuario["apellidos"].toString();
        QString qFechaNacimiento = usuario["fecha_de_nacimiento"].toString();
        QString qCorreo = usuario["correo"].toString();
        QString qContrasena = usuario["contraseña"].toString();

        // Convertir QString a std::string
        std::string nombres = qNombres.toStdString();
        std::string apellidos = qApellidos.toStdString();
        std::string fechaNacimiento = qFechaNacimiento.toStdString();
        std::string correo = qCorreo.toStdString();
        std::string contrasena = qContrasena.toStdString();

        // Insertar en el árbol AVL
        usuariosAVL->insert(nombres, apellidos, fechaNacimiento, correo, contrasena);
        std::cout << "Cargado usuario: " << nombres << " " << apellidos << " (" << correo << ")" << std::endl;
    }

    // Imprimir los usuarios en orden alfabético
    usuariosAVL->graph();

    QMessageBox::information(this, "Éxito", "Usuarios cargados exitosamente.");
}


void AdminWindow::on_actionCargar_solicitudes_triggered() {
    // Seleccionar el archivo JSON
    QString fileName = QFileDialog::getOpenFileName(this, "Seleccionar archivo JSON", "", "Archivos JSON (*.json);;Todos los archivos (*)");

    if (fileName.isEmpty()) {
        return;  // Si no se selecciona un archivo, salir de la función
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo: " + file.errorString());
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    // Parsear el contenido JSON
    QJsonDocument doc = QJsonDocument::fromJson(fileData);

    if (doc.isNull() || !doc.isArray()) {
        QMessageBox::warning(this, "Error", "El archivo no es un JSON válido.");
        return;
    }

    QJsonArray jsonArray = doc.array();

    // Iterar sobre cada solicitud en el JSON
    for (QJsonValue value : jsonArray) {
        QJsonObject solicitud = value.toObject();

        QString qEmisor = solicitud["emisor"].toString();
        QString qReceptor = solicitud["receptor"].toString();
        QString qEstado = solicitud["estado"].toString();

        // Convertir QString a std::string
        std::string emisor = qEmisor.toStdString();
        std::string receptor = qReceptor.toStdString();
        std::string estado = qEstado.toStdString();

        // Buscar el emisor y receptor en el árbol AVL
        Node* usuarioReceptor = usuariosAVL->buscarPorCorreo(receptor);
        Node* usuarioEmisor = usuariosAVL->buscarPorCorreo(emisor);

        // Si el receptor existe y la solicitud está pendiente, agregarla a la pila del receptor
        if (usuarioReceptor != nullptr && estado == "PENDIENTE") {
            usuarioReceptor->solicitudes.push(emisor, receptor, estado);
            std::cout << "Solicitud para " << receptor << " de " << emisor << " añadida a la pila del receptor." << std::endl;
        }

        // Si el emisor existe y la solicitud está pendiente, agregarla a su lista de enviadas
        if (usuarioEmisor != nullptr && estado == "PENDIENTE") {
            usuarioEmisor->solicitudListEnviadas.insert(emisor, receptor, estado);
            std::cout << "Solicitud enviada de " << emisor << " para " << receptor << " añadida a la lista de enviadas del emisor." << std::endl;
        }
    }

    QMessageBox::information(this, "Éxito", "Solicitudes cargadas exitosamente.");
}

void AdminWindow::on_actionCargarPublicaciones_triggered()
{
    // Implementación para cargar publicaciones
}
void AdminWindow::on_pushButton_clicked()
{
    MainWindow *mainWindow = new MainWindow(this, usuariosAVL);
    mainWindow->show();
    this->hide();
}

