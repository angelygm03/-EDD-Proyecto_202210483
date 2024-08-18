#ifndef STACK_H
#define STACK_H

#include "stacknode.h"

class Stack {
private:
    StackNode* top;

public:
    Stack();

    void push(string emisor, string receptor, string estado);
    void pop();
    bool isEmpty() const;
    void print() const;
};

#endif
