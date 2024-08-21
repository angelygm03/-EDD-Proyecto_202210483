#include "headers/circularDoubleList.h"
#include <fstream>

CircularDoubleList::CircularDoubleList() : head(nullptr), tail(nullptr), size(0) {}

void CircularDoubleList::insertAtEnd(string correo, string contenido, string fecha, string hora) {
    NodeCircularList* newNode = new NodeCircularList(correo, contenido, fecha, hora);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        head->next = head;
        head->prev = head;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
        tail = newNode;
    }
    size++;
}

void CircularDoubleList::print() const {
    if (head == nullptr) {
        cout << "La lista circular está vacía." << endl;
        return;
    }

    NodeCircularList* current = head;
    do {
        current->print();
        current = current->next;
    } while (current != head && current != nullptr);
}

bool CircularDoubleList::deleteByPosition(int position) {
    if (position < 0 || position >= size) {
        return false;
    }

    NodeCircularList* current = head;

    // Si la lista tiene solo un nodo
    if (size == 1) {
        delete current;
        head = nullptr;
        tail = nullptr;
    } else {
        // Navegar hasta el nodo a eliminar
        for (int i = 0; i < position; i++) {
            current = current->next;
        }

        // Actualizar enlaces de nodos
        if (current == head) {
            head = current->next;
            tail->next = head;
            head->prev = tail;
        } else if (current == tail) {
            tail = current->prev;
            tail->next = head;
            head->prev = tail;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
    }

    size--;
    return true;
}

void CircularDoubleList::generateDotFile(const string& filename, const string& userCorreo) const {
    ofstream archivo(filename);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << filename << endl;
        return;
    }

    archivo << "digraph G {\n";
    archivo << "  rankdir=LR;\n";  // Para una representación horizontal
    archivo << "  node [shape=record, height=.1];\n";

    if (head != nullptr) {
        NodeCircularList* current = head;
        NodeCircularList* firstNode = nullptr;
        NodeCircularList* lastNode = nullptr;
        bool found = false;
        int nodeCount = 0;

        // Crear los nodos
        do {
            if (current->correo == userCorreo) {
                archivo << "node" << nodeCount << " [label=\"{<f1>|Correo: " << current->correo
                        << "\\nContenido: " << current->contenido
                        << "\\nFecha: " << current->fecha
                        << "\\nHora: " << current->hora << "|<f2>}\"];\n";
                if (firstNode == nullptr) {
                    firstNode = current;
                }
                lastNode = current;
                found = true;
                nodeCount++;
            }
            current = current->next;
        } while (current != head);

        if (!found) {
            archivo << "  \"NoPublicaciones\" [label=\"No hay publicaciones para este usuario\"];\n";
        } else {
            // Crear las conexiones entre nodos adyacentes
            for (int i = 0; i < nodeCount - 1; ++i) {
                archivo << "node" << i << ":f2 -> node" << i + 1 << ":f1 [dir=both];\n";
            }
            // Conexión bidireccional entre el primer y el último nodo
            archivo << "node" << nodeCount - 1 << ":f2 -> node0:f1 [dir=both];\n";
        }
    }
    archivo << "}\n";
    archivo.close();
    cout << "Archivo DOT generado correctamente." << endl;

    // Convertir el archivo .dot a .png automáticamente
    string command = "dot -Tpng " + filename + " -o " + filename.substr(0, filename.find_last_of('.')) + ".png";
    std::system(command.c_str());

    // Abrir el archivo .png generado
    command = "start " + filename.substr(0, filename.find_last_of('.')) + ".png";
    system(command.c_str());
}
