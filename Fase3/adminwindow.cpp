#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QMessageBox>
#include "mainwindow.h"
#include "imagewindow.h"
#include "adjacencylist.h"
#include <iostream>

AdminWindow::AdminWindow(QWidget *parent, AVLTree* existingAVL, BinarySearchTree* existingBST)
    : QMainWindow(parent)
    , ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    usuariosAVL = existingAVL;
    publicacionesList = new DoubleList();
    comentariosTree = new ArbolB();
    bst = existingBST;

    // Establecer encabezados de la tabla
    QStringList encabezados;
    encabezados << "Nombre" << "Apellido" << "Correo" << "Nacimiento";
    ui->tableWidget_usuarios->setHorizontalHeaderLabels(encabezados);

    // Ajustar ancho de columnas
    ui->tableWidget_usuarios->setColumnWidth(2, 250);
    ui->tableWidget_usuarios->setColumnWidth(0, 100);
    ui->tableWidget_usuarios->setColumnWidth(1, 100);
    ui->tableWidget_usuarios->setColumnWidth(3, 150);

    // Mensaje de depuración para verificar la inicialización
    qDebug() << "AdminWindow inicializado con usuariosAVL:" << usuariosAVL;
}


AdminWindow::~AdminWindow()
{
    delete publicacionesList;
    delete comentariosTree;
    delete bst;
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
            // Verificar si ya son amigos antes de añadir la solicitud
            if (!usuarioReceptor->friends.esAmigo(emisor)) {
                usuarioReceptor->solicitudes.push(emisor, receptor, estado);
                std::cout << "Solicitud para " << receptor << " de " << emisor << " añadida a la pila del receptor." << std::endl;
            } else {
                std::cout << "No se puede añadir solicitud: " << emisor << " ya es amigo de " << receptor << std::endl;
            }
        }

        // Si el emisor existe y la solicitud está pendiente, agregarla a su lista de enviadas
        if (usuarioEmisor != nullptr && estado == "PENDIENTE") {
            // Agregar la solicitud a la lista de enviadas del emisor solo si no son amigos
            if (!usuarioEmisor->friends.esAmigo(receptor)) {
                usuarioEmisor->solicitudListEnviadas.insert(emisor, receptor, estado);
                std::cout << "Solicitud enviada de " << emisor << " para " << receptor << " añadida a la lista de enviadas del emisor." << std::endl;
            } else {
                std::cout << "No se puede añadir solicitud a la lista de enviadas: " << emisor << " ya es amigo de " << receptor << std::endl;
            }
        }

        // Manejar solicitudes aceptadas
        if (estado == "ACEPTADA") {
            if (usuarioReceptor != nullptr) {
                usuarioReceptor->friends.addFriend(emisor); // Añadir el emisor a la lista de amigos del receptor
                usuarioReceptor->adjacencyList->createConnection(emisor, receptor); // Crear conexión en el grafo
                std::cout << emisor << " añadido a la lista de amigos de " << receptor << std::endl;
            }

            if (usuarioEmisor != nullptr) {
                usuarioEmisor->friends.addFriend(receptor); // Añadir el receptor a la lista de amigos del emisor
                usuarioEmisor->adjacencyList->createConnection(receptor, emisor); // Crear conexión en el grafo
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
        qDebug() << "AdminWindow inicializado con publicaciones:" << bst;

        // Insertar la publicación en la lista doblemente enlazada
        publicacionesList->insertAtEnd(correo.toStdString(), contenido.toStdString(), fecha.toStdString(), hora.toStdString(), imagenPath.toStdString());

        // Buscar el usuario en el árbol AVL por correo
        Node* usuario = usuariosAVL->buscarPorCorreo(correo.toStdString());
        if (usuario) {
            usuario->publicaciones->insertarPublicacion(fecha.toStdString(), correo.toStdString(), contenido.toStdString(), hora.toStdString());
            // Insertar la publicación en el BST
            bst->insertarPublicacion(fecha.toStdString(), correo.toStdString(), contenido.toStdString(), hora.toStdString());
        }

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
    QMessageBox::information(this, "Éxito", "Publicaciones cargadas exitosamente.");
    // Imprimir publicaciones y comentarios después de cargar
    publicacionesList->print();
    comentariosTree->imprimir();
}


void AdminWindow::on_pushButton_clicked() {
    MainWindow *mainWindow = qobject_cast<MainWindow*>(QApplication::activeWindow());
    if (!mainWindow) {
        mainWindow = new MainWindow(nullptr, usuariosAVL, publicacionesList, bst); // Reutilizar usuariosAVL
    }
    mainWindow->show();
    this->close();
}

void AdminWindow::on_pushButton_2_buscar_clicked()
{
    QString correoBuscado = ui->lineEdit_correo->text().trimmed(); // Obtenemos el texto del lineEdit y eliminamos espacios
    QString selectedOrder = ui->comboBox_orden->currentText();

    // Limpiar la tabla antes de mostrar nuevos resultados
    ui->tableWidget_usuarios->clearContents();
    ui->tableWidget_usuarios->setRowCount(0); // Asegúrate de vaciar la tabla completamente

    int fila = 0;

    if (correoBuscado.isEmpty()) {
        // Si el correo está vacío, hacer la búsqueda según el orden seleccionado
        if (selectedOrder == "Ninguno") {
            return; // No hacemos nada
        } else if (selectedOrder == "Preorden") {
            usuariosAVL->preorden(usuariosAVL->root, ui->tableWidget_usuarios, fila);
        } else if (selectedOrder == "Inorden") {
            usuariosAVL->inorden(usuariosAVL->root, ui->tableWidget_usuarios, fila);
        } else if (selectedOrder == "Postorden") {
            usuariosAVL->postorden(usuariosAVL->root, ui->tableWidget_usuarios, fila);
        }
    } else {
        // Si hay un correo, buscar el usuario específico
        Node* usuario = usuariosAVL->buscarPorCorreo(correoBuscado.toStdString());
        if (usuario != nullptr) {
            // Si se encontró al usuario, agregar su información a la tabla
            ui->tableWidget_usuarios->insertRow(fila);
            ui->tableWidget_usuarios->setItem(fila, 0, new QTableWidgetItem(QString::fromStdString(usuario->nombres)));
            ui->tableWidget_usuarios->setItem(fila, 1, new QTableWidgetItem(QString::fromStdString(usuario->apellidos)));
            ui->tableWidget_usuarios->setItem(fila, 2, new QTableWidgetItem(QString::fromStdString(usuario->correo)));
            ui->tableWidget_usuarios->setItem(fila, 3, new QTableWidgetItem(QString::fromStdString(usuario->fechaNacimiento)));

            // Centrar el texto en las celdas
            for (int i = 0; i < 4; i++) {
                QTableWidgetItem* item = ui->tableWidget_usuarios->item(fila, i);
                if (item) {
                    item->setTextAlignment(Qt::AlignCenter);
                }
            }
        } else {
            // Si no se encuentra el usuario, se puede mostrar un mensaje
            QMessageBox::warning(this, "Usuario no encontrado", "No se encontró un usuario con el correo proporcionado.");
        }
    }
}

void AdminWindow::on_actionUsuarios_triggered()
{
    usuariosAVL->graph();
    ImageWindow *imageWindow = new ImageWindow("avltree.png", this);
    imageWindow->setWindowTitle("Árbol AVL de Usuarios");
    imageWindow->resize(800, 600);
    imageWindow->show();
}


void AdminWindow::on_actionPublicaciones_triggered()
{
    publicacionesList->generateDotFile();
    ImageWindow *imageWindow = new ImageWindow("reportePublicaciones.png", this);
    imageWindow->setWindowTitle("Gráfico de Publicaciones");
    imageWindow->resize(800, 600);
    imageWindow->show();
}


void AdminWindow::on_actionReporte_Comentarios_triggered()
{

}


void AdminWindow::on_actionLista_de_amistades_triggered()
{
    // Verificamos si el árbol AVL tiene algún usuario
    if (!usuariosAVL->root) {
        QMessageBox::warning(this, "Error", "No hay usuarios disponibles.");
        qDebug() << "El árbol AVL está vacío. No se pueden generar listas de adyacencia.";
        return;
    }

    // Variables para la generación de archivos .dot y .png
    std::string filename = "adjacency_list";

    // Generar la lista de adyacencia para todos los usuarios
    qDebug() << "Generando lista de adyacencia...";
    generateAdjacencyListGraph(usuariosAVL->root, filename);

    // Asegurar que los archivos `.png` se generaron antes de mostrar
    QString filePath = QString::fromStdString(filename) + ".png"; // Cambiar esto por el nombre real que generaste

    // Verificar si el archivo fue creado
    QFileInfo checkFile(filePath);
    if (!checkFile.exists() || !checkFile.isFile()) {
        QMessageBox::warning(this, "Error", "No se pudo generar el gráfico de la lista de adyacencia.");
        qDebug() << "No se encontró el archivo:" << filePath;
        return;
    }

    // Mostrar la imagen generada
    qDebug() << "Mostrando la imagen generada.";
    ImageWindow *imageWindow = new ImageWindow(filePath, this);
    imageWindow->setWindowTitle("Lista de Adyacencia");
    imageWindow->resize(800, 600);
    imageWindow->show();
}

// Método adicional que se encarga de generar el gráfico de la lista de adyacencia
void AdminWindow::generateAdjacencyListGraph(Node* node, const std::string& filename) {
    // Crear un archivo DOT
    std::ofstream outFile(filename + ".dot");

    if (!outFile.is_open()) {
        qDebug() << "Error al crear el archivo .dot";
        return;
    }

    // Escribir el encabezado del archivo DOT
    outFile << "digraph adjacency_list {\n";
    outFile << "rankdir=LR;\n";

    // Recorrer el árbol y agregar nodos y conexiones
    traverseAndGraph(node, outFile);

    // Escribir el pie del archivo DOT
    outFile << "}\n";
    outFile.close();
    qDebug() << "Archivo DOT generado:" << QString::fromStdString(filename) + ".dot";

    // Generar la imagen a partir del archivo DOT
    std::string command = "dot -Tpng " + filename + ".dot -o " + filename + ".png";
    int result = system(command.c_str());

    if (result != 0) {
        qDebug() << "Ocurrió un error al generar la imagen.";
    } else {
        qDebug() << "La imagen fue generada exitosamente.";
    }
}

// Método auxiliar que recorre el árbol AVL y grafica los nodos
void AdminWindow::traverseAndGraph(Node* node, std::ofstream& outFile) {
    if (node == nullptr) {
        return;
    }

    // Agregar el nodo actual
    outFile << "\"" << node->correo << "\" [label=\"" << node->nombres << " " << node->apellidos << "\"];\n";

    // Graficar la lista de adyacencia del usuario
    if (node->adjacencyList) {
        qDebug() << "Procesando lista de adyacencia para el usuario:" << QString::fromStdString(node->nombres);
        UserNode* currentUserNode = node->adjacencyList->head;
        while (currentUserNode) {
            Neighbor* currentNeighbor = currentUserNode->neighbors;
            while (currentNeighbor) {
                outFile << "\"" << currentUserNode->userName << "\" -> \"" << currentNeighbor->friendName << "\" [dir=\"both\"];\n";
                currentNeighbor = currentNeighbor->next;
            }
            currentUserNode = currentUserNode->next;
        }
    } else {
        qDebug() << "No se encontró lista de adyacencia para el usuario:" << QString::fromStdString(node->nombres);
    }

    // Recorrer el árbol en inorden para continuar con otros nodos
    traverseAndGraph(node->left, outFile);
    traverseAndGraph(node->right, outFile);
}

void AdminWindow::on_actionGrafo_de_amistades_triggered() {
    // Verificamos si el árbol AVL tiene algún usuario
    if (!usuariosAVL->root) {
        QMessageBox::warning(this, "Error", "No hay usuarios disponibles.");
        qDebug() << "El árbol AVL está vacío. No se pueden generar el grafo de amistades.";
        return;
    }

    // Variables para la generación de archivos .dot y .png
    std::string filename = "friendship_graph";

    // Generar el grafo de amistades
    qDebug() << "Generando grafo de amistades...";
    generateFriendshipGraph(usuariosAVL->root, filename);

    // Asegurar que los archivos `.png` se generaron antes de mostrar
    QString filePath = QString::fromStdString(filename) + ".png";

    // Verificar si el archivo fue creado
    QFileInfo checkFile(filePath);
    if (!checkFile.exists() || !checkFile.isFile()) {
        QMessageBox::warning(this, "Error", "No se pudo generar el grafo de amistades.");
        qDebug() << "No se encontró el archivo:" << filePath;
        return;
    }

    // Mostrar la imagen generada
    qDebug() << "Mostrando la imagen generada del grafo de amistades.";
    ImageWindow *imageWindow = new ImageWindow(filePath, this);
    imageWindow->setWindowTitle("Grafo de Amistades");
    imageWindow->resize(800, 600);
    imageWindow->show();
}

// Método adicional que se encarga de generar el gráfico del grafo de amistades
void AdminWindow::generateFriendshipGraph(Node* node, const std::string& filename) {
    // Crear un archivo DOT
    std::ofstream outFile(filename + ".dot");

    if (!outFile.is_open()) {
        qDebug() << "Error al crear el archivo .dot para el grafo de amistades.";
        return;
    }

    // Escribir el encabezado del archivo DOT
    outFile << "graph friendship_graph {\n";
    outFile << "node [shape=circle];\n";  // Cambia el aspecto del nodo si es necesario

    // Recorrer el árbol y agregar nodos y conexiones
    traverseAndGraphFriendships(node, outFile);

    // Escribir el pie del archivo DOT
    outFile << "}\n";
    outFile.close();
    qDebug() << "Archivo DOT del grafo de amistades generado:" << QString::fromStdString(filename) + ".dot";

    // Generar la imagen a partir del archivo DOT
    std::string command = "dot -Tpng " + filename + ".dot -o " + filename + ".png";
    int result = system(command.c_str());

    if (result != 0) {
        qDebug() << "Ocurrió un error al generar la imagen del grafo de amistades.";
    } else {
        qDebug() << "La imagen del grafo de amistades fue generada exitosamente.";
    }
}

// Método auxiliar que recorre el árbol AVL y grafica las amistades
void AdminWindow::traverseAndGraphFriendships(Node* node, std::ofstream& outFile) {
    if (node == nullptr) {
        return;
    }

    // Agregar el nodo actual
    outFile << "\"" << node->correo << "\" [label=\"" << node->nombres << " " << node->apellidos << "\"];\n";

    // Graficar las amistades del usuario
    if (node->adjacencyList) {
        qDebug() << "Procesando amistades para el usuario:" << QString::fromStdString(node->nombres);
        UserNode* currentUserNode = node->adjacencyList->head;
        while (currentUserNode) {
            Neighbor* currentNeighbor = currentUserNode->neighbors;
            while (currentNeighbor) {
                // Asegurarse de graficar cada conexión entre usuarios
                outFile << "\"" << node->correo << "\" -- \"" << currentNeighbor->friendName << "\";\n";
                currentNeighbor = currentNeighbor->next;
            }
            currentUserNode = currentUserNode->next;
        }
    } else {
        qDebug() << "No se encontró lista de amistades para el usuario:" << QString::fromStdString(node->nombres);
    }

    // Recorrer el árbol en inorden para continuar con otros nodos
    traverseAndGraphFriendships(node->left, outFile);
    traverseAndGraphFriendships(node->right, outFile);
}
