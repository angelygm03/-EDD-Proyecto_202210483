#include "headers/mylist.h"
#include <iostream>
#include <fstream>


// Constructor inicializa la cabeza de la lista como nula y el tamaño en 0
MyList::MyList() : head(nullptr), size(0) {}

// Método para insertar un nuevo nodo al final de la lista
void MyList::insert(string nombres, string apellidos, string fechaNacimiento, string correo, string contrasena) {
    // Crear un nuevo nodo con los datos
    Node* newNode = new Node(nombres, apellidos, fechaNacimiento, correo, contrasena);

    // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
    if (head == nullptr) {
        head = newNode;
    } else {
        // De lo contrario, recorrer la lista hasta el último nodo
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        // Conectar el último nodo con el nuevo nodo
        current->next = newNode;
    }
    size++; // Incrementar el tamaño de la lista
}

// Método para imprimir todos los nodos de la lista
void MyList::print() {
    if (head == nullptr) {
        cout << "No hay usuarios en la lista." << endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        current->print();
        current = current->next;
    }
}

// Método para buscar un nodo por su correo electrónico
Node* MyList::buscar(const string& correo) {
    Node* current = head;
    while (current != nullptr) {
        if (current->correo == correo) {
            return current;
        }
        current = current->next;
    }
    return nullptr; // Retorna nullptr si no se encuentra el nodo
}

// Método para eliminar un nodo por su correo electrónico
bool MyList::eliminar(const string& correo) {
    if (head == nullptr) {
        return false; // Lista vacía, no se puede eliminar nada
    }

    // Si el nodo a eliminar es el primero
    if (head->correo == correo) {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->correo == correo) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }
        current = current->next;
    }
    return false; // Nodo no encontrado
}

void MyList::manejarSolicitudes(Node* usuario) {
    StackNode* current = usuario->solicitudes.getTop(); // Accede al nodo superior de la pila

    bool hayPendientes = false;

    while (current != nullptr) {
        if (current->estado == "PENDIENTE") {
            hayPendientes = true;

            // Buscar el emisor en la lista de usuarios
            Node* solicitante = buscar(current->emisor);
            if (solicitante != nullptr) {
                string nombreCompleto = solicitante->nombres + " " + solicitante->apellidos; // Concatenar nombres y apellidos

                cout << "--------------- Solicitud de Amistad --------------- \n";
                cout << "Nombre: " << nombreCompleto << endl;
                cout << "Correo: " << solicitante->correo << endl;
            } else {
                cout << "El solicitante no se encuentra en la lista de usuarios." << endl;
            }

            cout << "¿Deseas aceptar esta solicitud? (s/n): ";
            char decision;
            cin >> decision;

            if (decision == 's' || decision == 'S') {
                current->estado = "ACEPTADA";
                cout << "Solicitud aceptada." << endl;
            } else if (decision == 'n' || decision == 'N') {
                current->estado = "RECHAZADA";
                cout << "Solicitud rechazada." << endl;
            } else {
                cout << "Mantenida como pendiente." << endl;
            }

            // Eliminar la solicitud de la lista enlazada del emisor
            if (solicitante != nullptr) {
                solicitante->solicitudListEnviadas.eliminarPorEmisorYReceptor(current->emisor, usuario->correo);
            }

            // Ahora elimina la solicitud de la pila del receptor
            usuario->solicitudes.pop();

            // Actualizar el puntero al nuevo nodo superior
            current = usuario->solicitudes.getTop();

        } else {
            // Si la solicitud no es pendiente, se avanza al siguiente nodo sin eliminar el actual
            current = current->next;
        }
    }

    if (!hayPendientes) {
        cout << "No tienes mas solicitudes pendientes." << endl;
    }
}


void MyList::generateDotFile() {
    ofstream file("reporteUsuarios.dot");
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo para escribir el .dot" << endl;
        return;
    }

    file << "digraph G {" << endl;
    file << "rankdir=LR;\n";
    file << "node [shape=box];\n";

    Node* current = head;
    while (current != nullptr) {
        file << "\"" << current->correo << "\" [label=\"" << current->nombres << " " << current->apellidos << "\\n" << current->correo << "\"];" << endl;
        if (current->next != nullptr) {
            file << "\"" << current->correo << "\" -> \"" << current->next->correo << "\";" << endl;
        }
        current = current->next;
    }
    file << "}" << endl;

    file.close();

    // Convertir el archivo .dot a .png automáticamente
    system("dot -Tpng reporteUsuarios.dot -o reporteUsuarios.png");
    system("start reporteUsuarios.png");
}

// Método para agregar una solicitud a la lista simple del emisor
void MyList::agregarSolicitudEnviada(const string& emisor, const string& receptor) {
    Node* usuario = buscar(emisor);
    if (usuario != nullptr) {
        usuario->solicitudListEnviadas.insert(emisor, receptor, "PENDIENTE");
    } else {
        cout << "El usuario emisor no se encontro." << endl;
    }
}


// Método para generar el archivo dot de las solicitudes enviadas
void MyList::generateSolicitudDotFile(Node* usuario) {
    if (usuario != nullptr) {
        usuario->solicitudListEnviadas.generateDotFile("reporteSolicitudes_" + usuario->correo);
    } else {
        cout << "Usuario no encontrado para generar reporte de solicitudes." << endl;
    }
}