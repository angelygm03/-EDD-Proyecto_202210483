#include "stack.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

// Constructor inicializa la pila vacía
Stack::Stack() : top(nullptr) {}

// Método para insertar un nuevo nodo en la pila
void Stack::push(string emisor, string receptor, string estado) {
    StackNode* newNode = new StackNode(emisor, receptor, estado);
    newNode->next = top;
    top = newNode;
}

// Método para eliminar el nodo superior de la pila
void Stack::pop() {
    if (isEmpty()) {
        std::cout << "La pila está vacía." << std::endl;
        return;
    }
    StackNode* temp = top;
    top = top->next;
    delete temp;
}

// Método para verificar si la pila está vacía
bool Stack::isEmpty() const {
    return top == nullptr;
}

// Método para imprimir la pila
void Stack::print() const {
    StackNode* current = top;
    while (current != nullptr) {
        std::cout << "Emisor: " << current->emisor << std::endl;
        std::cout << "Receptor: " << current->receptor << std::endl;
        std::cout << "Estado: " << current->estado << std::endl;
        std::cout << "-----------------------------" << std::endl;
        current = current->next;
    }
}

// Método para obtener el nodo superior de la pila
StackNode* Stack::getTop() const {
    return top;
}

void Stack::generateDotFile(const string& filename, const string& receptor) const {
    ofstream file(filename + ".dot");
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo para escribir el .dot" << endl;
        return;
    }

    file << "digraph G {\n";
    file << "rankdir=TB;\n";
    file << "node [shape=none, margin=0];\n";
    file << "struct1 [label=<\n";
    file << "<TABLE BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n";

    StackNode* current = top;

    while (current != nullptr) {
        if (current->receptor == receptor && current->estado == "PENDIENTE") {
            file << "<TR><TD>Emisor: " << current->emisor << "<br/>Estado: " << current->estado << "</TD></TR>\n";
        }
        current = current->next;
    }

    file << "</TABLE>\n";
    file << ">];\n";
    file << "}\n";
    file.close();

    // Convertir el archivo .dot a .png automáticamente
    string command = "dot -Tpng " + filename + ".dot -o " + filename + ".png";
    system(command.c_str());

    // Abrir el archivo .png generado
    command = "start " + filename + ".png";
    system(command.c_str());
}
