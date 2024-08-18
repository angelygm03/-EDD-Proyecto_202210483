#include "headers/mylist.h"

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

                string nombreCompleto = solicitante->nombres + " " + solicitante->apellidos; //concatenar nombres y apellidos

                cout <<"--------------- Solicitud de Amistad --------------- \n";
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

            // Eliminar el nodo procesado de la pila
            usuario->solicitudes.pop(); 
            current = usuario->solicitudes.getTop(); // Actualizar el puntero al nuevo nodo superior

        } else {
            // Si la solicitud no es pendiente se avanzamos al siguiente nodo sin eliminar el actual
            current = current->next;
        }
    }

    if (!hayPendientes) {
        cout << "No tienes más solicitudes pendientes." << endl;
    }
}
