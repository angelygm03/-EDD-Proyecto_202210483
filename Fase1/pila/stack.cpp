#include "headers/stack.h"
#include <iostream>

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
