#include "simplelist.h"
#include <iostream>

SimpleList::SimpleList() {
    size = 0;
    head = nullptr;
}

void SimpleList::push(HuffmanNode* huffNode) {
    NodeList* newNode = new NodeList(huffNode);
    // Si la lista está vacía, asignamos el nuevo nodo
    if (head == nullptr) {
        head = newNode;
        size++;
        return;
    }

    // Encuentra la posición correcta para insertar el nuevo nodo
    NodeList* current = head;
    while (current->next != nullptr && current->next->huffNode->freq <= newNode->huffNode->freq) {
        current = current->next;
    }

    // Insertar el nuevo nodo en la posición correcta
    newNode->next = current->next;
    current->next = newNode;
    size++;
}

NodeList* SimpleList::pop() {
    if (head == nullptr) {
        std::cout << "La lista está vacía. No se puede realizar pop." << std::endl;
        return nullptr;
    }

    NodeList* temp = head; // Guardamos el nodo cabeza
    head = head->next; // Mover la cabeza al siguiente nodo
    size--;
    return temp;       // Devuelve el nodo eliminado
}

void SimpleList::print() {
    if (head == nullptr) {
        std::cout << "La lista está vacía" << std::endl;
        return;
    } else {
        NodeList* current = head;
        // Recorre la lista e imprime cada nodo
        while (current != nullptr) {
            std::cout << current->huffNode->data << ": " << current->huffNode->freq << std::endl;
            current = current->next;
        }
    }
}
