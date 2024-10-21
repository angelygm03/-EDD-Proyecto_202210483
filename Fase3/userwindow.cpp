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
#include "adjacencylist.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

Userwindow::Userwindow(QWidget *parent, AVLTree *usuariosAVL, Node *usuarioActual, DoubleList* publicacionesList, BinarySearchTree *bst, ArbolB* comentariosTree)
    : QMainWindow(parent),
    ui(new Ui::Userwindow),
    usuariosAVL(usuariosAVL),
    bst(bst),
    pilaSolicitudes(nullptr),
    usuarioActual(usuarioActual),
    publicaciones(publicacionesList),
    comentariosTree(comentariosTree)
{
    ui->setupUi(this);
        connect(ui->pushButton_actualizarDatos, &QPushButton::clicked, this, &Userwindow::on_pushButton_actualizarDatos_clicked);
    if (usuarioActual != nullptr) {
        this->bst = usuarioActual->publicaciones;
        qDebug() << "Usuario logeado:" << QString::fromStdString(usuarioActual->correo);
        qDebug() << "BST inicializado con publicaciones:" << (bst != nullptr ? "Sí" : "No");
        // Mostrar la información del usuario logeado
        ui->lineEdit_2_nombreUsuario->setText(QString::fromStdString(usuarioActual->nombres));
        ui->lineEdit_3_apellidosUsuario->setText(QString::fromStdString(usuarioActual->apellidos));
        ui->lineEdit_4_correoUsuario->setText(QString::fromStdString(usuarioActual->correo));
        ui->lineEdit_5_fechanacUsuario->setText(QString::fromStdString(usuarioActual->fechaNacimiento));
        ui->lineEdit_6_contrasena->setText(QString::fromStdString(usuarioActual->contrasena));

        // Llenar la pila de solicitudes del usuario actual
        pilaSolicitudes = &usuarioActual->solicitudes;
        populateSolicitudesTable();

        // Llenar el listWidget_publicaciones con las publicaciones del árbol
        populatePublicacionesList();

        //Llena la tabla de las sugerencias de amistad
        mostrarSugerenciasDeAmistad();

        //Mostrar el grafo de las relaciones al iniciar sesión
        graficarRelaciones();
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

    if (usuarioActual != nullptr) {
        // Añadir el emisor a la lista de amigos del receptor (usuarioActual)
        usuarioActual->friends.addFriend(emisor.toStdString());
        QMessageBox::information(this, "Amigos", "¡Ahora son amigos!");

        // Añadir el receptor a la lista de amigos del emisor en el árbol AVL
        Node* usuarioEmisor = usuariosAVL->buscarPorCorreo(emisor.toStdString());
        if (usuarioEmisor != nullptr) {
            usuarioEmisor->friends.addFriend(usuarioActual->correo); // Añadir el receptor a la lista de amigos del emisor
            cout << "Amistad aceptada: " << emisor.toStdString() << " añadido a la lista de amigos de " << usuarioActual->correo << endl;
            // Crear la conexión en el grafo
            usuarioActual->adjacencyList->createConnection(usuarioActual->correo, emisor.toStdString());
            usuarioEmisor->adjacencyList->createConnection(emisor.toStdString(), usuarioActual->correo);
            cout << "Amistad aceptada: " << usuarioActual->correo << " añadido al grafo de amigos de " << emisor.toStdString() << endl;
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

void Userwindow::on_pushButton_clicked() {
    // Verifica si hay un usuario actual antes de intentar guardar la información
    if (usuarioActual != nullptr) {
        qDebug() << "Guardando información del usuario actual.";
        Huffman huffman;

        // Construir la cadena de datos
        std::string userData = usuarioActual->nombres +", "+
                               usuarioActual->apellidos +", "+
                               usuarioActual->fechaNacimiento +", "+
                               usuarioActual->correo + "," +
                               usuarioActual->contrasena;

        qDebug() << "Datos del usuario antes de comprimir:" << QString::fromStdString(userData);

        // Construir el árbol de Huffman y obtener los códigos de Huffman
        huffman.buildHuffmanTree(userData);
        auto huffmanCodes = huffman.getHuffmanCodes();
        std::string compressedData = huffman.compress(userData, huffmanCodes);

        // Verificar el tamaño de los datos comprimidos
        qDebug() << "Datos comprimidos, tamaño:" << compressedData.size() << " bytes.";

        // Guardar el archivo
        std::string fileName = usuarioActual->correo + ".edd";
        qDebug() << "Nombre del archivo a guardar:" << QString::fromStdString(fileName);

        std::ofstream outFile(fileName, std::ios::binary);
        if (outFile.is_open()) {
            // nuevo código para almacenar los datos
            outFile << userData << "\n"; // Línea con datos no comprimidos
            outFile << compressedData << "\n"; // Datos comprimidos
            for (const auto& pair : huffmanCodes) {
                outFile << pair.first << ":" << pair.second << "\n"; // Se guardan los códigos de Huffman
            }
            outFile.close();
            qDebug() << "Información guardada en" << QString::fromStdString(fileName);
        } else {
            qDebug() << "No se pudo abrir el archivo para guardar la información.";
        }

        // Liberar la memoria
        delete usuarioActual;
        usuarioActual = nullptr;
    } else {
        qDebug() << "No hay usuario actual para guardar la información.";
    }

    MainWindow *mainWindow = qobject_cast<MainWindow*>(QApplication::activeWindow());
    if (!mainWindow) {
        mainWindow = new MainWindow(nullptr, usuariosAVL);
    }
    mainWindow->show();
    this->close();
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
    cout << "Solicitud enviada a " << usuarioReceptor->correo << endl;

    // Agregar la solicitud a la lista de solicitudes enviadas del emisor (usuarioActual)
    usuarioActual->solicitudListEnviadas.insert(usuarioActual->correo, usuarioReceptor->correo, "PENDIENTE");
    cout << "Solicitud añadida a la lista de solicitudes enviadas de " << usuarioActual->correo << endl;

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
    string imagenUsuario = usuarioActual->publicaciones->graficarArbol("publicaciones_" + usuarioActual->correo);

    // Ahora graficamos las publicaciones de los amigos
    FriendNode* currentFriend = usuarioActual->friends.head;
    while (currentFriend != nullptr) {
        Node* amigoNode = usuariosAVL->buscarPorCorreo(currentFriend->friendEmail);
        if (amigoNode != nullptr && amigoNode->publicaciones != nullptr) {
            string imagenAmigo = amigoNode->publicaciones->graficarArbol("publicaciones_" + amigoNode->correo);
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

void Userwindow::mostrarPublicacionesDelUsuario(const string& userEmail) {
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
void Userwindow::mostrarPublicacionesPorFecha(NodeBST* nodo, const string& userEmail) {
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

NodeBST* Userwindow::buscarNodoPorFecha(NodeBST* node, const string& fecha) {
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
    cout << "Fecha: " << node->fecha << endl; // Imprimir la fecha
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
        cout << "Se encontró un nodo para la fecha: " << fechaStr.toStdString() << endl;
        mostrarPublicacionesEnListWidget(nodoFecha);
    } else {
        cout << "No se encontró un nodo para la fecha: " << fechaStr.toStdString() << endl;
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
    string nombreArchivoDot = "arbolB.dot";
    comentariosTree->graficar(nombreArchivoDot);

    string nombreArchivoImagen = "arbolB.png";
    string comando = "dot -Tpng " + nombreArchivoDot + " -o " + nombreArchivoImagen;
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

    map<string, int> conteoFechas;

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
    vector<pair<string, int>> fechasConConteo(conteoFechas.begin(), conteoFechas.end());

    // Ordenar por conteo (más publicaciones primero)
    sort(fechasConConteo.begin(), fechasConConteo.end(), [](const auto& a, const auto& b) {
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

void Userwindow::contarPublicacionesPorFecha(Node* usuario, map<string, int>& conteoFechas) {
    if (!usuario || !usuario->publicaciones) return;

    // Recorre el árbol y cuenta por fecha
    contarPublicacionesPorFechaNodo(usuario->publicaciones->root, conteoFechas);
}

void Userwindow::contarPublicacionesPorFechaNodo(NodeBST* nodo, map<string, int>& conteoFechas) {
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


void Userwindow::on_pushButton_6_verArbol_clicked()
{
    // Verificar si el árbol de comentarios está inicializado
    if (comentariosTree == nullptr) {
        QMessageBox::warning(this, "Error", "El árbol de comentarios no está inicializado.");
        return;
    }

    // Generar el archivo .dot para el árbol B
    string nombreArchivoDot = "arbolB.dot";
    comentariosTree->graficar(nombreArchivoDot);

    // Generar la imagen PNG a partir del archivo .dot
    string nombreArchivoImagen = "arbolB.png";
    string comando = "dot -Tpng " + nombreArchivoDot + " -o " + nombreArchivoImagen;
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


void Userwindow::on_pushButton_actualizarDatos_clicked()
{
    if (usuarioActual == nullptr) {
        QMessageBox::warning(this, "Error", "No hay usuario actual para actualizar.");
        return;
    }

    QString nuevoNombre = ui->lineEdit_2_nombreUsuario->text();
    QString nuevosApellidos = ui->lineEdit_3_apellidosUsuario->text();
    QString nuevaFechaNac = ui->lineEdit_5_fechanacUsuario->text();
    QString nuevaContrasena = ui->lineEdit_6_contrasena->text();

    // Imprimir los valores leídos para verificar
    qDebug() << "Valores leídos:";
    qDebug() << "Nombre:" << nuevoNombre;
    qDebug() << "Apellidos:" << nuevosApellidos;
    qDebug() << "Fecha de Nacimiento:" << nuevaFechaNac;
    qDebug() << "Contraseña:" << nuevaContrasena;

    bool actualizado = false;

    // Comparar y actualizar solo si hay cambios
    if (QString::fromStdString(usuarioActual->nombres) != nuevoNombre) {
        usuarioActual->nombres = nuevoNombre.toStdString();
        actualizado = true;
        qDebug() << "Nombre actualizado.";
    }
    if (QString::fromStdString(usuarioActual->apellidos) != nuevosApellidos) {
        usuarioActual->apellidos = nuevosApellidos.toStdString();
        actualizado = true;
        qDebug() << "Apellidos actualizados.";
    }
    if (QString::fromStdString(usuarioActual->fechaNacimiento) != nuevaFechaNac) {
        usuarioActual->fechaNacimiento = nuevaFechaNac.toStdString();
        actualizado = true;
        qDebug() << "Fecha de nacimiento actualizada.";
    }
    if (QString::fromStdString(usuarioActual->contrasena) != nuevaContrasena) {
        usuarioActual->contrasena = nuevaContrasena.toStdString();
        actualizado = true;
        qDebug() << "Contraseña actualizada.";
    }

    // Muestra el mensaje según el estado de 'actualizado'
    if (actualizado) {
        qDebug() << "Actualizando información en el AVL.";
        usuariosAVL->eliminarPorCorreo(usuarioActual->correo);
        usuariosAVL->insert(usuarioActual->nombres, usuarioActual->apellidos,
                            usuarioActual->fechaNacimiento, usuarioActual->correo,
                            usuarioActual->contrasena);
        QMessageBox::information(this, "Actualización exitosa", "La información de usuario ha sido actualizada.");
    } else {
        qDebug() << "No se realizaron cambios.";
    }
}

// Método para mostrar sugerencias de amistad
void Userwindow::mostrarSugerenciasDeAmistad() {
    if (!usuarioActual || !usuariosAVL) {
        QMessageBox::warning(this, "Error", "El usuario actual o la estructura de usuarios no están inicializados.");
        return;
    }

    ui->tableWidget_sugerencias->setRowCount(0); // Limpiar la tabla de sugerencias
    unordered_map<string, int> sugerencias; // Mapa para contar amigos en común

    // Conjunto para evitar sugerencias duplicadas
    unordered_set<string> amigosActuales;
    for (FriendNode* f = usuarioActual->friends.head; f != nullptr; f = f->next) {
        amigosActuales.insert(f->friendEmail);
    }

    // Recorrer amigos del usuario actual
    for (FriendNode* f = usuarioActual->friends.head; f != nullptr; f = f->next) {
        Node* amigo = usuariosAVL->buscarPorCorreo(f->friendEmail);
        if (!amigo) continue; // Si no se encuentra el amigo (por algún motivo)

        // Ahora recorrer los amigos del amigo
        for (FriendNode* amigoDeAmigo = amigo->friends.head; amigoDeAmigo != nullptr; amigoDeAmigo = amigoDeAmigo->next) {
            // Ignorar si el amigo de amigo es el mismo usuario actual o ya es amigo
            if (amigosActuales.count(amigoDeAmigo->friendEmail) || amigoDeAmigo->friendEmail == usuarioActual->correo) {
                continue;
            }

            // Si el amigo de amigo no está en el mapa de sugerencias, inicializarlo
            if (sugerencias.find(amigoDeAmigo->friendEmail) == sugerencias.end()) {
                sugerencias[amigoDeAmigo->friendEmail] = 0;
            }

            // Contar amigos en común
            sugerencias[amigoDeAmigo->friendEmail]++;
        }
    }

    // Convertir a un vector para poder ordenar
    vector<pair<string, int>> sugerenciasOrdenadas(sugerencias.begin(), sugerencias.end());

    // Ordenar las sugerencias desde la más alta a la más baja en base a amigos en común
    sort(sugerenciasOrdenadas.begin(), sugerenciasOrdenadas.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Ordenar en orden descendente
    });

    // Llenar el QTableWidget
    for (const auto& sugerencia : sugerenciasOrdenadas) {
        const string& correoSugerido = sugerencia.first;
        const int amigosEnComun = sugerencia.second;

        Node* usuarioSugerido = usuariosAVL->buscarPorCorreo(correoSugerido);
        if (usuarioSugerido) {
            int rowCount = ui->tableWidget_sugerencias->rowCount();
            ui->tableWidget_sugerencias->insertRow(rowCount);

            // Mostrar el nombre y apellido del usuario sugerido
            ui->tableWidget_sugerencias->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(usuarioSugerido->nombres)));
            ui->tableWidget_sugerencias->setItem(rowCount, 1, new QTableWidgetItem(QString::fromStdString(usuarioSugerido->apellidos)));
            ui->tableWidget_sugerencias->setItem(rowCount, 2, new QTableWidgetItem(QString::number(amigosEnComun))); // Amigos en común

            // Crear botón para enviar solicitud
            QPushButton* botonSolicitud = new QPushButton("Agregar");
            connect(botonSolicitud, &QPushButton::clicked, [this, correoSugerido, usuarioSugerido]() {
                // Agregar la solicitud a la pila del receptor
                usuarioSugerido->solicitudes.push(usuarioActual->correo, correoSugerido, "PENDIENTE");
                cout << "Solicitud enviada a " << correoSugerido << endl;

                // Agregar la solicitud a la lista de solicitudes enviadas del emisor (usuarioActual)
                usuarioActual->solicitudListEnviadas.insert(usuarioActual->correo, correoSugerido, "PENDIENTE");
                cout << "Solicitud añadida a la lista de solicitudes enviadas de " << usuarioActual->correo << endl;

                QMessageBox::information(this, "Solicitud Enviada", "Se ha enviado la solicitud de amistad correctamente.");

                // Eliminar la sugerencia de la tabla
                int rowCount = ui->tableWidget_sugerencias->rowCount();
                ui->tableWidget_sugerencias->removeRow(rowCount);
            });

            ui->tableWidget_sugerencias->setCellWidget(rowCount, 3, botonSolicitud);
        }
    }
}

void Userwindow::graficarRelaciones() {
    if (!usuarioActual) {
        QMessageBox::warning(this, "Error", "No hay usuario actual.");
        return;
    }

    string dotFileName = "grafo_relaciones.dot";
    ofstream out(dotFileName);

    if (!out) {
        QMessageBox::warning(this, "Error", "No se pudo crear el archivo para el grafo.");
        return;
    }

    out << "graph G {\n";
    out << "node [shape=circle];\n";

    // Agregar al usuario actual
    out << "\"" << usuarioActual->correo << "\" [label=\"" << usuarioActual->nombres << "\", color=\"blue\"];\n";

    // Agregar amigos
    unordered_set<string> amigosActuales;
    for (FriendNode* f = usuarioActual->friends.head; f != nullptr; f = f->next) {
        Node* amigo = usuariosAVL->buscarPorCorreo(f->friendEmail);
        if (amigo) {
            out << "\"" << amigo->correo << "\" [label=\"" << amigo->nombres << "\", color=\"orange\"];\n"; // Amigos en azul
            out << "\"" << usuarioActual->correo << "\" -- \"" << amigo->correo << "\";\n"; // Conexión no dirigida
            amigosActuales.insert(amigo->correo);
        }
    }

    // Agregar amigos de amigos
    unordered_set<string> amigosDeAmigos;
    for (FriendNode* f = usuarioActual->friends.head; f != nullptr; f = f->next) {
        Node* amigo = usuariosAVL->buscarPorCorreo(f->friendEmail);
        if (!amigo) continue;

        for (FriendNode* amigoDeAmigo = amigo->friends.head; amigoDeAmigo != nullptr; amigoDeAmigo = amigoDeAmigo->next) {
            // Verificar que no sea el usuario actual ni un amigo directo
            if (amigoDeAmigo->friendEmail != usuarioActual->correo && amigosActuales.find(amigoDeAmigo->friendEmail) == amigosActuales.end()) {
                Node* amigoDeAmigoNode = usuariosAVL->buscarPorCorreo(amigoDeAmigo->friendEmail);
                if (amigoDeAmigoNode) {
                    out << "\"" << amigoDeAmigoNode->correo << "\" [label=\"" << amigoDeAmigoNode->nombres << "\", color=\"green\"];\n"; // Amigos de amigos en verde
                    out << "\"" << amigo->correo << "\" -- \"" << amigoDeAmigoNode->correo << "\";\n"; // Conexión no dirigida
                    amigosDeAmigos.insert(amigoDeAmigo->friendEmail);
                }
            }
        }
    }

    // Agregar amigos de amigos de amigos
    for (const string& amigoDeAmigoCorreo : amigosDeAmigos) {
        Node* amigoDeAmigo = usuariosAVL->buscarPorCorreo(amigoDeAmigoCorreo);
        if (!amigoDeAmigo) continue;

        for (FriendNode* amigoDeAmigoDeAmigo = amigoDeAmigo->friends.head; amigoDeAmigoDeAmigo != nullptr; amigoDeAmigoDeAmigo = amigoDeAmigoDeAmigo->next) {
            // Evitar conexiones duplicadas y ya conocidas
            if (amigosActuales.find(amigoDeAmigoDeAmigo->friendEmail) == amigosActuales.end() &&
                amigosDeAmigos.find(amigoDeAmigoDeAmigo->friendEmail) == amigosDeAmigos.end() &&
                amigoDeAmigoDeAmigo->friendEmail != usuarioActual->correo) {
                Node* amigoDeAmigoDeAmigoNode = usuariosAVL->buscarPorCorreo(amigoDeAmigoDeAmigo->friendEmail);
                if (amigoDeAmigoDeAmigoNode) {
                    out << "\"" << amigoDeAmigoDeAmigoNode->correo << "\" [label=\"" << amigoDeAmigoDeAmigoNode->nombres << "\", color=\"black\"];\n"; // Amigos de amigos de amigos en negro
                    out << "\"" << amigoDeAmigoCorreo << "\" -- \"" << amigoDeAmigoDeAmigoNode->correo << "\";\n"; // Conexión no dirigida
                }
            }
        }
    }

    out << "}\n";
    out.close();

    string command = "dot -Tpng -Gdpi=300 " + dotFileName + " -o grafo_relaciones.png";
    if (system(command.c_str()) != 0) {
        QMessageBox::warning(this, "Error", "No se pudo generar la imagen del grafo.");
        return;
    }

    // Mostrar la imagen en graphicsView_grafo
    QImage image("grafo_relaciones.png");
    if (image.isNull()) {
        QMessageBox::warning(this, "Error", "No se pudo cargar la imagen del grafo.");
        return;
    }

    // Escalar la imagen
    QImage scaledImage = image.scaled(ui->graphicsView_grafo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Crear la escena y agregar la imagen
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(scaledImage));
    ui->graphicsView_grafo->setScene(scene);
    ui->graphicsView_grafo->setRenderHint(QPainter::Antialiasing);
}
