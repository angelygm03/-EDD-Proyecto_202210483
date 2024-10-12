#include "userwindow.h"
#include "ui_userwindow.h"
#include <QMessageBox>
#include <QTabWidget>
#include "mainwindow.h"
#include <QFileDialog>
#include <QImage>
#include <QGraphicsScene>
#include <QPainter>
#include <iostream>
#include <string>
#include "imagewindow.h"
#include <map>
#include <vector>
#include <algorithm>

Userwindow::Userwindow(QWidget *parent, AVLTree *usuariosAVL, Node *usuarioActual, DoubleList* publicacionesList, BinarySearchTree *bst, ArbolB* comentariosTree)
    : QMainWindow(parent),
    ui(new Ui::Userwindow),
    usuariosAVL(usuariosAVL),
    bst(bst),
    pilaSolicitudes(nullptr),
    usuarioActual(usuarioActual),
    publicaciones(publicacionesList),
    comentariosTree(comentariosTree) // Aquí inicializa el puntero
{
    ui->setupUi(this);
    if (usuarioActual != nullptr) {
        this->bst = usuarioActual->publicaciones;
        qDebug() << "Usuario logeado:" << QString::fromStdString(usuarioActual->correo);
        qDebug() << "BST inicializado con publicaciones:" << (bst != nullptr ? "Sí" : "No");
        // Mostrar la información del usuario logeado
        ui->lineEdit_2_nombreUsuario->setText(QString::fromStdString(usuarioActual->nombres));
        ui->lineEdit_3_apellidosUsuario->setText(QString::fromStdString(usuarioActual->apellidos));
        ui->lineEdit_4_correoUsuario->setText(QString::fromStdString(usuarioActual->correo));
        ui->lineEdit_5_fechanacUsuario->setText(QString::fromStdString(usuarioActual->fechaNacimiento));

        // Llenar la pila de solicitudes del usuario actual
        pilaSolicitudes = &usuarioActual->solicitudes;
        populateSolicitudesTable();


        // Llenar el listWidget_publicaciones con las publicaciones del árbol
        populatePublicacionesList();
    }
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
void Userwindow::populateSolicitudesTable() {
    if (usuarioActual == nullptr || pilaSolicitudes == nullptr) {
        return;
    }

    ui->tableWidget_recibidas->setRowCount(0);  // Limpiar la tabla
    StackNode* current = pilaSolicitudes->getTop();
    int row = 0;

    while (current != nullptr) {
        // Verificar si el emisor ya es amigo del usuario actual
        if (!usuarioActual->friends.esAmigo(current->emisor)) {  // Usa el nuevo método
            // Solo agregar a la tabla si no son amigos
            ui->tableWidget_recibidas->insertRow(row);
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
            row++;
        }
        current = current->next;
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
        QMessageBox::information(this, "Amigos", "¡Ahora son amigos!");
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
                QMessageBox::information(this, "Alerta", "Acabas de rechazar la solicitud de amistad");
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
    QString correoReceptor = ui->lineEdit_buscar->text(); // Obtener el correo del receptor

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

    // Verificar si ya son amigos
    if (usuarioActual->friends.esAmigo(correoReceptor.toStdString())) {  // Usa el nuevo método
        QMessageBox::information(this, "Ya son amigos", "Ya eres amigo de " + correoReceptor);
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

void Userwindow::on_pushButton_2_publicar_clicked() {
    QString contenido = ui->plainTextEdit_contenidoPost->toPlainText();
    if (contenido.isEmpty()) {
        QMessageBox::warning(this, "Error", "El contenido de la publicación no puede estar vacío.");
        return;
    }

    // Obtener la fecha y hora actuales
    QDateTime now = QDateTime::currentDateTime();
    QString fecha = now.toString("dd/MM/yyyy");
    QString hora = now.toString("HH:mm");

    // Insertar la publicación en la lista de publicaciones del usuario actual
    publicaciones->insertAtEnd(usuarioActual->correo, contenido.toStdString(), fecha.toStdString(), hora.toStdString(), imagenPath.toStdString());
    publicaciones->print();

    // Insertar la publicación en la lista de publicaciones del usuario actual
    publicaciones->insertAtEnd(usuarioActual->correo, contenido.toStdString(), fecha.toStdString(), hora.toStdString(), imagenPath.toStdString());

    // **Insertar la publicación en el árbol BST**
    bst->insertarPublicacion(fecha.toStdString(), usuarioActual->correo, contenido.toStdString(), hora.toStdString());
    // Mostrar publicaciones ordenadas por fecha
    bst->mostrarPublicacionesEnOrden();
    QMessageBox::information(this, "Publicación Registrada", "Tu publicación ha sido realizada con éxito.");
    populatePublicacionesList();
    publicaciones->print();

    // Limpiar el contenido y la imagen seleccionada
    ui->plainTextEdit_contenidoPost->clear();
    imagenPath.clear();
    QGraphicsScene *scene = new QGraphicsScene(this); // Limpiar imagen anterior
    ui->graphicsView_img->setScene(scene);
}

void Userwindow::on_pushButton_abrirImg_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Abrir Imagen", "", "Imágenes (*.png *.xpm *.jpg *.jpeg *.bmp)");

    if (!filePath.isEmpty()) {
        // Guardar el path de la imagen
        imagenPath = filePath;

        // Crear un nuevo QImage para cargar la imagen desde el path
        QImage image(imagenPath);
        if (image.isNull()) {
            QMessageBox::warning(this, "Error", "No se pudo cargar la imagen. Asegúrate de que el archivo sea una imagen válida.");
            return;
        }

        //mostrar la imagen en el QGraphicsView
        QGraphicsScene *scene = new QGraphicsScene(this);
        scene->addPixmap(QPixmap::fromImage(image));
        ui->graphicsView_img->setScene(scene);
        ui->graphicsView_img->setRenderHint(QPainter::Antialiasing); // renderizar la imagen
        ui->graphicsView_img->fitInView(scene->sceneRect(), Qt::KeepAspectRatio); // mantener la relación de aspecto
    }
}

void Userwindow::graficarPublicacionesConAmigos() {
    // Graficar publicaciones del usuario actual
    std::string imagenUsuario = usuarioActual->publicaciones->graficarArbol("publicaciones_" + usuarioActual->correo);

    // Ahora graficamos las publicaciones de los amigos
    FriendNode* currentFriend = usuarioActual->friends.head;
    while (currentFriend != nullptr) {
        Node* amigoNode = usuariosAVL->buscarPorCorreo(currentFriend->friendEmail);
        if (amigoNode != nullptr && amigoNode->publicaciones != nullptr) {
            std::string imagenAmigo = amigoNode->publicaciones->graficarArbol("publicaciones_" + amigoNode->correo);
            // Aquí podrías combinar las imágenes de las publicaciones si es necesario
        }
        currentFriend = currentFriend->next;
    }

    // Cargar y mostrar la imagen del usuario actual en el QGraphicsView
    QImage image(QString::fromStdString(imagenUsuario));
    if (image.isNull()) {
        QMessageBox::warning(this, "Error", "No se pudo cargar la gráfica de tus publicaciones.");
        return;
    }

    // Mostrar la imagen en el QGraphicsView
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView_bst->setScene(scene);
    ui->graphicsView_bst->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_bst->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void Userwindow::on_pushButton_7_reportes_clicked() {
    mostrarTop3Fechas();
    graficarPublicacionesConAmigos();
}

void Userwindow::populatePublicacionesList() {
    if (bst == nullptr || usuarioActual == nullptr) {
        qDebug() << "BST o usuario actual no están inicializados."; // Depuración
        return; // Asegúrate de que el árbol y el usuario estén inicializados.
    }

    // Limpiar el listWidget
    ui->listWidget_publicaciones->clear();
    qDebug() << "Llenando publicaciones del usuario actual:" << QString::fromStdString(usuarioActual->correo);

    // Mostrar publicaciones del usuario actual
    mostrarPublicacionesDelUsuario(usuarioActual->correo);

    // Ahora buscar y mostrar publicaciones de los amigos
    FriendNode* currentFriend = usuarioActual->friends.head; // Obtener la lista de amigos
    while (currentFriend != nullptr) {
        qDebug() << "Mostrando publicaciones de amigo:" << QString::fromStdString(currentFriend->friendEmail); // Depuración
        mostrarPublicacionesDelUsuario(currentFriend->friendEmail); // Mostrar publicaciones de cada amigo
        currentFriend = currentFriend->next; // Avanzar al siguiente amigo
    }
}

void Userwindow::mostrarPublicacionesDelUsuario(const std::string& userEmail) {
    qDebug() << "Mostrando publicaciones del usuario:" << QString::fromStdString(userEmail);

    Node* amigoNode = usuariosAVL->buscarPorCorreo(userEmail);
    if (amigoNode) {
        if (amigoNode->publicaciones == nullptr) {
            qDebug() << "El amigo no tiene publicaciones (BST es nulo).";
        } else {
            qDebug() << "El amigo tiene publicaciones (BST no es nulo).";

            // Supongamos que aquí decides cuál BST usar.
            mostrarPublicacionesPorFecha(amigoNode->publicaciones->root, userEmail);
        }
    } else {
        qDebug() << "No se encontró al amigo en el AVL.";
    }
}

// El método para buscar publicaciones en el BST por las fechas y el correo del usuario
void Userwindow::mostrarPublicacionesPorFecha(NodeBST* nodo, const std::string& userEmail) {
    if (nodo == nullptr) return; // Si el nodo es nulo, no hay publicaciones.

    // Recurriendo a la izquierda
    mostrarPublicacionesPorFecha(nodo->left, userEmail);

    // Ahora mostramos las publicaciones en este nodo
    FechaNodo* temp = nodo->publicaciones.head; // Acceder a la lista de publicaciones
    while (temp != nullptr) { // Mientras haya publicaciones
        if (temp->correo == userEmail) { // Solo muestro las publicaciones del correo especificado
            QString publicacion = QString("Usuario: %1\nFecha: %2\nHora: %3\nContenido: %4\n")
                                      .arg(QString::fromStdString(temp->correo))
                                      .arg(QString::fromStdString(nodo->fecha))
                                      .arg(QString::fromStdString(temp->hora))
                                      .arg(QString::fromStdString(temp->contenido));
            ui->listWidget_publicaciones->addItem(publicacion);
            qDebug() << "Publicación añadida del amigo:" << publicacion; // Depuración
        }
        temp = temp->next; // Avanzar al siguiente nodo en la lista
    }

    // Recurriendo a la derecha
    mostrarPublicacionesPorFecha(nodo->right, userEmail);
}

NodeBST* Userwindow::buscarNodoPorFecha(NodeBST* node, const std::string& fecha) {
    if (node == nullptr) {
        return nullptr;
    }

    // Comparar exactamente la fecha
    if (fecha == node->fecha) {
        return node;  // Nodo encontrado
    } else if (fecha < node->fecha) {
        return buscarNodoPorFecha(node->left, fecha);
    } else { // (fecha > node->fecha)
        return buscarNodoPorFecha(node->right, fecha);
    }
}

void Userwindow::mostrarPublicacionesEnListWidget(NodeBST* nodo) {
    if (nodo == nullptr) return; // Asegúrate de que el nodo es válido

    // Recorrer las publicaciones en inorden
    mostrarPublicacionesEnListWidget(nodo->left); // Recursión izquierda

    // Mostrar las publicaciones de este nodo
    FechaNodo* temp = nodo->publicaciones.head; // Acceder a la lista
    while (temp != nullptr) {  // Mientras haya publicaciones
        // Crear una cadena de texto para mostrar la publicación
        QString publicacion = QString("Usuario: %1\nFecha: %2\nHora: %3\nContenido: %4\n")
                                  .arg(QString::fromStdString(temp->correo))
                                  .arg(QString::fromStdString(nodo->fecha))
                                  .arg(QString::fromStdString(temp->hora))
                                  .arg(QString::fromStdString(temp->contenido));

        // Agregar al listWidget
        ui->listWidget_publicaciones->addItem(publicacion);
        temp = temp->next;  // Avanzar al siguiente nodo en la lista
    }

    mostrarPublicacionesEnListWidget(nodo->right); // Recursión derecha
}

void Userwindow::imprimirNodosBST(NodeBST* node) {
    if (node == nullptr) return;

    imprimirNodosBST(node->left); // Recursión hacia la izquierda
    std::cout << "Fecha: " << node->fecha << std::endl; // Imprimir la fecha
    imprimirNodosBST(node->right); // Recursión hacia la derecha
}

void Userwindow::on_pushButton_AplicarFecha_clicked()
{
    if (bst == nullptr) {
        QMessageBox::warning(this, "Error", "El árbol de publicaciones no está inicializado.");
        qDebug() << "BST es nulo.";
        return;
    }

    QDate fechaSeleccionada = ui->dateEdit_fechaBST->date();
    QString fechaStr = fechaSeleccionada.toString("dd/MM/yyyy");

    ui->listWidget_publicaciones->clear();  // Limpiar el listWidget

    NodeBST* nodoFecha = buscarNodoPorFecha(bst->root, fechaStr.toStdString());
    if (nodoFecha != nullptr) {
        std::cout << "Se encontró un nodo para la fecha: " << fechaStr.toStdString() << std::endl;
        mostrarPublicacionesEnListWidget(nodoFecha);
    } else {
        std::cout << "No se encontró un nodo para la fecha: " << fechaStr.toStdString() << std::endl;
        QMessageBox::information(this, "Sin Publicaciones", "No hay publicaciones para la fecha seleccionada.");
    }
}

void Userwindow::on_pushButton_3_recorridoAplicar_clicked()
{
    if (bst == nullptr) {
        QMessageBox::warning(this, "Error", "El árbol de publicaciones no está inicializado.");
        return;
    }

    // Obtener la opción seleccionada en el combo box
    QString opcionSeleccionada = ui->comboBox_2_recorrido->currentText();

    // Limpiar el listWidget antes de mostrar nuevas publicaciones
    ui->listWidget_publicaciones->clear();

    // Clear and store all publications based on the selected option
    if (opcionSeleccionada == "Inorden") {
        populatePublicacionesList(); // Actualizar el listWidget
    } else if (opcionSeleccionada == "Preorden") {
        bst->preorder(bst->root); // Mostrar el preorden en la consola (opcional)
        populatePublicacionesList(); // Actualizar el listWidget
    } else if (opcionSeleccionada == "Postorden") {
        bst->postorder(bst->root); // Mostrar el postorden en la consola (opcional)
        populatePublicacionesList(); // Actualizar el listWidget
    } else {
        QMessageBox::information(this, "Información", "No se ha seleccionado un recorrido válido.");
    }
}


void Userwindow::on_pushButton_4_Comments_clicked()
{
    std::string nombreArchivoDot = "arbolB.dot";
    comentariosTree->graficar(nombreArchivoDot);

    std::string nombreArchivoImagen = "arbolB.png";
    std::string comando = "dot -Tpng " + nombreArchivoDot + " -o " + nombreArchivoImagen;
    system(comando.c_str()); // Llamar a Graphviz para generar la imagen

    ImageWindow *imageWindow = new ImageWindow(QString::fromStdString(nombreArchivoImagen));
    imageWindow->setWindowTitle("Árbol B de Comentarios");
    imageWindow->resize(800, 600);
    imageWindow->show();
}

void Userwindow::mostrarTop3Fechas() {
    if (!usuarioActual) {
        QMessageBox::warning(this, "Error", "El usuario actual no está inicializado.");
        return;
    }

    std::map<std::string, int> conteoFechas;

    // Contar publicaciones del usuario actual
    contarPublicacionesPorFecha(usuarioActual, conteoFechas);

    // Contar publicaciones de amigos
    FriendNode* currentFriend = usuarioActual->friends.head;
    while (currentFriend) {
        Node* amigoNode = usuariosAVL->buscarPorCorreo(currentFriend->friendEmail);
        contarPublicacionesPorFecha(amigoNode, conteoFechas); // Aquí se cuentan las publicaciones del amigo
        currentFriend = currentFriend->next;
    }

    // Crear un vector de pares para ordenar
    std::vector<std::pair<std::string, int>> fechasConConteo(conteoFechas.begin(), conteoFechas.end());

    // Ordenar por conteo (más publicaciones primero)
    std::sort(fechasConConteo.begin(), fechasConConteo.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Ordenar de mayor a menor
    });

    // Limpiar las line edits
    ui->lineEdit_2_top1fecha->clear();
    ui->lineEdit_3_top2fecha->clear();
    ui->lineEdit_4_top3fecha->clear();

    // Mostrar las 3 fechas principales
    for (size_t i = 0; i < 3 && i < fechasConConteo.size(); ++i) {
        QString fecha = QString::fromStdString(fechasConConteo[i].first);
        switch (i) {
        case 0:
            ui->lineEdit_2_top1fecha->setText(fecha);
            break;
        case 1:
            ui->lineEdit_3_top2fecha->setText(fecha);
            break;
        case 2:
            ui->lineEdit_4_top3fecha->setText(fecha);
            break;
        }
    }
}

void Userwindow::contarPublicacionesPorFecha(Node* usuario, std::map<std::string, int>& conteoFechas) {
    if (!usuario || !usuario->publicaciones) return;

    // Recorre el árbol y cuenta por fecha
    contarPublicacionesPorFechaNodo(usuario->publicaciones->root, conteoFechas);
}

void Userwindow::contarPublicacionesPorFechaNodo(NodeBST* nodo, std::map<std::string, int>& conteoFechas) {
    if (!nodo) return; // Si el nodo es nulo, retorna.

    contarPublicacionesPorFechaNodo(nodo->left, conteoFechas); // Recorrido a la izquierda

    // Asumiendo que 'publicaciones' es una lista enlazada de publicaciones
    FechaNodo* temp = nodo->publicaciones.head; // Acceder a la lista de publicaciones

    // Contar las publicaciones en la lista para esta fecha
    int conteo = 0;
    while (temp != nullptr) {
        conteo++;
        temp = temp->next; // Avanza al siguiente nodo
    }

    // Incrementa el conteo de publicaciones para la fecha del nodo
    conteoFechas[nodo->fecha] += conteo; // Acumula el total de publicaciones por fecha

    contarPublicacionesPorFechaNodo(nodo->right, conteoFechas); // Recorrido a la derecha
}

void Userwindow::on_pushButton_2_eliminar_clicked() {
    if (usuarioActual == nullptr) {
        QMessageBox::warning(this, "Error", "No hay usuario actual para eliminar.");
        return;
    }

    // Confirmar si el usuario quiere eliminar su cuenta
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmar Eliminación",
                                  "¿Está seguro de que desea eliminar su cuenta?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Eliminar el usuario del árbol AVL
        usuariosAVL->eliminarPorCorreo(usuarioActual->correo);

        QMessageBox::information(this, "Cuenta Eliminada", "Tu cuenta ha sido eliminada exitosamente.");

        // Cerrar la ventana actual o redirigir a la ventana de inicio de sesión, etc.
        this->close();
    }
}


void Userwindow::on_pushButton_6_verArbol_clicked()
{
    // Verificar si el árbol de comentarios está inicializado
    if (comentariosTree == nullptr) {
        QMessageBox::warning(this, "Error", "El árbol de comentarios no está inicializado.");
        return;
    }

    // Generar el archivo .dot para el árbol B
    std::string nombreArchivoDot = "arbolB.dot";
    comentariosTree->graficar(nombreArchivoDot);

    // Generar la imagen PNG a partir del archivo .dot
    std::string nombreArchivoImagen = "arbolB.png";
    std::string comando = "dot -Tpng " + nombreArchivoDot + " -o " + nombreArchivoImagen;
    int resultCode = system(comando.c_str()); // Ejecutar el comando

    // Verificar si el comando se ejecutó correctamente
    if (resultCode != 0) {
        QMessageBox::warning(this, "Error", "No se pudo generar la gráfica del árbol B.");
        return;
    }

    // Mostrar la imagen en una nueva ventana
    ImageWindow *imageWindow = new ImageWindow(QString::fromStdString(nombreArchivoImagen));
    imageWindow->setWindowTitle("Árbol B de Comentarios");
    imageWindow->resize(800, 600);
    imageWindow->show();
}

