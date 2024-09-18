#include "userwindow.h"
#include "ui_userwindow.h"
#include <QMessageBox>
#include <QTabWidget>
#include "mainwindow.h"

Userwindow::Userwindow(QWidget *parent, AVLTree *usuariosAVL, Node *usuarioActual)
    : QMainWindow(parent)
    , ui(new Ui::Userwindow)
    , usuariosAVL(usuariosAVL)
    , pilaSolicitudes(nullptr)
    , usuarioActual(usuarioActual)
{
    ui->setupUi(this);
    if (usuarioActual != nullptr) {
        pilaSolicitudes = &usuarioActual->solicitudes;
    }
    populateSolicitudesTable();
}

Userwindow::~Userwindow()
{
    delete ui;
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

// Método para llenar la tabla con las solicitudes del usuario
void Userwindow::populateSolicitudesTable()
{
    if (usuarioActual == nullptr || pilaSolicitudes == nullptr) {
        return;
    }

    ui->tableWidget_recibidas->setRowCount(0);  // Limpiar la tabla
    StackNode* current = pilaSolicitudes->getTop();

    int row = 0;
    while (current != nullptr) {
        // Agregar una nueva fila
        ui->tableWidget_recibidas->insertRow(row);

        // Llenar las celdas con la información de la solicitud
        ui->tableWidget_recibidas->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(current->emisor)));
        ui->tableWidget_recibidas->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(current->estado)));

        // Crear botones para aceptar y eliminar
        QPushButton* aceptarButton = new QPushButton("Aceptar");
        QPushButton* eliminarButton = new QPushButton("Eliminar");

        // Conectar las señales de los botones con los slots correspondientes
        connect(aceptarButton, &QPushButton::clicked, this, &Userwindow::aceptarSolicitud);
        connect(eliminarButton, &QPushButton::clicked, this, &Userwindow::eliminarSolicitud);

        // Agregar los botones a la tabla
        ui->tableWidget_recibidas->setCellWidget(row, 2, aceptarButton);
        ui->tableWidget_recibidas->setCellWidget(row, 3, eliminarButton);

        current = current->next;
        row++;
    }
}

// Slot para aceptar la solicitud
void Userwindow::aceptarSolicitud()
{
    // Obtener el índice de la fila donde se hizo clic
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (!senderButton) return;

    int row = ui->tableWidget_recibidas->indexAt(senderButton->pos()).row();
    QString emisor = ui->tableWidget_recibidas->item(row, 0)->text();

    // Actualizar el estado de la solicitud en la pila
    StackNode* current = pilaSolicitudes->getTop();
    StackNode* prev = nullptr;
    StackNode* nodoAEliminar = nullptr;

    // Buscar el nodo correspondiente a la solicitud
    while (current != nullptr) {
        if (current->emisor == emisor.toStdString()) {
            // Cambiar el estado a "ACEPTADA"
            current->estado = "ACEPTADA";
            nodoAEliminar = current; // Guardar el nodo para eliminar después
            break;
        }
        prev = current;
        current = current->next;
    }

    // Eliminar el nodo de la pila
    if (nodoAEliminar) {
        if (prev == nullptr) {
            // Eliminar el primer nodo
            pilaSolicitudes->pop();
        } else {
            prev->next = nodoAEliminar->next;
            delete nodoAEliminar;
        }
    }

    //Agregar el emisor a la lista de amigos del usuario actual
    if (usuarioActual != nullptr) {
        // Añadir el emisor a la lista de amigos del receptor (usuarioActual)
        usuarioActual->friends.addFriend(emisor.toStdString());
        std::cout << "Amistad aceptada: " << emisor.toStdString() << " añadido a la lista de amigos de " << usuarioActual->correo << std::endl;

        // Añadir el receptor a la lista de amigos del emisor en el árbol AVL
        Node* usuarioEmisor = usuariosAVL->buscarPorCorreo(emisor.toStdString());
        if (usuarioEmisor != nullptr) {
            usuarioEmisor->friends.addFriend(usuarioActual->correo); // Añadir el receptor a la lista de amigos del emisor
            std::cout << "Amistad aceptada: " << usuarioActual->correo << " añadido a la lista de amigos de " << emisor.toStdString() << std::endl;
        }
    }

    // Actualizar la tabla después de aceptar
    populateSolicitudesTable();
}

void Userwindow::eliminarSolicitud()
{
    // Obtener el índice de la fila donde se hizo clic
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (!senderButton) return;

    int row = ui->tableWidget_recibidas->indexAt(senderButton->pos()).row();
    QString emisor = ui->tableWidget_recibidas->item(row, 0)->text();

    // Eliminar la solicitud de la pila
    StackNode* current = pilaSolicitudes->getTop();
    StackNode* prev = nullptr;

    while (current != nullptr) {
        if (current->emisor == emisor.toStdString()) {
            if (prev == nullptr) {
                pilaSolicitudes->pop();  // Eliminar el primer nodo
            } else {
                prev->next = current->next;
                delete current;
            }
            break;
        }
        prev = current;
        current = current->next;
    }

    // Actualizar la tabla después de eliminar
    populateSolicitudesTable();
}



void Userwindow::on_pushButton_clicked()
{
    {
        // Verificar si la ventana principal ya está abierta
        MainWindow *mainWindow = qobject_cast<MainWindow*>(QApplication::activeWindow());
        if (!mainWindow) {
            mainWindow = new MainWindow(nullptr, usuariosAVL);
        }
        mainWindow->show();
        this->close();
    }
}


void Userwindow::on_pushButton_2_agregar_clicked() {
    QString correoReceptor = ui->lineEdit_buscar->text(); // Obtener el correo del receptor de la interfaz

    // Verificar si el correo del receptor no está vacío
    if (correoReceptor.isEmpty()) {
        QMessageBox::warning(this, "Error", "Debe ingresar un correo válido.");
        return;
    }

    // Buscar el usuario receptor en el AVL
    Node* usuarioReceptor = usuariosAVL->buscarPorCorreo(correoReceptor.toStdString());

    if (!usuarioReceptor) {
        QMessageBox::information(this, "Usuario no encontrado", "El usuario con el correo ingresado no existe.");
        return;
    }

    // Agregar la solicitud a la pila del receptor
    usuarioReceptor->solicitudes.push(usuarioActual->correo, usuarioReceptor->correo, "PENDIENTE");
    std::cout << "Solicitud enviada a " << usuarioReceptor->correo << std::endl;

    // Agregar la solicitud a la lista de solicitudes enviadas del emisor (usuarioActual)
    usuarioActual->solicitudListEnviadas.insert(usuarioActual->correo, usuarioReceptor->correo, "PENDIENTE");
    std::cout << "Solicitud añadida a la lista de solicitudes enviadas de " << usuarioActual->correo << std::endl;

    QMessageBox::information(this, "Solicitud Enviada", "Se ha enviado la solicitud de amistad correctamente.");
}
