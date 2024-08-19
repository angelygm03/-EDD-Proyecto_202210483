#include "headers/circularDoubleList.h"

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
