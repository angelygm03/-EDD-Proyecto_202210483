#include "binarysearchtree.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

// Método recursivo para insertar un nodo en el BST
NodeBST* BinarySearchTree::insertar(NodeBST* node, string fecha, string correo, string contenido, string hora) {
    if (node == nullptr) {
        node = new NodeBST(fecha);
    }

    if (fecha == node->fecha) {
        // Si ya existe un nodo con la fecha, se agrega la publicación a la lista de esa fecha
        node->publicaciones.agregarPublicacion(correo, contenido, hora);
    } else if (fecha < node->fecha) {
        node->left = insertar(node->left, fecha, correo, contenido, hora);
    } else {
        node->right = insertar(node->right, fecha, correo, contenido, hora);
    }

    return node;
}

void BinarySearchTree::insertarPublicacion(string fecha, string correo, string contenido, string hora) {
    root = insertar(root, fecha, correo, contenido, hora);
}

// Recorrido en orden del BST para mostrar las publicaciones cronológicamente
void BinarySearchTree::inorder(NodeBST* node) const {
    if (node == nullptr) return;

    inorder(node->left);
    cout << "Fecha: " << node->fecha << endl;
    node->publicaciones.imprimirPublicaciones();
    inorder(node->right);
}

void BinarySearchTree::mostrarPublicacionesEnOrden() const {
    inorder(root);
}

void BinarySearchTree::generarDOT(NodeBST* node, ofstream& archivo) const {
    if (node == nullptr) return;

    // Agregamos el nodo del árbol al archivo DOT
    archivo << "    \"" << node->fecha << "\" [label=\"" << node->fecha << "\"];\n";

    // Si hay publicaciones en la lista, agregamos nodos para cada una
    FechaNodo* temp = node->publicaciones.head;
    int count = 0;
    std::string prevNodo = node->fecha;
    while (temp != nullptr) {
        string publicacionID = node->fecha + "_pub" + to_string(count++);
        archivo << "    \"" << publicacionID << "\" [label=\"" << temp->correo << ": " << temp->contenido << "\\n" << temp->hora << "\", shape=box];\n";
        archivo << "    \"" << prevNodo << "\" -> \"" << publicacionID << "\";\n";  // Relación entre nodo del árbol y publicaciones
        prevNodo = publicacionID;  // El siguiente nodo enlazado
        temp = temp->next;
    }

    // Relación con hijos
    if (node->left != nullptr) {
        archivo << "    \"" << node->fecha << "\" -> \"" << node->left->fecha << "\";\n";
    }
    if (node->right != nullptr) {
        archivo << "    \"" << node->fecha << "\" -> \"" << node->right->fecha << "\";\n";
    }

    // Llamada recursiva para recorrer hijos izquierdo y derecho
    generarDOT(node->left, archivo);
    generarDOT(node->right, archivo);
}

string BinarySearchTree::graficarArbol(const string& filename) {
    string dotFile = filename + ".dot";
    string pngFile = filename + ".png";

    ofstream archivo(dotFile);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir el DOT.\n";
        return "";
    }

    archivo << "digraph G {\n";
    archivo << "    node [fontname=\"Arial\"];\n";

    generarDOT(root, archivo);
    archivo << "}\n";
    archivo.close();

    string comando = "dot -Tpng " + dotFile + " -o " + pngFile;
    if (system(comando.c_str()) != 0) {
        cerr << "Error al ejecutar Graphviz.\n";
        return "";
    }
    return pngFile;
}

void BinarySearchTree::preorder(NodeBST* node) const {
    if (node == nullptr) return;

    cout << "Fecha: " << node->fecha << endl;
    node->publicaciones.imprimirPublicaciones(); // Mostrar publicaciones de esta fecha
    preorder(node->left);
    preorder(node->right);
}

void BinarySearchTree::postorder(NodeBST* node) const {
    if (node == nullptr) return;

    postorder(node->left);
    postorder(node->right);
    cout << "Fecha: " << node->fecha << endl;
    node->publicaciones.imprimirPublicaciones(); // Mostrar publicaciones de esta fecha
}

void BinarySearchTree::mostrarPublicacionesEnPreOrden() const {
    preorder(root);
}

void BinarySearchTree::mostrarPublicacionesEnPostOrden() const {
    postorder(root);
}
