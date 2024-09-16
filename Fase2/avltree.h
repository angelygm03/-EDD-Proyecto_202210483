#include "node.h"
#include <fstream>

#define LEFT_HEAVY -1
#define BALANCED 0
#define RIGHT_HEAVY 1

class AVLTree {
private:
    Node* root;

    Node* insert(Node* root, string nombres, string apellidos, string fechaNacimiento,
                 string correo, string contrasena, bool increase);
    Node* l_rotation(Node* n, Node* n1);
    Node* r_rotation(Node* n, Node* n1);
    Node* lr_rotation(Node* n, Node* n1);
    Node* rl_rotation(Node* n, Node* n1);
    void graph(Node *root, std::ofstream &content);
    Node* buscarPorCorreo(Node* root, const string& correo);

public:
    AVLTree();
    void insert(string nombres, string apellidos, string fechaNacimiento,
                string correo, string contrasena);
    void graph();
    Node* buscarPorCorreo(const string& correo);
    bool verificarCredenciales(const string& correo, const string& contrasena);

};
