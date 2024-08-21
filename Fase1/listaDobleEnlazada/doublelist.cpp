#include "headers/doublelist.h"
#include <fstream>

// Constructor
DoubleList::DoubleList() : head(nullptr), tail(nullptr), size(0) {}

// Método para insertar al principio de la lista doblemente enlazada
void DoubleList::insertAtBeginning(string correo, string contenido, string fecha, string hora) {
    NodeDoubleList* newNode = new NodeDoubleList(correo, contenido, fecha, hora);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
    size++;
}

// Inserta una publicación al final de la lista
void DoubleList::insertAtEnd(const string& correo, const string& contenido, const string& fecha, const string& hora) {
    NodeDoubleList* newNode = new NodeDoubleList(correo, contenido, fecha, hora);

    if (tail == nullptr) { // Si la lista está vacía
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

// Inserta una publicación en una posición específica
void DoubleList::insertAtPosition(int givenPosition, string correo, string contenido, string fecha, string hora) {
    if (givenPosition <= 0) {
        insertAtBeginning(correo, contenido, fecha, hora);
    } else if (givenPosition >= size) {
        insertAtEnd(correo, contenido, fecha, hora);
    } else {
        NodeDoubleList* newNode = new NodeDoubleList(correo, contenido, fecha, hora);
        NodeDoubleList* current = head;
        for (int actualPosition = 0; actualPosition < givenPosition - 1; actualPosition++) {
            current = current->next;
        }

        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;

        size++;
    }
}

// Imprime la lista completa
void DoubleList::print() const {
    if (head == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

    NodeDoubleList* current = head;
    int position = 0;
    while (current != nullptr) {
        cout << "ID " << position << ": ";
        current->print();
        current = current->next;
        position++;
    }
}

// Elimina una publicación por su ID (position)
bool DoubleList::deleteAtPosition(int position) {
    if (position < 0 || position >= size) {
        return false;
    }

    NodeDoubleList* current = head;
    for (int actualPosition = 0; actualPosition < position; actualPosition++) {
        current = current->next;
    }

    if (current == head) {
        head = current->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
    } else if (current == tail) {
        tail = current->prev;
        tail->next = nullptr;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    delete current;
    size--;
    return true;
}

//Método para imprimir las publicaciones de un usuario específico
void DoubleList::printByUser(const string& correoUsuario) const {
    if (head == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

    NodeDoubleList* current = head;
    int position = 0;
    while (current != nullptr) {
        if (current->correo == correoUsuario) {
            cout << "ID " << position << ": ";
            current->print();
        }
        current = current->next;
        position++;
    }
}

//Método para eliminar las publicaciones de un usuario específico
bool DoubleList::deleteByUser(int position, const string& correoUsuario) {
    NodeDoubleList* current = head;
    int actualPosition = 0;
    while (current != nullptr) {
        if (current->correo == correoUsuario && actualPosition == position) {
            if (current == head) {
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
            } else if (current == tail) {
                tail = current->prev;
                if (tail != nullptr) {
                    tail->next = nullptr;
                }
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            size--;
            return true;
        }
        current = current->next;
        actualPosition++;
    }
    return false; // No se encontró la publicación
}

//Método para generar un archivo con las publicaciones de un usuario
void DoubleList::generateDotFile() {
    ofstream file("reportePublicaciones.dot");
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo para escribir el .dot" << endl;
        return;
    }

    file << "digraph G {" << endl;
    file << "rankdir=LR;\n"; // Layout horizontal
    file << "node [shape=box];\n";

    NodeDoubleList* current = head;
    while (current != nullptr) {
        // Etiqueta de cada nodo con correo, contenido, fecha y hora
        file << "\"" << current << "\" [label=\""
             << "Correo: " << current->correo << "\\n"
             << "Contenido: " << current->contenido << "\\n"
             << "Fecha: " << current->fecha << "\\n"
             << "Hora: " << current->hora << "\"];" << endl;

        // Flechas entre los nodos
        if (current->next != nullptr) {
            file << "\"" << current << "\" -> \"" << current->next << "\" [dir=both];" << endl;
        }

        current = current->next;
    }

    file << "}" << endl;

    file.close();

    // Convertir el archivo .dot a .png automáticamente
    system("dot -Tpng reportePublicaciones.dot -o reportePublicaciones.png");
    system("start reportePublicaciones.png");
}


// Método para obtener e imprimir los 5 usuarios con más publicaciones
void DoubleList::printTopUsersByPublications() const {
    const int MAX_USERS = 200;
    string users[MAX_USERS];
    int counts[MAX_USERS] = {0};  // Array para contar publicaciones
    int numUsers = 0;  // Número actual de usuarios únicos

    // Contar publicaciones por usuario
    NodeDoubleList* current = head;
    while (current != nullptr) {
        bool found = false;
        for (int i = 0; i < numUsers; ++i) {
            if (users[i] == current->correo) {
                counts[i]++;
                found = true;
                break;
            }
        }

        if (!found) {
            if (numUsers < MAX_USERS) {
                users[numUsers] = current->correo;
                counts[numUsers] = 1;
                numUsers++;
            }
        }

        current = current->next;
    }

    // Ordenar usuarios por número de publicaciones usando el método de burbuja
    for (int i = 0; i < numUsers - 1; ++i) {
        for (int j = 0; j < numUsers - i - 1; ++j) {
            if (counts[j] < counts[j + 1]) {
                // Intercambiar conteos
                int tempCount = counts[j];
                counts[j] = counts[j + 1];
                counts[j + 1] = tempCount;

                // Intercambiar usuarios
                string tempUser = users[j];
                users[j] = users[j + 1];
                users[j + 1] = tempUser;
            }
        }
    }

    // Imprimir los 5 usuarios con más publicaciones
    for (int i = 0; i < 5 && i < numUsers; ++i) {
        cout << "Usuario: " << users[i] << " Publicaciones: " << counts[i] << endl;
    }
}