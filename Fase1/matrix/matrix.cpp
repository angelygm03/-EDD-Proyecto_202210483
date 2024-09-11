#include "matrix.h"
#include <fstream>
#include <set>
#include <iostream>
#include <map>

// Constructor
Matrix::Matrix() : head(new MatrixNode("")) {
}

// Destructor
Matrix::~Matrix() {
    MatrixNode* row = head;
    while (row != nullptr) {
        MatrixNode* col = row->right;
        while (col != nullptr) {
            MatrixNode* temp = col;
            col = col->right;
            delete temp;
        }
        MatrixNode* temp = row;
        row = row->down;
        delete temp;
    }
}


// Método para insertar una relación entre dos usuarios
void Matrix::insertarRelacion(Node* usuario1, Node* usuario2) {
    if (usuario1->correo == usuario2->correo) {
        std::cout << "No se puede agregar una relación de un usuario consigo mismo." << std::endl;
        return;
    }

    // Inserción en la fila de usuario2
    MatrixNode* row = head;
    while (row->down != nullptr && row->down->correo != usuario2->correo) {
        row = row->down;
    }
    if (row->down == nullptr || row->down->correo != usuario2->correo) {
        row->down = new MatrixNode(usuario2->correo);
        row = row->down;
    } else {
        row = row->down;
    }

    // Inserción en la columna de usuario1
    MatrixNode* col = row;
    while (col->right != nullptr && col->right->correo != usuario1->correo) {
        col = col->right;
    }
    if (col->right == nullptr || col->right->correo != usuario1->correo) {
        col->right = new MatrixNode(usuario1->correo);
    }

    // Inserción en la fila de usuario1
    row = head;
    while (row->right != nullptr && row->right->correo != usuario1->correo) {
        row = row->right;
    }
    if (row->right == nullptr || row->right->correo != usuario1->correo) {
        row->right = new MatrixNode(usuario1->correo);
        row = row->right;
    } else {
        row = row->right;
    }

    // Inserción en la columna de usuario2
    col = row;
    while (col->down != nullptr && col->down->correo != usuario2->correo) {
        col = col->down;
    }
    if (col->down == nullptr || col->down->correo != usuario2->correo) {
        col->down = new MatrixNode(usuario2->correo);
    }
}


void Matrix::printMatrix() const {
    std::cout << "Imprimiendo la matriz dispersa..." << std::endl;
    MatrixNode* row = head->down;
    while (row != nullptr) {
        std::cout << "Fila de " << row->correo << ": ";
        MatrixNode* col = row->right;
        while (col != nullptr) {
            std::cout << col->correo << " ";
            col = col->right;
        }
        std::cout << std::endl;
        row = row->down;
    }
}



// Método para verificar si dos usuarios son amigos
bool Matrix::sonAmigos(Node* usuario1, Node* usuario2) {
    MatrixNode* row = head;
    while (row != nullptr) {
        if (row->correo == usuario1->correo) {
            MatrixNode* col = row->right;
            while (col != nullptr) {
                if (col->correo == usuario2->correo) {
                    return true;
                }
                col = col->right;
            }
            return false;
        }
        row = row->down;
    }
    return false;
}

// Método para generar el archivo .dot
void Matrix::generateDotFile(const std::string& filename) const {
    ofstream file(filename + ".dot");
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir el .dot" << std::endl;
        return;
    }

    file << "digraph G {\n";
    file << "graph [pad=\"0.5\", nodesep=\"1\", ranksep=\"1\"];\n";
    file << "node [shape=box, height=0.8];\n";

    // Para almacenar las relaciones ya añadidas
    std::set<std::pair<std::string, std::string>> edges;

    // Imprimir nodos y aristas
    MatrixNode* row = head->down;
    while (row != nullptr) {
        MatrixNode* col = row->right;
        while (col != nullptr) {
            // Añadir nodos para filas y columnas usando solo el correo
            file << "\"" << row->correo << "\" [label=\"" << row->correo << "\" style=filled fillcolor=white];\n";
            file << "\"" << col->correo << "\" [label=\"" << col->correo << "\" style=filled fillcolor=white];\n";

            // Añadir una sola arista bidireccional si no existe ya
            auto edge = std::make_pair(row->correo, col->correo);
            auto reverse_edge = std::make_pair(col->correo, row->correo);

            if (edges.find(edge) == edges.end() && edges.find(reverse_edge) == edges.end()) {
                file << "\"" << row->correo << "\" -> \"" << col->correo << "\" [dir=\"both\"];\n";
                edges.insert(edge);
            }

            col = col->right;
        }
        row = row->down;
    }

    file << "}\n";
    file.close();

    // Convertir el archivo .dot a .png automáticamente
    string command = "dot -Tpng " + filename + ".dot -o " + filename + ".png";
    system(command.c_str());

    // Abrir el archivo .png generado
    command = "start " + filename + ".png";
    system(command.c_str());
}


const int MAX_USUARIOS = 100; 

// Método para obtener e imprimir los 5 usuarios con menos amigos
void Matrix::top5MenosAmigos() const {
    std::map<std::string, int> amigoCount;
    
    // Contar el número de amigos para cada usuario
    MatrixNode* row = head->down;
    while (row != nullptr) {
        int count = 0;
        MatrixNode* col = row->right;
        while (col != nullptr) {
            count++;
            col = col->right;
        }
        amigoCount[row->correo] = count;
        row = row->down;
    }

    //arreglo para almacenar los usuarios y sus conteos de amigos
    std::pair<std::string, int> usuarios[MAX_USUARIOS];
    int usuarioCount = 0;

    // Copiar datos del map al arreglo
    for (const auto& pair : amigoCount) {
        if (usuarioCount < MAX_USUARIOS) {
            usuarios[usuarioCount++] = pair;
        }
    }

    // Ordenar el arreglo de menor a mayor usando el algoritmo de ordenación por selección
    for (int i = 0; i < usuarioCount - 1; ++i) {
        for (int j = i + 1; j < usuarioCount; ++j) {
            if (usuarios[j].second < usuarios[i].second) {
                std::swap(usuarios[i], usuarios[j]);
            }
        }
    }

    // Imprimir los 5 usuarios con menos amigos
    int topCount = std::min(5, usuarioCount);
    for (int i = 0; i < topCount; ++i) {
        std::cout << usuarios[i].first << " (" << usuarios[i].second << " amigos)" << std::endl;
    }
}

