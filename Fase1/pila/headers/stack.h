#ifndef STACK_H
#define STACK_H

#include "stacknode.h"

class Stack {
private:
    StackNode* top;  // Puntero al nodo superior de la pila

public:
    Stack();

    void push(string emisor, string receptor, string estado);
    void pop();
    bool isEmpty() const;
    void print() const;

    // método para obtener el nodo superior de la pila
    StackNode* getTop() const;  
};

#endif
