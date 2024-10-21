#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "avltree.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent, AVLTree *usuarios, DoubleList* publicacionesList, BinarySearchTree *existingBST)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , usuariosAVL(usuarios)
    , publicacionesList(publicacionesList)
    , bst(existingBST)
{
    ui->setupUi(this);
    qDebug() << "Dirección de usuariosAVL en MainWindow:" << usuariosAVL;
    adminwindow = new AdminWindow(nullptr, usuariosAVL, bst);
    userwindow = nullptr;

    cargarUsuariosDesdeArchivos(); // Cargar usuarios desde archivos
}

MainWindow::~MainWindow()
{
    delete ui;
    delete adminwindow;
    delete userwindow;
}

// Función para eliminar espacios en blanco al inicio y final de una cadena
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return ""; // Solo espacios en blanco
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Método para cargar usuarios desde archivos .edd
void MainWindow::cargarUsuariosDesdeArchivos() {
    QDir dir(QDir::currentPath());
    QStringList filters;
    filters << "*.edd";
    qDebug("Buscando archivos .edd...");

    foreach (QString file, dir.entryList(filters)) {
        qDebug() << "Archivo encontrado:" << file;
        QFile inputFile(file);
        if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Error al abrir el archivo:" << file;
            continue; // Saltar este archivo
        }

        QTextStream in(&inputFile);
        QString originalData; // Para almacenar los datos originales
        QString compressedData; // Para almacenar los datos comprimidos
        std::unordered_map<std::string, char> huffmanCodes; // Mapa para los códigos de Huffman

        // Leer el primer línea (los datos originales)
        if (!in.atEnd()) {
            originalData = in.readLine();
        }

        // Leer los datos comprimidos
        if (!in.atEnd()) {
            compressedData = in.readLine();
            qDebug() << "Datos comprimidos leídos del archivo:" << compressedData;
        }

        // Leer los códigos de Huffman
        while (!in.atEnd()) {
            QString line = in.readLine();
            char ch = line[0].toLatin1(); // Convertir el primer caracter a char
            std::string code = line.mid(2).toStdString();
            huffmanCodes[code] = ch; // Se guarda el código y símbolo
        }

        // Utilizar los códigos para descomprimir
        Huffman huffman;
        huffman.buildHuffmanTree(originalData.toStdString());

        // Descomprimir los datos
        std::string decompressedData = huffman.decompress(compressedData.toStdString(), huffmanCodes);
        qDebug() << "Datos descomprimidos: " << QString::fromStdString(decompressedData);

        // Procesar la información...
        std::vector<std::string> userInfo;
        std::istringstream ss(decompressedData);
        std::string item;
        while (std::getline(ss, item, ',')) {
            userInfo.push_back(trim(item)); // Aplicando trim a cada elemento para eliminar espacios
            qDebug() << "Elemento descomprimido:" << QString::fromStdString(userInfo.back());
        }

        // Agregar al árbol AVL
        if (userInfo.size() == 5) {
            int emptyFields = 0;
            for (const auto& info : userInfo) {
                if (info.empty()) {
                    emptyFields++;
                }
            }
            if (emptyFields > 0) {
                qDebug() << "Error: Se encontraron" << emptyFields << "campos vacíos en la información de usuario.";
                continue; // Saltar este usuario
            }

            usuariosAVL->insert(userInfo[0], userInfo[1], userInfo[2], userInfo[3], userInfo[4]);
            qDebug() << "Usuario cargado:" << QString::fromStdString(userInfo[3]);
        } else {
            qDebug() << "Error: La información descomprimida no tiene 5 elementos.";
        }
    }
}

void MainWindow::on_pushButton_Login_clicked()
{
    QString qCorreo = ui->lineEdit_Usuario->text();
    QString qPassword = ui->lineEdit_2_Password->text();

    std::string correo = qCorreo.toStdString();
    std::string password = qPassword.toStdString();

    if (correo == "admin@gmail.com" && password == "EDD2S2024") {
        QMessageBox::information(this, "Alerta", "Inicio de sesión como administrador exitoso");
        adminwindow->show();
        this->hide();
    } else if (usuariosAVL && usuariosAVL->verificarCredenciales(correo, password)) {
        Node* usuarioBuscado = usuariosAVL->buscarPorCorreo(correo);
        if(usuarioBuscado) {
            QMessageBox::information(this, "Alerta", "Inicio de sesión como usuario exitoso");
            userwindow = new Userwindow(this, usuariosAVL, usuarioBuscado, publicacionesList, bst, adminwindow->comentariosTree);
            userwindow->show();
            this->hide();
        }
    } else {
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
