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
    publicacionesList = new DoubleList();
    comentariosTree = new ArbolB();

    // Mensaje de depuración para verificar la inicialización
    qDebug() << "AdminWindow inicializado con usuariosAVL:" << usuariosAVL;
}


AdminWindow::~AdminWindow()
{
    qDebug() << "Destruyendo AdminWindow, usuariosAVL:" << usuariosAVL;
    delete usuariosAVL;
    delete publicacionesList;
    delete comentariosTree;
    delete ui;
}


void AdminWindow::on_actionCargar_usuarios_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Seleccionar archivo JSON", "", "Archivos JSON (*.json);;Todos los archivos (*)");

    if (fileName.isEmpty()) {
        qDebug() << "No se seleccionó ningún archivo.";
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo: " + file.errorString());
        qDebug() << "No se pudo abrir el archivo:" << file.errorString();
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QString jsonData = QString::fromUtf8(fileData);

    QJsonDocument doc = QJsonDocument::fromJson(jsonData.toUtf8());

    if (doc.isNull() || !doc.isArray()) {
        QMessageBox::warning(this, "Error", "El archivo no es un JSON válido.");
        qDebug() << "El archivo JSON no es válido.";
        return;
    }

    QJsonArray jsonArray = doc.array();

    for (QJsonValue value : jsonArray) {
        QJsonObject usuario = value.toObject();

        QString qNombres = usuario["nombres"].toString();
        QString qApellidos = usuario["apellidos"].toString();
        QString qFechaNacimiento = usuario["fecha_de_nacimiento"].toString();
        QString qCorreo = usuario["correo"].toString();
        QString qContrasena = usuario["contraseña"].toString();

        std::string nombres = qNombres.toStdString();
        std::string apellidos = qApellidos.toStdString();
        std::string fechaNacimiento = qFechaNacimiento.toStdString();
        std::string correo = qCorreo.toStdString();
        std::string contrasena = qContrasena.toStdString();

        usuariosAVL->insert(nombres, apellidos, fechaNacimiento, correo, contrasena);

        // Mensaje de depuración para verificar los datos cargados
        qDebug() << "Usuario cargado:" << QString::fromStdString(nombres) << QString::fromStdString(apellidos) << QString::fromStdString(correo);
    }

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
        // Manejar solicitudes aceptadas
        if (estado == "ACEPTADA") {
            if (usuarioReceptor != nullptr) {
                usuarioReceptor->friends.addFriend(emisor); // Añadir el emisor a la lista de amigos del receptor
                std::cout << emisor << " añadido a la lista de amigos de " << receptor << std::endl;
            }

            if (usuarioEmisor != nullptr) {
                usuarioEmisor->friends.addFriend(receptor); // Añadir el receptor a la lista de amigos del emisor
                std::cout << receptor << " añadido a la lista de amigos de " << emisor << std::endl;
            }
        }
    }

    QMessageBox::information(this, "Éxito", "Solicitudes cargadas exitosamente.");
}


void AdminWindow::on_actionCargarPublicaciones_triggered() {
    // Abrir el archivo JSON
    QString fileName = QFileDialog::getOpenFileName(this, "Seleccionar archivo JSON", "", "Archivos JSON (*.json);;Todos los archivos (*)");

    if (fileName.isEmpty()) {
        return; // Salir si no se selecciona archivo
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo: " + file.errorString());
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData);

    if (doc.isNull() || !doc.isArray()) {
        QMessageBox::warning(this, "Error", "El archivo no es un JSON válido.");
        return;
    }

    QJsonArray jsonArray = doc.array();

    // Recorrer las publicaciones
    for (const QJsonValue& publicacionValue : jsonArray) {
        QJsonObject publicacionObj = publicacionValue.toObject();

        QString correo = publicacionObj["correo"].toString();
        QString contenido = publicacionObj["contenido"].toString();
        QString fecha = publicacionObj["fecha"].toString();
        QString hora = publicacionObj["hora"].toString();
        QString imagenPath = publicacionObj["imagen"].toString();

        // Insertar la publicación en la lista doblemente enlazada
        publicacionesList->insertAtEnd(correo.toStdString(), contenido.toStdString(), fecha.toStdString(), hora.toStdString(), imagenPath.toStdString());

        // Insertar comentarios en el Árbol B
        QJsonArray comentariosArray = publicacionObj["comentarios"].toArray();

        for (const QJsonValue& comentarioValue : comentariosArray) {
            QJsonObject comentarioObj = comentarioValue.toObject();

            QString correoComentario = comentarioObj["correo"].toString();
            QString comentarioTexto = comentarioObj["comentario"].toString();
            QString fechaComentario = comentarioObj["fecha"].toString();
            QString horaComentario = comentarioObj["hora"].toString();

            // Crear un comentario y agregarlo al árbol B
            Comentario* nuevoComentario = new Comentario(correoComentario.toStdString(), comentarioTexto.toStdString(), fechaComentario.toStdString(), horaComentario.toStdString());
            comentariosTree->insertar(nuevoComentario);
        }
    }

    // Imprimir publicaciones y comentarios después de cargar
    publicacionesList->print();
    comentariosTree->imprimir();
}



void AdminWindow::on_pushButton_clicked() {
    // Verificar si la ventana principal ya está abierta
    MainWindow *mainWindow = qobject_cast<MainWindow*>(QApplication::activeWindow());
    if (!mainWindow) {
        // Verificar que usuariosAVL y publicacionesList no sean nulos antes de crear MainWindow
        qDebug() << "Creando MainWindow con usuariosAVL y publicacionesList:";
        mainWindow = new MainWindow(nullptr, usuariosAVL, publicacionesList);
    }
    mainWindow->show();
    this->close();
}




