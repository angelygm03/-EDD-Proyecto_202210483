#ifndef SIMPLELIST_H
#define SIMPLELIST_H

#include "nodelist.h"

class SimpleList {
private:
    NodeList* head;
public:
    // Constructor por defecto
    SimpleList();
    int size;

    void push(HuffmanNode* huffNode);
    NodeList* pop();
    void print();
};

#endif // SIMPLELIST_H
