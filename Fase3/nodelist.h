#ifndef NODELIST_H
#define NODELIST_H

#include "huffmannode.h"

class NodeList {
public:
    NodeList();
    NodeList(HuffmanNode* huffNode);

    NodeList* next;
    HuffmanNode* huffNode;
};

#endif // NODELIST_H
