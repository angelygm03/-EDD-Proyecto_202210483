#include "headers/stacknode.h"

// Constructor inicializa los valores del nodo
StackNode::StackNode(string emisor, string receptor, string estado)
    : emisor(emisor), receptor(receptor), estado(estado), next(nullptr) {}