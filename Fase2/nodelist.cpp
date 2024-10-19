#include "nodelist.h"

// Constructor por defecto
NodeList::NodeList() {
    huffNode = nullptr;
    next = nullptr;
}

// Constructor parametrizado
NodeList::NodeList(HuffmanNode* huffNode) {
    this->huffNode = huffNode;
    next = nullptr;
}
