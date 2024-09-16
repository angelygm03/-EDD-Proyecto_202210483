#include "avltree.h"
#include <iostream>
#include <fstream>

AVLTree::AVLTree() {
    root = nullptr;
}

void AVLTree::insert(string nombres, string apellidos, string fechaNacimiento,
                     string correo, string contrasena) {
    bool increase = false;
    root = insert(this->root, nombres, apellidos, fechaNacimiento, correo, contrasena, increase);
}

Node* AVLTree::insert(Node* root, string nombres, string apellidos, string fechaNacimiento,
                      string correo, string contrasena, bool increase) {
    if (root == nullptr) {
        std::cout << "Insertando: " << correo << " con contraseña: " << contrasena << std::endl;
        root = new Node(nombres, apellidos, fechaNacimiento, correo, contrasena);
        increase = true;
    } else if (correo < root->correo) {  // Comparar por correo
        root->left = insert(root->left, nombres, apellidos, fechaNacimiento, correo, contrasena, increase);
        // Balanceo del árbol
        if (increase) {
            switch (root->factor) {
            case RIGHT_HEAVY:
                root->factor = 0;
                increase = false;
                break;
            case BALANCED:
                root->factor = LEFT_HEAVY;
                break;
            case LEFT_HEAVY:
                Node* n1 = root->left;
                if (n1->factor == LEFT_HEAVY) {
                    root = l_rotation(root, n1);
                } else {
                    root = lr_rotation(root, n1);
                }
                increase = false;
                break;
            }
        }
    } else if (correo > root->correo) {
        root->right = insert(root->right, nombres, apellidos, fechaNacimiento, correo, contrasena, increase);
        // Balanceo del árbol
        if (increase) {
            Node* n1;
            switch (root->factor) {
            case RIGHT_HEAVY:
                n1 = root->right;
                if (n1->factor == RIGHT_HEAVY) {
                    root = r_rotation(root, n1);
                } else {
                    root = rl_rotation(root, n1);
                }
                increase = false;
                break;
            case BALANCED:
                root->factor = RIGHT_HEAVY;
                break;
            case LEFT_HEAVY:
                root->factor = 0;
                increase = false;
                break;
            }
        }
    }
    return root;
}

Node* AVLTree::l_rotation(Node* n, Node* n1){
    n->left = n1->right;
    n1->right = n;

    n->factor = 0;
    n1->factor = 0;
    return n1;
}
Node* AVLTree::r_rotation(Node* n, Node* n1){
    n->right = n1->left;
    n1->left = n;

    n->factor = 0;
    n1->factor = 0;
    return n1;
}
Node* AVLTree::rl_rotation(Node* n, Node* n1){
    Node* n2 = n1->left;

    n1->left = n2->right;
    n2->right = n1;
    n->right = n2->left;
    n2->left = n;

    n2->factor = 0;
    n1->factor = 0;
    n->factor = 0;
    return n2;
}
Node* AVLTree::lr_rotation(Node* n, Node* n1){
    Node* n2 = n1->right;

    n1->right = n2->left;
    n2->left = n1;
    n->left = n2->right;
    n2->right = n;

    n2->factor = 0;
    n1->factor = 0;
    n->factor = 0;
    return n2;
}


void AVLTree::graph() {
    std::ofstream outfile("avltree.dot");
    outfile << "digraph G {" << std::endl;

    if (root != nullptr) {
        graph(root, outfile);
    }

    outfile << "}" << std::endl;
    outfile.close();
    int returnCode = system("dot -Tpng avltree.dot -o avltree.png");
    std::system("start avltree.png");


    if (returnCode == 0) {
        std::cout << "Command executed successfully." << std::endl;
    } else {
        std::cout << "Command execution failed or returned non-zero: " << returnCode << std::endl;
    }
}

void AVLTree::graph(Node *root, std::ofstream &content) {
    if (root != nullptr) {
        content << "Nodo" << root << "[label = \"" << root->correo << "\"]" << std::endl;

        if (root->left != nullptr) {
            content << "Nodo" << root << "->Nodo" << root->left << std::endl;
        }

        if (root->right != nullptr) {
            content << "Nodo" << root << "->Nodo" << root->right << std::endl;
        }

        graph(root->left, content);
        graph(root->right, content);
    }
}

Node* AVLTree::buscarPorCorreo(Node* root, const string& correo) {
    if (root == nullptr || root->correo == correo) {
        return root;  // Retorna el nodo encontrado o nullptr si no existe
    } else if (correo < root->correo) {
        return buscarPorCorreo(root->left, correo);  // Buscar en el subárbol izquierdo
    } else {
        return buscarPorCorreo(root->right, correo);  // Buscar en el subárbol derecho
    }
}

Node* AVLTree::buscarPorCorreo(const string& correo) {
    return buscarPorCorreo(root, correo);
}

bool AVLTree::verificarCredenciales(const string& correo, const string& contrasena) {
    Node* nodo = buscarPorCorreo(correo);  // Busca el nodo por el correo
    if (nodo != nullptr && nodo->contrasena == contrasena) {
        return true;  // Las credenciales son correctas
    }
    return false;  // Credenciales incorrectas
}



